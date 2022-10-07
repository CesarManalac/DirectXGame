#include "EngineTime.h"

EngineTime* EngineTime::sharedInstance = NULL;

void EngineTime::initialize()
{
    sharedInstance = new EngineTime();
}

double EngineTime::getDeltaTime()
{
    return sharedInstance->deltaTime;
}

EngineTime::EngineTime()
{
}

EngineTime::~EngineTime()
{
}

void EngineTime::LogFrameStart()
{
    sharedInstance->start = chrono::system_clock::now();
}

void EngineTime::LogFrameEnd()
{
    sharedInstance->end = chrono::system_clock::now();
    chrono::duration<double> elapsed_seconds = sharedInstance->end - sharedInstance->start;

    sharedInstance->deltaTime = elapsed_seconds.count();
}
