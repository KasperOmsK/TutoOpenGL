#include "math.h"
#include <time.h>
#include <iostream>
namespace math {

	#define PI 3.14159265359

	//desc : Init randomizer. needs to be called before any Random operation
	void initRand()
	{
		srand(time(NULL));
	}

	//desc : returns an integer between min & max 
	//TODO: Use better Random generation
	int NextInt(int min, int max)
	{
		return (rand() % (max - min)) + min;
	}
	
	// desc :return a 1 dimension array index from 3 dimension array indexes
	// input : coordinates x,y,z of 3D array, 'width' and 'height' of array 
	int from3D_indexing_to_1d(int x, int y, int z, int width, int height)
	{
		return x + width *(y + height * z);
	}

	//desc: convert angle from degree to radians
	double toRad(double angleInDegree) {
		return angleInDegree * PI / 180.0;
	}

}