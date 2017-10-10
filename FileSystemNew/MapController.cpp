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
	for (size_t i = 0; i < size; i++)
	{
		std::cout << current->getMaps()[i]->getName() << "\t" << std::endl;
	}
	return std::string();
}

void MapController::createMap(const std::string & name)
{
	if (!current->mapExist(name) && !name.empty())
		current->addMap(name);
	else
		std::cout << "The filename already exists or there was an invalid filename" << std::endl;
}

void MapController::removeMap(const std::string & name)
{
	if (current->mapExist(name))
		current->removeMap(name);
	else
		std::cout << "Can't find file" << std::endl;
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