#include "MapController.h"




MapController::MapController(int nrOfBlocks)
{
	root = new Map();
	current = root;

	currentID = 1;

	this->nrOfBlocks = nrOfBlocks;
	blocks = new bool[nrOfBlocks];

	for (int i = 0; i < this->nrOfBlocks; i++)
		blocks[i] = false;

	pos = 0;
	blockesUsed = 0;

	totMaps = 0;

	maps = std::vector<Map*>();
	maps.push_back(root);
	totMaps++;
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
		Map * map = new Map(name, current, currentID);
		maps.push_back(map);
		current->addMap(map);
		totMaps++;
	}
}

void MapController::addFile(const std::string & name, int nrOfBlocks, int bytes, const std::string & user)
{
	if (!current->fileExist(name) && !current->mapExist(name) && !name.empty()) {
		int * nBlocks = this->getBlocks(nrOfBlocks);
		if (nBlocks != nullptr) {
			current->addFile(name, nrOfBlocks, nBlocks, bytes, user);
			this->blockesUsed+=nrOfBlocks;
		}
	}
}
void MapController::addFile(const std::string & name, int nrOfBlocks, int *& blocks, int fileSize, const std::string & user)
{
	if (!current->fileExist(name) && !current->mapExist(name) && !name.empty() && name.find('/') > name.size()) {
		int * nBlocks = this->getBlocks(nrOfBlocks);
		if (nBlocks != nullptr) {
			current->addFile(name, nrOfBlocks, nBlocks, fileSize, user);
			this->blockesUsed+=nrOfBlocks;
		}
		if (blocks != nullptr)
			delete[] blocks;
		blocks = new int[nrOfBlocks];
		for (int i = 0; i < nrOfBlocks; i++)
			blocks[i] = nBlocks[i];
	}
	else if (!current->fileExist(name) && !current->mapExist(name) && !name.empty() && name.find('/') < name.length()) {

		std::string * path = new std::string[64];

		int size = this->splitPath(name, path);
		Map * c = current;
		this->goToMap(name);

		int * nBlocks = this->getBlocks(nrOfBlocks);
		if (nBlocks != nullptr) {
			current->addFile(path[size], nrOfBlocks, nBlocks, fileSize, user);
			this->blockesUsed += nrOfBlocks;
		}
		if (blocks != nullptr)
			delete[] blocks;
		blocks = new int[nrOfBlocks];
		for (int i = 0; i < nrOfBlocks; i++)
			blocks[i] = nBlocks[i];				
		delete[] path;
		this->current = c;
	}
}

void MapController::rm(const std::string & name, const std::string & user)
{
	if (!name.empty()) {
		if (current->fileExist(name) && !current->mapExist(name)) {
			if (current->getFile(current->getFileIndex(name))->user == user)
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
	std::string * input = new std::string[totMaps];
	
	root->saveString(input);

	std::ofstream outFile;
	outFile.open(path);

	outFile << totMaps << std::endl;

	for (int i = 0; i < totMaps; i++)
	{
		outFile << input[i];
	}

	outFile << "0xTOMMY";

	outFile.close();
	delete[] input;
}

void MapController::load(const char * path)
{
	for (size_t i = 0; i < totMaps; i++)
	{
		delete maps[i];
	}
	maps = std::vector<Map *>();
	totMaps = 0;

	std::ifstream inFile;
	inFile.open(path);

	int nMaps;
	inFile >> nMaps;

	int blockPos = 0;

	for (int i = 0; i < nMaps; i++)
	{
		std::string name, root, fileName, user;
		int nFiles, nBlocks, fileSize, mapID, parentID;
		int * memBlocks = new int[0];
		Map * current;

		inFile >> name;
		inFile >> root;
		inFile >> mapID;
		inFile >> parentID;
		if (name == "root") {
			this->root = new Map();
			inFile >> nFiles;
			
			for (int j = 0; j < nFiles; j++)
			{
				inFile >> fileName;
				inFile >> user;
				inFile >> nBlocks;
				blockesUsed += nBlocks;
				delete[] memBlocks;
				memBlocks = new int[nBlocks];
				for (int k = 0; k < nBlocks; k++)
				{
					inFile >> memBlocks[k];
					this->blocks[memBlocks[k]] = true;
					if (memBlocks[k] > blockPos)
						blockPos = memBlocks[k];
				}
				inFile >> fileSize;
				int * copy = new int[nBlocks];
				for (int k = 0; k < nBlocks; k++)
				{
					copy[k] = memBlocks[k];
				}
				this->root->addFile(fileName, nBlocks, copy, fileSize, user);
			}
			this->maps.push_back(this->root);
			
		}
		else
		{
			Map * parent;
			for (int j = 0; j < totMaps; j++)
			{
				if (this->maps[j]->getID() == parentID)
					parent = this->maps[j];
			}
			current = new Map(name, parent, mapID);
			current->getRoot()->addMap(current);
			inFile >> nFiles;

			for (int j = 0; j < nFiles; j++)
			{
				inFile >> fileName;
				inFile >> user;
				inFile >> nBlocks;
				blockesUsed += nBlocks;
				delete[] memBlocks;
				memBlocks = new int[nBlocks];
				for (int k = 0; k < nBlocks; k++)
				{
					inFile >> memBlocks[k];
					this->blocks[memBlocks[k]] = true;
					if (memBlocks[k] > blockPos)
						blockPos = memBlocks[k];
				}
				inFile >> fileSize;
				int * copy = new int[nBlocks];
				for (int k = 0; k < nBlocks; k++)
				{
					copy[k] = memBlocks[k];
				}
				current->addFile(fileName, nBlocks, copy, fileSize, user);
			}
			maps.push_back(current);
		}
		totMaps++;

		delete[] memBlocks;
	}

	

	inFile.close();

	this->current = root;
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

std::string MapController::getName(const std::string & path) const
{
	std::string name;

	int i = 0;
	int index = path.length();

	if (path[path.length()] == '/')
		index = path.length() - 1;

	while (index >= 0)
	{
		if (path[index] != '/')
		{
			name += path[index];
		}
		else
		{
			std::string ret;
			for (int j = name.length(); j > -1; j--)
			{
				ret += name[j];
			}
			return ret;
		}
		index--;
	}
	std::string ret;
	for (int j = name.length(); j > -1; j--)
	{
		ret += name[i];
	}
	return ret;
	
}
