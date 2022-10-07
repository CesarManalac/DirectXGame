#pragma once
#include <iostream>
#include <chrono>
#include <ctime>

class Window;
using namespace std;
class EngineTime
{
public:
	static void initialize();
	static double getDeltaTime();
private:
	EngineTime();
	~EngineTime();
	EngineTime(EngineTime const&) {};
	EngineTime& operator=(EngineTime const&) {};

	static EngineTime* sharedInstance;

	chrono::system_clock::time_point start;
	chrono::system_clock::time_point end;

	double deltaTime = 0.0;

	static void LogFrameStart();
	static void LogFrameEnd();

	friend class Window;

};

