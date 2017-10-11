#ifndef MapC_H
#define MapC_H
#include "Map.h"

#include <iostream>

class MapController
{
private: 
	Map * root;
	Map * current;

	int pos;
	int blockesUsed;

	int nrOfBlocks;
	bool * blocks;

	std::string getMaps() const;
	std::string getFiles() const;

	std::string byteToKB(const int & bytes) const;

	void removeFile(const std::string & name);
	void removeMap(const std::string & name);

	int * getBlocks(int nrOfBlocks);

	std::string * splitPath(const std::string & path) const;

public:

	MapController(int nrOfBlocks = 250);
	~MapController();

	std::string ls() const;

	void createMap(const std::string & name);

	void addFile(const std::string & name, int nrOfBlocks, int byts = 0);
	void addFile(const std::string & name, int nrOfBlocks, int *& blocks, int fileSize = 0);

	void rm(const std::string & name);

	void goToMap(const std::string & name);
	//Syntax: (/)map0/map1/file
	File * getFile(const std::string & path) const;
	std::string pwd() const;
};

#endif 