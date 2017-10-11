#ifndef FILESYSTEM_H
#define FILESYSTEM_H

#include "memblockdevice.h"
#include "MapController.h"
#include <string>
#include <iostream>
#include <vector>

class FileSystem
{
private:
    MemBlockDevice mMemblockDevice;
    // Here you can add your own data structures

	MapController * mapController;

	std::vector<int> openBlocks;
	
public:
    FileSystem();
    ~FileSystem();

    /* These API functions need to be implemented
	   You are free to specify parameter lists and return values
    */

    /* This function creates a file in the filesystem */
    // createFile(...)
	void createFile(const std::string &fileName);

	/*Reads a block and outputs to user*/
	Block readFile();

	/*Formating the hole file system*/
	void formatSystem();

    /* Creates a folder in the filesystem */
    // createFolderi(...);

	int amountOfBlocksFree() const;

    /* Removes a file in the filesystem */
    void removeFile();

    /* Removes a folder in the filesystem */
    // removeFolder(...);

    /* Function will move the current location to a specified location in the filesystem */
    // goToFolder(...);

    /* This function will get all the files and folders in the specified folder */
    // listDir(...);

    /* Add your own member-functions if needed */

	//-----------------------------------	Map Controller Functions
	void mkdir(const std::string & mapName);
	void rm(const std::string & mapName);
	void cd(const std::string & mapName);
	std::string pwd();
	std::string ls();
};

#endif // FILESYSTEM_H
