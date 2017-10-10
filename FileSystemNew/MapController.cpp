#include "MapController.h"



MapController::MapController()
{
	root = new Map();
	current = root;
}


MapController::~MapController()
{
	root->removeEverything();
	delete root;
}

std::string MapController::getMaps() const
{
	int size = current->getMapsSize();
	std::string s = "";

	for (size_t i = 0; i < size; i++)
	{
		s += current->getMaps()[i]->getName();		
		s += "\n";
	}

	return s;
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
