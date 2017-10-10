#include "Map.h"



void Map::init()
{
	nFiles = 0;
	files = new File[2];
	maxFiles = 2;

	nMaps = 0;
	vMap = std::vector<Map *>();
	maxMaps = 2;
}


Map::Map()
{
	this->mapName = "root";
	root = this;

	init();
}

Map::Map(const std::string& mapName, Map * root)
{
	this->mapName = mapName;
	this->root = root;

	init();
}

Map::~Map()
{
	for (size_t i = 0; i < nMaps; i++)
	{
		delete vMap[i];
	}

	if (nFiles > 0)
		delete[] files;
}


//Simply returns the index of the map based on the name
int Map::getMapIndex(const std::string & name)
{
	for (int i = 0; i < nMaps; i++)
	{
		if (vMap[i]->getName() == name)
			return i;
	}
	return -1;
}
Map * Map::getRoot() const
{
	return this->root;
}
//Returns the name of the map
std::string Map::getName() const
{
	return this->mapName;
}
//-----------------------------------------	Files
int Map::getFilesSize() const
{
	return nFiles;
}
//return the name on all the files
std::string * Map::getFilesNames() const
{
	std::string * arr = new std::string[nFiles];
	for (size_t i = 0; i < nFiles; i++)
	{
		arr[i] = files[i].fileName;
	}
	return arr;
}

void Map::addFile(const std::string& fileName, int block)
{

	if (nFiles < maxFiles) {
		int i = nFiles;
		this->files[i].fileBlock = block;
		this->files[i].fileName = fileName;
	}
	else
	{
		this->expand(files, nFiles, maxFiles * 2);
		maxFiles *= 2;

		int i = nFiles;
		this->files[i].fileBlock = block;
		this->files[i].fileName = fileName;
	}
}
//-----------------------------------------	Maps
int Map::getMapsSize() const
{
	return nMaps;
}
std::vector<Map*> Map::getMaps() const
{
	return vMap;
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
	nMaps = 0;
	nFiles = 0;
	delete[] files;


}
//returns true if the map exists
bool Map::mapExist(const std::string & name) const
{
	if (name.empty())
		return true;
	for (int i = 0; i < nMaps; i++)
	{
		if (this->vMap[i]->getName() == name)
			return true;
	}
	return false;
}