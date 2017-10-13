#ifndef MapC_H
#define MapC_H
#include "Map.h"

#include <iostream>
#include <fstream>

class MapController
{
private: 
	Map * root;
	Map * current;

	int pos;
	int blockesUsed;

	int nrOfBlocks;
	bool * blocks;

	std::vector<Map*> maps;

	int currentID;

	int totMaps;

	std::string getMaps() const;
	std::string getFiles() const;

	std::string byteToKB(const int & bytes) const;

	void removeFile(const std::string & name);
	void removeMap(const std::string & name);

	int * getBlocks(int nrOfBlocks);

	int splitPath(const std::string & path, std::string *& buffert) const;

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

	void save(const char * path);
	void load(const char * path);
};

#endif 