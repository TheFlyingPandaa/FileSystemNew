#ifndef MapC_H
#define MapC_H
#include "Map.h"

class MapController
{
private: 
	Map * root;
	Map * current;

	int pos;
	int blockesUsed;
	unsigned int nrOfBlocks;
	bool * blocks;

	int * getBlocks(int nrOfBlocks);
	std::string getMaps() const;
	std::string getFiles() const;

	std::string byteToKB(const int & bytes) const;

public:
	MapController(int nrOfBlocks = 250);
	~MapController();

	std::string ls() const;

	void addFile(const std::string & name, int nrOfBlocks, int byts = 0);
	void addFile(const std::string & name, int nrOfBlocks, int *& blocks, int fileSize = 0);
	void removeFile(const std::string & name);

	void createMap(const std::string & name);
	void removeMap(const std::string & name);

	void goToMap(const std::string & name);

	std::string pwd() const;
};

#endif // !MapC_H
