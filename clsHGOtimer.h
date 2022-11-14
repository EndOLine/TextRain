#pragma once
/*
Program: clsHGOtimer.h
Description: class to produce timing in code
		

Notes:
	Based on https://www.youtube.com/watch?v=oEx5vGNFrLk by The Cherno
	std::chrono::high_resolution_clock::now()	// current time
	std::chrono::duration<float> duration = end - start;	// duration example
	if "LOGSTREAM" macro from clsHGOlog is available it will use that instead of cout
	std::this_thread::sleep_for(std::chrono::milliseconds(10000));	// sleep thread
	clsHGOtimer time(__func__);	// example for setting output to current function name;
log:
	20211103: created
*/
#ifndef CLSHGOTIMER
#define CLSHGOTIMER
#include <iostream>
#include <chrono>
#include <string>

class clsHGOtimer{
public:
	std::chrono::time_point<std::chrono::steady_clock> StartTime, EndTime;
	std::chrono::duration<float> Duration;
	std::string TimerName;

public:
	clsHGOtimer() {
		StartTime = std::chrono::high_resolution_clock::now();
	}
	clsHGOtimer(const std::string Name) {
		TimerName = Name;
		StartTime = std::chrono::high_resolution_clock::now();
	}

	~clsHGOtimer() {
		EndTime = std::chrono::high_resolution_clock::now();
		Duration = EndTime - StartTime;
		float ms = Duration.count() * 1000.0f;
#ifdef LOGSTREAM
		LOGSTREAM("Elapased Time(" << TimerName << "): " << ms << "ms ");
#else
#ifdef _DEBUG
		OutputDebugString("Elapased Time(");
		OutputDebugString(TimerName.c_str());
		OutputDebugString("): ");
		OutputDebugString(std::to_string(ms).c_str());
		OutputDebugString("ms \n");
#endif
		std::cout << "Elapased Time(" << TimerName << "): " << ms << "ms " << std::endl;
#endif
	}
};
#endif

