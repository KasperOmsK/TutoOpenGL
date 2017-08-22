#include "math.h"
#include <time.h>
#include <iostream>
namespace math {

	#define PI 3.14159265359

	void initRand()
	{
		srand(time(NULL));
	}
	int NextInt(int min, int max)
	{
		return (rand() % (max - min)) + min;
	}
	
	int from3D_indexing_to_1d(int x, int y, int z, int width, int height)
	{
		return x + width *(y + height * z);
	}

	double toRad(double angleInDegree) {
		return angleInDegree * PI / 180.0;
	}

}