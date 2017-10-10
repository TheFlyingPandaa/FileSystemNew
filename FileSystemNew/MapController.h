#ifndef MapC_H
#define MapC_H
#include "Map.h"
#include <iostream>

class MapController
{
private:
	Map * root;
	Map * current;

public:
	MapController();
	~MapController();

	std::string getMaps() const;

	void createMap(const std::string & name);
	void removeMap(const std::string & name);

	void goToMap(const std::string & name);
};

#endif // !MapC_H