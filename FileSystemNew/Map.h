#ifndef Map_h
#define Map_h
#include <string>
#include <vector>
#include <string.h>
//debug
#include <iostream>


struct File
{
	File(const std::string& name, int n, int * file, int bytes) {
		this->fileName = name;
		this->nrOfBlocks = n;
		this->fileBlocks = file;
		this->bytes = bytes;
	}
	int bytes;
	int nrOfBlocks;
	int * fileBlocks;
	std::string fileName;
};

class Map
{
private:

	Map * root;
	std::string mapName;

	int nFiles;
	std::vector<File *> vFiles;
	
	int nMaps;	
	std::vector<Map *> vMap;

	

	
public:
	Map();
	Map(const std::string & name, Map * root = nullptr);
	~Map();
	
	//-----------------------------------------------	Map Info

	Map * getRoot() const;
	std::string getName() const;

	//-----------------------------------------------	Files

	std::vector<File *> getFiles() const;
	File * getFile(const int & index);

	void addFile(const std::string& fileName, int nrOfBlocks, int * block, int bytes);
	void removeFile(const std::string & fileName);

	bool fileExist(const std::string & name) const;

	int getFilesSize() const;
	int getFileIndex(const std::string & name);

	//-----------------------------------------------	Maps

	std::vector<Map*> getMaps() const;
	Map * getMap(const int & index) const;

	void addMap(const std::string& mapName);
	void removeMap(const std::string& name);

	bool mapExist(const std::string & name) const;

	int getMapsSize() const;
	int getMapIndex(const std::string & name);

	//-----------------------------------------------	plz no memory leaks

	void removeEverything();

};


#endif // !Map_H