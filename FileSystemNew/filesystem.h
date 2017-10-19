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
	void createFile(const std::string &fileName, const std::string user);

	void createCopyFile(const std::string &oldName, const std::string & newFile, const std::string & user);

	/*Reads a block and outputs to user*/
	Block * readFile(const std::string user, const std::string & fileName, int & size);

	/*Formating the hole file system*/
	void formatSystem();

    /* Creates a folder in the filesystem */
    // createFolderi(...);

	int amountOfBlocksFree() const;

    /* Removes a file in the filesystem */
    void removeFile();

    /* Removes a folder in the filesystem */
    // removeFolder(...);

	/* Saves the hole fileSystem to a txt file*/
	void saveFileSystem();

	/* Restores the hole filesystem from a txt file*/
	void restoreFileSystem();

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

	void mv(const std::string & fileName, const std::string & destFile, const std::string & user);
};

#endif // FILESYSTEM_H
