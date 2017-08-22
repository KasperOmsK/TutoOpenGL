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
	
	void initRand();

	int NextInt(int min, int max);

	int from3D_indexing_to_1d(int x, int y, int z, int width, int height);

	double toRad(double angleInDegrees);

}