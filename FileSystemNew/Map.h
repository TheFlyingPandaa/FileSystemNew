#ifndef Map_h
#define Map_h
#include <string>
#include <vector>
#include <string.h>
//debug
#include <iostream>


struct File
{
	File(const std::string& name, int n, int * file, int bytes, std::string user) {
		this->fileName = name;
		this->nrOfBlocks = n;
		this->fileBlocks = file;
		this->bytes = bytes;
		this->user = user;
	}

	int bytes;
	int nrOfBlocks;
	int * fileBlocks;

	std::string user;
	std::string fileName;
};

class Map
{
private:

	int id;

	Map * root;
	std::string mapName;

	int nFiles;
	std::vector<File *> vFiles;
	
	int nMaps;	
	std::vector<Map *> vMap;

	

	
public:
	Map();
	Map(const std::string & name, Map * root = nullptr, int id = -1);
	~Map();
	
	//-----------------------------------------------	Map Info

	Map * getRoot() const;
	int getID() const;
	std::string getName() const;

	//-----------------------------------------------	Files

	std::vector<File *> getFiles() const;
	File * getFile(const int & index);

	void addFile(const std::string& fileName, int nrOfBlocks, int * block, int bytes, const std::string & user);
	void removeFile(const std::string & fileName);

	bool fileExist(const std::string & name) const;

	int getFilesSize() const;
	int getFileIndex(const std::string & name);

	//-----------------------------------------------	Maps

	std::vector<Map*> getMaps() const;
	Map * getMap(const int & index) const;

	void addMap(const std::string& mapName, int id = -1);
	void addMap(Map * map);
	void removeMap(const std::string& name);

	bool mapExist(const std::string & name) const;

	int getMapsSize() const;
	int getMapIndex(const std::string & name);

	//-----------------------------------------------	plz no memory leaks

	void removeEverything();

	void saveString(Map * current, std::string * input, int  index) const;
	void saveString(std::string * buffert) const;
	

};


#endif // !Map_H