#include <iostream>
#include <cassert>
#include <cstdlib>
#include "elevation_map.h"

int main (int argc, char **argv) {
	std::cout << "Making new elevation map\n";
	ElevationMap *testMap = new ElevationMap(10, 15);
	assert(testMap != 0);
	std::cout << "Passed all assertions\n";

	//Given size of 
}
