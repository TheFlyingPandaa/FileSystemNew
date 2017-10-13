#include "MapController.h"




MapController::MapController(int nrOfBlocks)
{
	root = new Map();
	current = root;

	this->nrOfBlocks = nrOfBlocks;
	blocks = new bool[nrOfBlocks];

	for (int i = 0; i < this->nrOfBlocks; i++)
		blocks[i] = false;

	pos = 0;
	blockesUsed = 0;

	totMaps = 0;
}
MapController::~MapController()
{
	root->removeEverything();
	delete root;
	delete[] blocks;
}

//--------------------------------------	Public Commands

 std::string MapController::ls() const
{
	std::string string = "Type\tName\tSize\n";
	string += getMaps();
	string += getFiles();
	return string;
}

void MapController::createMap(const std::string & name)
{
	if (!current->fileExist(name) && !current->mapExist(name) && !name.empty())
	{
		current->addMap(name);
		totMaps++;
	}
}

void MapController::addFile(const std::string & name, int nrOfBlocks, int bytes)
{
	if (!current->fileExist(name) && !current->mapExist(name) && !name.empty()) {
		int * nBlocks = this->getBlocks(nrOfBlocks);
		if (nBlocks != nullptr) {
			current->addFile(name, nrOfBlocks, nBlocks, bytes);
			this->blockesUsed++;
		}
	}
}
void MapController::addFile(const std::string & name, int nrOfBlocks, int *& blocks, int fileSize)
{
	if (!current->fileExist(name) && !current->mapExist(name) && !name.empty()) {
		int * nBlocks = this->getBlocks(nrOfBlocks);
		if (nBlocks != nullptr) {
			current->addFile(name, nrOfBlocks, nBlocks, fileSize);
			this->blockesUsed++;
		}
		blocks = nBlocks;
	}
}

void MapController::rm(const std::string & name)
{
	if (!name.empty()) {
		if (current->fileExist(name) && !current->mapExist(name)) {
			removeFile(name);
		}
		else if (current->mapExist(name) && !current->fileExist(name)) {
			removeMap(name);
			totMaps--;
		}
	}
}

void MapController::goToMap(const std::string & name)
{
	if (name == "..") {
		current = current->getRoot();
	}
	else if (current->mapExist(name) && name.find('/') > name.length()) {
		current = current->getMaps()[current->getMapIndex(name)];
	}
	else if (name.find('/') < name.length()) {
		
		Map * walker = root;

		std::string * buffert = new std::string[64];
		int index = splitPath(name, buffert);		

		for (int i = 0; i < index; i++)
		{			
			if (walker->mapExist(buffert[i]))
				walker = walker->getMaps()[walker->getMapIndex(buffert[i])];
		}
		current = walker;
		delete[] buffert;
	}
}
File * MapController::getFile(const std::string & path) const
{
	Map * walker = root;
	
	std::string * buffert = new std::string[64];
	int index = splitPath(path, buffert);
	std::string nextPath;

	for (int i = 0; i < index; i++)
	{
		//std::cout << buffert[i] << std::endl;
		walker = walker->getMaps()[walker->getMapIndex(buffert[i])];
		
	}
	std::string s = buffert[index];
	
	delete[] buffert;
	//std::cout << s << " " << walker->getFile(walker->getFileIndex(s)) << " " << walker->getFileIndex(s) << std::endl;
	return walker->getFiles()[walker->getFileIndex(s)];
}
std::string MapController::pwd() const
{
	int size = 0;
	Map * walker = current;

	std::string retString = "root/";
	std::vector<std::string> s = std::vector<std::string>();
	
	while (walker->getRoot() != walker) {
		s.push_back(walker->getName());
		size++;
		walker = walker->getRoot();
	}

	for (size_t i = 0; i < size; i++) {
		retString += s.back() + "/";
		s.pop_back();
	}
	return retString;
}

void MapController::save(const char * path)
{
	std::string * input = new std::string[totMaps + 1];
	
	root->saveString(input);

	std::ofstream outFile;
	outFile.open(path);

	for (int i = 0; i < totMaps + 1; i++)
	{
		outFile << input[i];
	}

	outFile.close();
	delete[] input;
}

void MapController::load(const char * path)
{

}

//--------------------------------------	Private 

std::string MapController::getMaps() const
{
	int size = current->getMapsSize();
	std::string s = "";

	for (size_t i = 0; i < size; i++) {
		s += "DIR\t";
		s += current->getMaps()[i]->getName() + "\t";	
		s += "-";
		s += "\n";
	}
	return s;
}
std::string MapController::getFiles() const
{
	int size = current->getFilesSize();
	std::string s = "";
	for (size_t i = 0; i < size; i++) {
		s += "FILE\t";
		s += current->getFiles()[i]->fileName + "\t";
		s += this->byteToKB(current->getFiles()[i]->bytes);
		s += "\n";
	}
	return s;
}

std::string MapController::byteToKB(const int & bytes) const
{
	return std::to_string(bytes / 1000) + "." + std::to_string(bytes % 1000) + " KB";
}

void MapController::removeFile(const std::string & name)
{
	if (current->fileExist(name) && !name.empty()) {
		File * f = current->getFile(current->getFileIndex(name));

		for (int i = 0; i < f->nrOfBlocks; i++) {
			this->blocks[f->fileBlocks[i]] = false;
			this->blockesUsed -= f->nrOfBlocks;
		}
		current->removeFile(name);
	}
}
void MapController::removeMap(const std::string & name)
{
	if (current->mapExist(name) && !name.empty())
		current->removeMap(name);
}

int * MapController::getBlocks(int nrOfBlocks)
{
	if (this->blockesUsed < this->nrOfBlocks && 
		this->nrOfBlocks - this->blockesUsed > nrOfBlocks) {

		int i = 0;
		int * nBlocks = new int[nrOfBlocks];

		while (i < nrOfBlocks) {
			if (!this->blocks[pos]) {
				this->blocks[pos] = true;
				nBlocks[i++] = pos;
			}
			pos++ % this->nrOfBlocks;
		}
		return nBlocks;
	}
	return nullptr;
}

int MapController::splitPath(const std::string & path, std::string *& buffert) const
{
	int i = 0;
	int index = 0;

	if (path[0] == '/')
		index = 1;
	else
		index = 0;
	
	while (index < path.length())
	{
		if (path[index] != '/') 
		{
			buffert[i] += path[index];
		}
		else
			i++;		
		index++;
	}
	return i;

}
