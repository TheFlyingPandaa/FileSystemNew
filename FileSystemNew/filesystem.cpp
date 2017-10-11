#include "filesystem.h"

FileSystem::FileSystem() {
	mMemblockDevice = MemBlockDevice();
	mapController = new MapController();
}

FileSystem::~FileSystem() {
	delete mapController;
}

void FileSystem::createFile(const std::string & fileName)
{
	int * blockArray;
	//mapController->addFile(fileName, nrOfBlocks, blockArray, fileSize);
	//Pretty please use this when adding files :D


	//std::string data = "test";
	//data.resize(1024, 'a');
	std::string data;
	getline(std::cin, data);
	//std::cin.ignore();
	if (fileName.size() > 0)
	{

		//Om vi ska ha C++;) s� ska detta tasbort
		if (data.size() < 512)
		{

			int amount = data.size();

			std::string newString = "0";
			newString.resize(512, 0);
			//std::string newString = "sarkrrpxgmvpmtqeutzoealpqihtnpjpjypwotltkimawhwrchhuayrytavvsrdbrgxvhyupywlcsdlmljiljbsanqhwbddkiyjkugakeqkpipodzspuripwiogudgpuhzkhniiavrkwvjqnrpgavzbquyhiwcvitywicivuvjbtpbdbzqnizzxrwadmmsgmmunymdzdfulhcffvwnsmijrouiafntujcirjkwelasbeumiyzthsqnovlgpcbchxrpviogjqfemmhnqnweglbuenyfgwggpnxtdvwkrorexggqqqpnzmxvkcnvzijafdmaerfsqidytdtklgxudsvovkghpalvdmajhcqaelrssidwtotixipjxiuyparxehxjdmeiozdtzcmkocjemalywwwbjchilespgwgdlmthcibyfqqvxoaxbnxhqkrsmnrmrkryktelrzxphjzhktoegbnitwlvvnczusgzoivzcrihekanqasuuqptylfztm";

			for (int i = 0; i < data.size(); i++)
			{
				newString[i] = data[i];
			}
			//for (int i = amount; i < 512; i++)
			//{
			//	newString[i] = 0;
			//}

			
			mMemblockDevice.writeBlock(0, newString);
			std::cout << "DEBUG_MSG: it finnished" << std::endl;
		}
		else
		{

			int amountBlocks = data.size() / 512;
			if (data.size() % 2 != 0)
			{
				amountBlocks++;
			}
			

			std::string * blocks = new std::string[amountBlocks];

			for (int i = 0; i < amountBlocks; i++)
			{
				blocks[i] = "0";
			}
			for (int i = 0; i < amountBlocks; i++) {
				blocks[i].resize(512, 0);
			}

			//TODO:: Fix this

			/*for (int i = 0; i < amountBlocks; i++) {
				for (int j = 0; j < 512; j++)
				{
					blocks[i] = data[j + (512 * i)];
				}
			}*/


			//PSUDO CODE 
			//findEmptyBlocks(amountBlocks);
			//STOP PSUDO
			for (int i = 0; i < amountBlocks; i++) {
				mMemblockDevice.writeBlock(i, blocks[i]);
			}

			delete[] blocks;

		}
	}
}

Block FileSystem::readFile()
{

	Block block = mMemblockDevice.readBlock(0);
	//std::cout << block.toString() << std::endl;
	//block = mMemblockDevice.readBlock(1);
	return block;

}

void FileSystem::formatSystem()
{
	//TODO:: Insert filesytem reset	

	mMemblockDevice.reset();
}

void FileSystem::removeFile()
{
	//TODO:: insert way of removing in tree

	mMemblockDevice.singleReset(0);

	//Insert way of removing in tree here


}



/* Please insert your code */

//-----------------------------------	Map Controller Functions

void FileSystem::mkdir(const std::string & mapName)
{
	mapController->createMap(mapName);
}

void FileSystem::rm(const std::string & mapName)
{
	mapController->removeMap(mapName);
}

void FileSystem::cd(const std::string & mapName)
{
	mapController->goToMap(mapName);
}

std::string FileSystem::pwd()
{
	return mapController->pwd();
}

std::string FileSystem::ls()
{
	return mapController->ls();
}
