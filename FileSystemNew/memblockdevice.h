#ifndef MEMBLOCKDEVICE_H
#define MEMBLOCKDEVICE_H
#include "blockdevice.h"
#include <vector>
#include <fstream>

class MemBlockDevice: public BlockDevice
{
public:
    MemBlockDevice(int nrOfBlocks = 250);
    MemBlockDevice(const MemBlockDevice &other);

    ~MemBlockDevice();

    /* Operators */
    MemBlockDevice& operator=(const MemBlockDevice &other);
    Block &operator[] (int index) const;

    /* Returns amount of free blocks */
    int spaceLeft() const;

    /* Writes a block */
    int writeBlock(int blockNr, const std::vector<char> &vec, const std::string newOwner);
    int writeBlock(int blockNr, const std::string &strBlock, const std::string newOwner);
    int writeBlock(int blockNr, const char cArr[], const std::string newOwner);     // Use with care, make sure that cArr has at least the same dimension as block

    /* Reads a block */
    Block readBlock(int blockNr) const;

	std::string getOwner(int blockNr) const;
    /* Resets all the blocks */
    void reset();

	/* Resets a single block */
	void singleReset(const int block);

	/* Function for saving the blocks to a file*/
	void saveBlocks(const char * path);

	void editReadWrite(int blockNr, bool readAll, bool writeAll);

	/* Function for reading in the blocks*/
	void readSavedBlocks(const char * path);

    /* Return the size */
    int size() const;
};

#endif // MEMBLOCKDEVICE_H
