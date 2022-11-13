#pragma once
/********************************************************************
Prog: clsRNG.h
Desc: Better random number generator than the builtin
Lehmer RNG; parkmiller modification avoiding 64bit division
Configuration Properties | General | Character Set = Use Multi-Byte Character Set
Library: 
Log : 221113 - created
	  
********************************************************************/
#ifndef CLSRNG_H
#define CLSRNG_H
#define WIN32_LEAN_AND_MEAN	
#include <stdint.h>

class clsRNG {
private:
	uint32_t uiSeed = 1;	// greater then 0 and less than 0x7fffffff
public:
	uint32_t RNG(const uint32_t Seed=0);
private:
	uint32_t lcg_parkmiller(uint32_t* state);
};

#endif
