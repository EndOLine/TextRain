/********************************************************************
Prog: clsRNG.cpp
Desc: Better random number generator than the builtin
Library:
Log : 221113 - created

********************************************************************/
#include "clsRNG.h"


uint32_t clsRNG::lcg_parkmiller(uint32_t* state) {
	uint64_t product = (uint64_t)*state * 48271;
	uint32_t x = (product & 0x7fffffff) + (product >> 31);

	x = (x & 0x7fffffff) + (x >> 31);
	return *state = x;
};
uint32_t clsRNG::RNG(const uint32_t Seed) {
	if (Seed != 0) {
		uiSeed = Seed;
		return uiSeed;
	} else {
		return lcg_parkmiller(&uiSeed);
	};
};