#include "memblockdevice.h"
#include <stdexcept>

MemBlockDevice::MemBlockDevice(int nrOfBlocks): BlockDevice(nrOfBlocks) {
	this->nrOfBlocks = nrOfBlocks;
	
}

MemBlockDevice::MemBlockDevice(const MemBlockDevice &other) : BlockDevice(other) {

}

MemBlockDevice::~MemBlockDevice() {
    /* Implicit call to base-class destructor */
}

MemBlockDevice& MemBlockDevice::operator=(const MemBlockDevice &other) {
    delete [] this->memBlocks;
    this->nrOfBlocks = other.nrOfBlocks;
    this->freePointer = other.freePointer;
    this->memBlocks = new Block[this->nrOfBlocks];

    for (int i = 0; i < this->nrOfBlocks; ++i)
        this->memBlocks[i] = other.memBlocks[i];

    return *this;
}

Block& MemBlockDevice::operator[](int index) const {
    if (index < 0 || index >= this->nrOfBlocks) {
        throw std::out_of_range("Illegal access\n");
    }
    else {
        return this->memBlocks[index];
    }
}

int MemBlockDevice::spaceLeft() const {
    
	int amountOfSpace = 0;

	for (int i = 0; i < 250; i++)
	{
		std::string tempString;
		tempString = memBlocks[i].readBlock().toString();
		int checkSum = 512;
		for (int j = 0; j < 512; j++) //512 = block size
		{
			if (tempString[j] == '0')
			{
				checkSum--;
			}
		}
		if (checkSum == 0)
		{
			amountOfSpace++;
		}
	}

	return amountOfSpace;
    
}

int MemBlockDevice::writeBlock(int blockNr, const std::vector<char> &vec, const std::string newOwner) {
    int output = -1;    // Assume blockNr out-of-range

    if (blockNr < this->nrOfBlocks && blockNr >= 0) {
        /* -2 = vec and block dont have same dimensions */
        /* 1 = success */
        output = this->memBlocks[blockNr].writeBlock(vec, newOwner);
    }
    return output;
}

int MemBlockDevice::writeBlock(int blockNr, const std::string &strBlock, const std::string newOwner) {
    int output = -1;    // Assume blockNr out-of-range

    if (blockNr < this->nrOfBlocks && blockNr >= 0) {
        /* -2 = str-length and block dont have same dimensions */
        /* 1 = success */
        output = this->memBlocks[blockNr].writeBlock(strBlock, newOwner);
    }
    return output;
}

int MemBlockDevice::writeBlock(int blockNr, const char cArr[], const std::string newOwner) {
    int output = -1;    // Assume blockNr out-of-range
    if (blockNr < this->nrOfBlocks && blockNr >= 0) {
        output = 1;
        // Underlying function writeBlock cannot check array-dimension.
        this->memBlocks[blockNr].writeBlock(cArr, newOwner);
    }
    return output;
}

Block MemBlockDevice::readBlock(int blockNr) const {
    if (blockNr < 0 || blockNr >= this->nrOfBlocks)
        throw std::out_of_range("Block out of range");
    else {
        Block a(this->memBlocks[blockNr]);
        return a;
    }
}

std::string MemBlockDevice::getOwner(int blockNr) const
{
	return memBlocks[blockNr].getOwner();
}

/* Resets all the blocks */
void MemBlockDevice::reset() {
    for (int i = 0; i < this->nrOfBlocks; ++i) {
        this->memBlocks[i].reset('0');
    }
}

void MemBlockDevice::singleReset(const int block)
{
	this->memBlocks[block].reset('0');
}


int MemBlockDevice::size() const {
    return this->nrOfBlocks;
}
