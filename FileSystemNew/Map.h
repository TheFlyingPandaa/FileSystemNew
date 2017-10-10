#ifndef Map_h
#define Map_h
#include <string>
//#include <iostream>
#include <vector>
#include <string.h>


struct File
{
	int fileBlock;
	std::string fileName;
};

class Map
{
private:
	std::string mapName;
	Map * root;

	int nFiles;
	int maxFiles;
	File * files;

	int nMaps;
	int maxMaps;	
	std::vector<Map *> vMap;


	template <typename T>
	void expand(T*& arr, int size, int target);

	void init();



public:
	Map();
	Map(const std::string & name, Map * root = nullptr);
	
	~Map();

	std::string getName() const;
	std::string * getFilesNames() const;
	int getFilesSize() const;

	std::vector<Map*> getMaps() const;
	int getMapsSize() const;

	void addFile(const std::string& fileName, int block);
	void addMap(const std::string& mapName);

	void removeMap(const std::string& name);

	bool fileExist(const std::string & name) const;
	bool mapExist(const std::string & name) const;

	int getMapIndex(const std::string & name);
	void removeEverything();

	Map * getRoot() const;
};


template<typename T>
inline void Map::expand(T *& arr, int size, int target)
{

	printf("Map array has been expanded\n");
	T * newArr = new T[target];
	for (size_t i = 0; i < size; i++)
	{
		newArr[i] = arr[i];
	}
	delete[] arr;

	arr = newArr;
}

#endif // !Map_H