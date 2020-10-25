#include "Utility.h"

using namespace std;

/*
RandomNumberGenerator(int min, int max)
Generates a random number between the min and max

Parameters:
int min - Minimum number
int max - Maximum number

Returns:
int
*/
int Utility::RandomNumberGenerator(const int min, const int max)
{
	std::random_device dev;
	std::mt19937 rng(dev());
	std::uniform_int_distribution<int> randomNumber(min, max);

	return randomNumber(rng);
}