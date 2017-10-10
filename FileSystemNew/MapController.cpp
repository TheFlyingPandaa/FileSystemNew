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
}

MapController::~MapController()
{
	root->removeEverything();
	delete root;
}

std::string MapController::ls() const
{
	std::string string = "Type\tName\tSize\n";
	string += getMaps();
	string += getFiles();
	return string;
}

std::string MapController::getMaps() const
{
	int size = current->getMapsSize();
	std::string s = "";

	for (size_t i = 0; i < size; i++)
	{
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
	for (size_t i = 0; i < size; i++)
	{
		s += "FILE\t";
		s += current->getFiles()[i]->fileName + "\t";
		s += std::to_string(current->getFiles()[i]->nrOfBlocks);
		s += "\n";
	}

	return s;
}

void MapController::addFile(const std::string & name, int nrOfBlocks)
{
	if (!current->fileExist(name) && !name.empty())
	{
		int * nBlocks = this->getBlocks(nrOfBlocks);
		if (nBlocks != nullptr)
			current->addFile(name, nrOfBlocks, nBlocks);
	}
}
int * MapController::getBlocks(int nrOfBlocks)
{
	if (this->blockesUsed < this->nrOfBlocks && 
		this->nrOfBlocks - this->blockesUsed > nrOfBlocks) {
		int i = 0;
		int * nBlocks = new int[nrOfBlocks];
		while (i < nrOfBlocks)
		{
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

void MapController::createMap(const std::string & name)
{
	if (!current->mapExist(name) && !name.empty())
		current->addMap(name);
}

void MapController::removeMap(const std::string & name)
{
	if (current->mapExist(name) && !name.empty())
		current->removeMap(name);
}

void MapController::goToMap(const std::string & name)
{
	if (name == "..")
	{
		current = current->getRoot();
	}
	if (current->mapExist(name))
	{
		current = current->getMaps()[current->getMapIndex(name)];
	}
}

std::string MapController::pwd() const
{
	std::string retString = "root/";

	std::vector<std::string> s = std::vector<std::string>();
	Map * walker = current;
	int size = 0;

	while (walker->getRoot() != walker)
	{
		s.push_back(walker->getName());
		size++;
		walker = walker->getRoot();
	}

	for (size_t i = 0; i < size; i++)
	{
		retString += s.back() + "/";
		s.pop_back();
	}

	return retString;
}
