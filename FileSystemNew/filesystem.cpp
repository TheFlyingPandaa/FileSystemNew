#include "filesystem.h"

FileSystem::FileSystem() {
	mMemblockDevice = MemBlockDevice();
	mapController = new MapController(250);

	openBlocks = std::vector<int>(250, 0); //250 amount of blocks
}

FileSystem::~FileSystem() {
	
	delete mapController;
}

void FileSystem::createFile(const std::string & fileName, const std::string user)
{
	int * blockArray = nullptr;

	//Pretty please use this when adding files :D



	//std::string data = "test";
	//data.resize(514, 'a');
	std::string data;
	getline(std::cin, data);
	//std::cin.ignore();
	if (fileName.size() > 0)
	{

		//Om vi ska ha C++;) så ska detta tasbort "typ inte"
		if (data.size() <= 512)
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

			
			mapController->addFile(fileName, 1, blockArray, data.size() * sizeof(char), user);
			mMemblockDevice.writeBlock(blockArray[0], newString, user);			
			delete[] blockArray;
		}
		else
		{

			int amountBlocks = data.size() / 512;
			if (data.size() % 512 != 0)
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

			//TODO:: Fix this: probs fixed

			for (int i = 0; i < amountBlocks -1; i++) {
				for (int j = 0; j < 512; j++)
				{
					blocks[i][j] = data[j + (512 * i)];
				}
			}
			int tempSize = data.size() - (amountBlocks - 1) * 512;
			for (int i = 0; i < tempSize; i++ )
			{
				blocks[amountBlocks -1][i] = data[i + (512 * (amountBlocks - 1))];
			}

			mapController->addFile(fileName, amountBlocks, blockArray, data.size() * sizeof(char), user);
			
			for (int i = 0; i < amountBlocks; i++) {
				mMemblockDevice.writeBlock(blockArray[i], blocks[i], user);
			}
			delete[] blockArray;
			delete[] blocks;

		}
	}
}

void FileSystem::createFileNoInp(const std::string & fileName, const std::string & data, const std::string user)
{

	int * blockArray = nullptr;

	if (data.size() <= 512)
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


		mapController->addFile(fileName, 1, blockArray, data.size() * sizeof(char), user);
		mMemblockDevice.writeBlock(blockArray[0], newString, user);
		delete[] blockArray;
	}
	else
	{

		int amountBlocks = data.size() / 512;
		if (data.size() % 512 != 0)
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

		//TODO:: Fix this: probs fixed

		for (int i = 0; i < amountBlocks - 1; i++) {
			for (int j = 0; j < 512; j++)
			{
				blocks[i][j] = data[j + (512 * i)];
			}
		}
		int tempSize = data.size() - (amountBlocks - 1) * 512;
		for (int i = 0; i < tempSize; i++)
		{
			blocks[amountBlocks - 1][i] = data[i + (512 * (amountBlocks - 1))];
		}

		mapController->addFile(fileName, amountBlocks, blockArray, data.size() * sizeof(char), user);

		for (int i = 0; i < amountBlocks; i++) {
			mMemblockDevice.writeBlock(blockArray[i], blocks[i], user);
		}
		delete[] blockArray;
		delete[] blocks;

	}

}

void FileSystem::createCopyFile(const std::string & oldName, const std::string & newFile, const std::string & user)
{
	int * blockArray = nullptr;

	std::string filePath = mapController->pwd();
	std::string removedRoot1 = "";
	for (int i = 4; i < filePath.size(); i++)
	{
		removedRoot1 += filePath[i];
	}
	for (int i = 0; i < oldName.size(); i++)
	{
		removedRoot1 += oldName[i];
	}
	
	File * file = mapController->getFile(removedRoot1);
	Block * block = new Block[file->nrOfBlocks];
	

	for (int i = 0; i < file->nrOfBlocks; i++)
	{
		block[i] = mMemblockDevice.readBlock(file->fileBlocks[i]);
	}

	mapController->addFile(newFile, file->nrOfBlocks, blockArray, file->bytes, user);


	for (int i = 0; i < file->nrOfBlocks; i++)
	{
		mMemblockDevice.writeBlock(blockArray[i], block[i].toString(), user);
	}
	
	delete[] blockArray;
	delete[] block;

}

