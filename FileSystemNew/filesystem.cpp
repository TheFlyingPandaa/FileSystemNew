#include "filesystem.h"

FileSystem::FileSystem() {
	mMemblockDevice = MemBlockDevice();
}

FileSystem::~FileSystem() {

}

void FileSystem::createFile(const std::string & fileName, const std::string &data)
{
	if (fileName.size() < 1)
	{

		//Om vi ska ha C++;) så ska detta tasbort
		if (data.size() < 512)
		{

			int amount = data.size();
			std::string newString = "sarkrrpxgmvpmtqeutzoealpqihtnpjpjypwotltkimawhwrchhuayrytavvsrdbrgxvhyupywlcsdlmljiljbsanqhwbddkiyjkugakeqkpipodzspuripwiogudgpuhzkhniiavrkwvjqnrpgavzbquyhiwcvitywicivuvjbtpbdbzqnizzxrwadmmsgmmunymdzdfulhcffvwnsmijrouiafntujcirjkwelasbeumiyzthsqnovlgpcbchxrpviogjqfemmhnqnweglbuenyfgwggpnxtdvwkrorexggqqqpnzmxvkcnvzijafdmaerfsqidytdtklgxudsvovkghpalvdmajhcqaelrssidwtotixipjxiuyparxehxjdmeiozdtzcmkocjemalywwwbjchilespgwgdlmthcibyfqqvxoaxbnxhqkrsmnrmrkryktelrzxphjzhktoegbnitwlvvnczusgzoivzcrihekanqasuuqptylfztm";
			
			
			for (int i = 0; i < data.size(); i++)
			{
				newString[i] = data[i];
			}
			for (int i = amount; i < 512; i++)
			{
				newString[i] = 0;
			}

			
			mMemblockDevice.writeBlock(0, newString);
			std::cout << "DEBUG_MSG: it finnished" << std::endl;
		}
		else
		{
			std::string firstBlock = "null";
			firstBlock.resize(512);


		}
	}
}

Block FileSystem::readFile()
{
	Block block = mMemblockDevice.readBlock(0);
	//std::cout << block.toString() << std::endl;

	return block;

}

void FileSystem::formatSystem()
{
		mMemblockDevice.reset();
}


/* Please insert your code */