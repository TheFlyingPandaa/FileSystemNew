#include <iostream>
#include <iomanip>
#include <sstream>
#include "filesystem.h"
#include "MapController.h"

const int MAXCOMMANDS = 8;
const int NUMAVAILABLECOMMANDS = 15;

std::string availableCommands[NUMAVAILABLECOMMANDS] = {
    "quit","format","ls","create","cat","createImage","restoreImage",
    "rm","cp","append","mv","mkdir","cd","pwd","help"
};

/* Takes usercommand from input and returns number of commands, commands are stored in strArr[] */
int parseCommandString(const std::string &userCommand, std::string strArr[]);
int findCommand(std::string &command);
bool quit();
std::string help();

/* More functions ... */

int main(void) {
	_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
	FileSystem fileSystem = FileSystem();

	std::string userCommand, commandArr[MAXCOMMANDS];
	std::string user = "user@JIM";    // JIMMMMMMMMMM
	std::string currentDir = "/";    // current directory, used for output

	std::string dataInput;
    bool bRun = true;

	Block * blocks = nullptr;
	int blockSize = 0;

    do {
		currentDir = fileSystem.pwd();
        std::cout << user << ":" << currentDir << "$ ";
        getline(std::cin, userCommand);				

        int nrOfCommands = parseCommandString(userCommand, commandArr);
        if (nrOfCommands > 0) {

            int cIndex = findCommand(commandArr[0]);
	        switch (cIndex)
	        {
			case 0: //quit
				bRun = quit();                
				delete[] blocks;
                break;
            case 1: // format
				fileSystem.formatSystem();
                break;
            case 2: // ls
                std::cout << "Listing directory" << std::endl;						
				std::cout << fileSystem.ls();
                break;
            case 3: // create
				std::cout << "Enter Data: ";
				fileSystem.createFile(commandArr[1], user);
                break;
            case 4: // cat
				if (blocks != nullptr)
					delete[] blocks;
				blocks = fileSystem.readFile(user, commandArr[1], blockSize);
				for (size_t i = 0; i < blockSize; i++)
				{
					std::cout << blocks[i].toString();
				}
				std::cout << std::endl;				
                break;
            case 5: // createImage
				fileSystem.saveFileSystem(commandArr[1].data());
                break;
            case 6: // restoreImage
				fileSystem.restoreFileSystem(commandArr[1].data());
                break;
            case 7: // rm
				fileSystem.rm(commandArr[1], user);
                break;
            case 8: // cp
				fileSystem.createCopyFile(commandArr[1], commandArr[2], user);
                break;
            case 9: // append
				fileSystem.append(commandArr[1], commandArr[2], user);
                break;
            case 10: // mv
				fileSystem.mv(commandArr[1], commandArr[2], user);
                break;
            case 11: // mkdir
				fileSystem.mkdir(commandArr[1]);
                break;
            case 12: // cd
				fileSystem.cd(commandArr[1]);
                break;
            case 13: // pwd
				std::cout << fileSystem.pwd() << std::endl;
                break;
            case 14: // help
                std::cout << help() << std::endl;
                break;
            default:
                std::cout << "Unknown command: " << commandArr[0] << std::endl;
            }
        }
    } while (bRun == true);

	

    return 0;
}

int parseCommandString(const std::string &userCommand, std::string strArr[]) {
    std::stringstream ssin(userCommand);
    int counter = 0;
    while (ssin.good() && counter < MAXCOMMANDS) {
        ssin >> strArr[counter];
        counter++;
    }
    if (strArr[0] == "") {
        counter = 0;
    }
    return counter;
}
int findCommand(std::string &command) {
    int index = -1;
    for (int i = 0; i < NUMAVAILABLECOMMANDS && index == -1; ++i) {
        if (command == availableCommands[i]) {
            index = i;
        }
    }
    return index;
}

bool quit() {
	std::cout << "Exiting\n";
	return false;
}

std::string help() {
    std::string helpStr;
    helpStr += "OSD Disk Tool .oO Help Screen Oo.\n";
    helpStr += "-----------------------------------------------------------------------------------\n" ;
    helpStr += "* quit:                             Quit OSD Disk Tool\n";
    helpStr += "* format;                           Formats disk\n";
    helpStr += "* ls     <path>:                    Lists contents of <path>.\n";
    helpStr += "* create <path>:                    Creates a file and stores contents in <path>\n";
    helpStr += "* cat    <path>:                    Dumps contents of <file>.\n";
    helpStr += "* createImage  <real-file>:         Saves disk to <real-file>\n";
    helpStr += "* restoreImage <real-file>:         Reads <real-file> onto disk\n";
    helpStr += "* rm     <file>:                    Removes <file>\n";
    helpStr += "* cp     <source> <destination>:    Copy <source> to <destination>\n";
    helpStr += "* append <source> <destination>:    Appends contents of <source> to <destination>\n";
    helpStr += "* mv     <old-file> <new-file>:     Renames <old-file> to <new-file>\n";
    helpStr += "* mkdir  <directory>:               Creates a new directory called <directory>\n";
    helpStr += "* cd     <directory>:               Changes current working directory to <directory>\n";
    helpStr += "* pwd:                              Get current working directory\n";
    helpStr += "* help:                             Prints this help screen\n";
    return helpStr;
}

/* Insert code for your shell functions and call them from the switch-case */
