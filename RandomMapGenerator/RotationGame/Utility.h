#ifndef UTILITY_H
#define UTILITY_H

#include <iostream>
#include <SDL.h>
#include <random>
#include <locale>

using namespace std;

struct Utility
{
	static int RandomNumberGenerator(const int min, const int max);
};

#endif