Block * FileSystem::readFile(const std::string user, const std::string & fileName, int& size)
{
	std::cout << mMemblockDevice.getOwner(0) << std::endl;
	std::string filePath = mapController->pwd();
	std::string removedRoot = "";
	for (int i = 4; i < filePath.size(); i++)
	{
		removedRoot += filePath[i];
	}
	for (int i = 0; i < fileName.size(); i++)
	{
		removedRoot += fileName[i];
	}
	File * f = mapController->getFile(removedRoot);
	Block * blocks = new Block[f->nrOfBlocks];
	size = f->nrOfBlocks;
	for (int i = 0; i < f->nrOfBlocks; i++)
	{
		blocks[i] = mMemblockDevice.readBlock(f->fileBlocks[i]);
	}
	return blocks;

}

void FileSystem::formatSystem()
{

	mMemblockDevice.reset();
	this->mapController->~MapController(); //Ja detta ser ut som en "Ghetto lösning"
	this->mapController = new MapController(250); //Men det ska var en legit väg att resata ett objekt

}

void FileSystem::removeFile()
{
	//TODO:: insert way of removing in tree

	mMemblockDevice.singleReset(0);

	//Insert way of removing in tree here


}

int FileSystem::amountOfBlocksFree() const
{
	return mMemblockDevice.spaceLeft();
}

void FileSystem::saveFileSystem(const char * path)
{
	//TODO:: Implement filesystem tree save func
	mapController->save(path);
	mMemblockDevice.saveBlocks(path);
}

void FileSystem::restoreFileSystem(const char * path)
{
	//TODO:: Implement filesystem tree read func
	mapController->load(path);
	mMemblockDevice.readSavedBlocks(path);
}





/* Please insert your code */

//-----------------------------------	Map Controller Functions

void FileSystem::mkdir(const std::string & mapName)
{
	mapController->createMap(mapName);
}

void FileSystem::rm(const std::string & mapName, const std::string & user)
{
	mapController->rm(mapName, user);
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

void FileSystem::mv(const std::string & fileName, const std::string & destFile, const std::string & user)
{
	if (fileName != destFile)
	{
		createCopyFile(fileName, destFile, user);

		mapController->rm(fileName, user);
	}
	

}

void FileSystem::append(const std::string & filename, const std::string & destFile, const std::string & user)
{
	if (filename != destFile)
	{
		int * blockArray = nullptr;
		
		std::string filePath = mapController->pwd();
		std::string removedRoot1 = "";
		std::string removedRoot2 = "";
		for (int i = 4; i < filePath.size(); i++)
		{
			removedRoot1 += filePath[i];
		}
		removedRoot2 = removedRoot1;
		for (int i = 0; i < filename.size(); i++)
		{
			removedRoot1 += filename[i];
		}
		for (int i = 0; i < destFile.size(); i++)
		{
			removedRoot2 += destFile[i];
		}


		File * file1 = mapController->getFile(removedRoot1);
		File * file2 = mapController->getFile(removedRoot2);
		int f1 = file1->nrOfBlocks;
		int f2 = file2->nrOfBlocks;
		Block * blocks1 = new Block[file1->nrOfBlocks];
		Block * blocks2 = new Block[file2->nrOfBlocks];
		
		for (int i = 0; i < file1->nrOfBlocks; i++)
		{
			blocks1[i] = mMemblockDevice.readBlock(file1->fileBlocks[i]);
			
		}
		for (int i = 0; i < file2->nrOfBlocks; i++)
		{
			blocks2[i] = mMemblockDevice.readBlock(file2->fileBlocks[i]);
		}

		std::string newString = std::string(file1->bytes + file2->bytes, 'a');
		std::string * block1 = new std::string[f1];
		for (int i = 0; i < f1; i++)
		{
			block1[i] = blocks1[i].toString();
		}
		std::string * block2 = new std::string[f1];
		for (int i = 0; i < f2; i++)
		{
			block2[i] = blocks2[i].toString();
		}
		if (file1->bytes + file2->bytes < 512)
		{
			for (int i = 0; i < file1->bytes; i++)
			{
				newString[i] = block1[0][i];
			}
			for (int i = 0; i<  file2->bytes; i++)
			{
				newString[i + file1->bytes] = block2[0][i];
			}
		}
		else
		{
			int counter = 0;
			for (int i = 0; i < f1; i++)
			{
				for (int j = 0; j < 512; j++)
				{
					if (counter <= file1->bytes)
					{
						newString[j + (512 * i)] = block1[i][j];
					}
					counter++;
				}
			}
			counter = 0;
			for (int i = 0; i < f2; i++)
			{
				for (int j= 0; j < 512; j++)
				{
					newString[file1->bytes + j + (512 * i)] = block2[i][j];
				}
			}
		}
		mapController->rm(destFile, user);
		
		createFileNoInp(destFile, newString, user);
		
		

		delete[] blockArray;
		delete[] blocks1;
		delete[] blocks2;
		delete[] block1;
		delete[] block2;
	}

}
