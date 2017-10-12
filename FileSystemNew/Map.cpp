#include "Map.h"




Map::Map()
{
	this->mapName = "root";
	root = this;

	nFiles = 0;
	vFiles = std::vector<File *>();

	nMaps = 0;
	vMap = std::vector<Map *>();

	
}
Map::Map(const std::string& mapName, Map * root)
{
	this->mapName = mapName;
	this->root = root;

	nFiles = 0;
	vFiles = std::vector<File *>();

	nMaps = 0;
	vMap = std::vector<Map *>();

	

}
Map::~Map()
{
	for (size_t i = 0; i < nMaps; i++)
	{		
		delete vMap[i];
	}
	for (size_t i = 0; i < nFiles; i++)
	{
		delete[] vFiles[i]->fileBlocks;
		delete vFiles[i];
	}
	
}

//-----------------------------------------------	Map info

Map * Map::getRoot() const
{
	return this->root;
}
std::string Map::getName() const
{
	return this->mapName;
}

//-----------------------------------------------	Files

std::vector<File*> Map::getFiles() const
{
	return vFiles;
}
File * Map::getFile(const int & index)
{
	
		return vFiles[index];
	
}

void Map::addFile(const std::string& fileName, int nrOfBlocks, int * blocks, int bytes)
{	
	this->vFiles.push_back(new File(fileName, nrOfBlocks, blocks, bytes));
	
	nFiles++;
}
void Map::removeFile(const std::string & fileName)
{
	int index = getFileIndex(fileName);

	if (index != -1)
	{
		delete[] vFiles[index]->fileBlocks;
		delete vFiles[index];
		vFiles.erase(vFiles.begin() + index);
		nFiles--;
	}
}

bool Map::fileExist(const std::string & name) const
{
	for (int i = 0; i < nFiles; i++)
	{
		if (this->vFiles[i]->fileName == name)
			return true;
	}
	return false;
}

int Map::getFilesSize() const
{
	return nFiles;
}
int Map::getFileIndex(const std::string & name)
{
	
	for (int i = 0; i < nFiles; i++)
	{
		
		if (vFiles[i]->fileName == name)
			return i;
	}
	return -1;
}

//-----------------------------------------------	Maps

std::vector<Map*> Map::getMaps() const
{
	return vMap;
}

Map * Map::getMap(const int & index) const
{	
	return vMap[index];
}

void Map::addMap(const std::string & mapName)
{
	this->vMap.push_back(new Map(mapName, this));
	nMaps++;
}
void Map::removeMap(const std::string & name)
{
	int index = getMapIndex(name);
	
	if (index != -1)
	{
		vMap[index]->removeEverything();
		delete vMap[index];
		vMap.erase(vMap.begin() + index);
		nMaps--;
	}
	vMap.shrink_to_fit();

}

bool Map::mapExist(const std::string & name) const
{		
	for (int i = 0; i < nMaps; i++)
	{
		if (this->vMap[i]->getName() == name)
			return true;
	}
	return false;
}

int Map::getMapsSize() const
{
	return nMaps;
}
int Map::getMapIndex(const std::string & name)
{
	for (int i = 0; i < nMaps; i++)
	{
		if (vMap[i]->getName() == name)
			return i;
	}
	return -1;
}

//-----------------------------------------------	plz no memory leaks

void Map::removeEverything()
{
	for (int i = 0; i < nMaps; i++)
	{
		vMap[i]->removeEverything();
	}

	for (size_t i = 0; i < nMaps; i++)
	{
		delete vMap[i];
	}
	for (size_t i = 0; i < nFiles; i++)
	{
		delete[] vFiles[i]->fileBlocks;
		delete vFiles[i];
	}
	nMaps = 0;
	nFiles = 0;
}

void Map::saveString(Map * current, std::string * input, int index) const
{
	input[index] += current->mapName + "\n";
	input[index] += "\t" + current->root->mapName + "\n";

	input[index] += "\t" + std::to_string(current->nFiles) + "\n";

	for (int i = 0; i < current->nFiles; i++)
	{
		input[index] += "\t\t" + current->vFiles[i]->fileName + "\n";
		input[index] += "\t\t" + std::to_string(current->vFiles[i]->nrOfBlocks) + "\n";
		for (int j = 0; j < current->vFiles[i]->nrOfBlocks; j++)
		{
			input[index] += "\t\t" + std::to_string(current->vFiles[i]->fileBlocks[j]) + "\n";
		}
		
		input[index] += "\t\t" + std::to_string(current->vFiles[i]->bytes) + "\n";
	}
	for (int i = 0; i < current->nMaps; i++)
	{
		current->vMap[i]->saveString(current->vMap[i], input, index + 1);
	}
}

void Map::saveString(std::string * buffert, int * index) const
{
	saveString(this->root, buffert, 0);
}
