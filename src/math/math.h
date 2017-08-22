#pragma once

namespace math 
{
	template<typename T>
	void clamp(T& value, T min, T max) {
		if (value < min) {
			value = min;
			return;
		}
		if (value > max) {
			value = max;
		}
	};

	template<typename T>
	void lerp(T& value, T target, float t) {
		value += (target - value)*t;
	}

	//desc : Init randomizer. needs to be called before any Random operation
	void initRand();

	//desc : returns an integer between min & max 
	//TODO: Use better Random generation
	int NextInt(int min, int max);

	// desc :return a 1 dimension array index from 3 dimension array indexes
	// input : coordinates x,y,z of 3D array, 'width' and 'height' of array 
	int from3D_indexing_to_1d(int x, int y, int z, int width, int height);

	//desc: convert angle from degree to radians
	double toRad(double angleInDegrees);

}