#ifndef Map_h
#define Map_h
#include <string>
#include <vector>
#include <string.h>


struct File
{
	File(const std::string& name, int n, int * file) {
		this->fileName = name;
		this->nrOfBlocks = n;
		this->fileBlocks = file;
	}
	int nrOfBlocks;
	int * fileBlocks;
	std::string fileName;
};

class Map
{
private:
	std::string mapName;
	Map * root;

	int nFiles;
	int maxFiles;
	std::vector<File *> vFiles;


	int nMaps;
	int maxMaps;	
	std::vector<Map *> vMap;

	void init();



public:
	Map();
	Map(const std::string & name, Map * root = nullptr);
	
	~Map();

	std::string getName() const;
	std::string * getFilesNames() const;
	std::vector<File *> getFiles() const;
	int getFilesSize() const;

	std::vector<Map*> getMaps() const;
	int getMapsSize() const;

	void addFile(const std::string& fileName, int nrOfBlocks, int * block);
	void addMap(const std::string& mapName);

	void removeMap(const std::string& name);

	bool fileExist(const std::string & name) const;
	bool mapExist(const std::string & name) const;

	int getMapIndex(const std::string & name);
	void removeEverything();

	Map * getRoot() const;
};


#endif // !Map_H