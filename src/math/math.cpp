#include "math.h"
#include <time.h>
#include <iostream>
namespace math {
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
}