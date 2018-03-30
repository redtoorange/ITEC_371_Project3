#pragma once
#include "ProgramFile.h"

class Process
{
public:
	Process( ProgramFile* program );
	
	int getMemoryRequired();
	int getTimeRequired();
	int getTimeRemaining();

	bool shouldSleepForIO();
	bool shouldWakeFromIO();

	void tickMain();
	void tickIO();

	bool isFinished();
	std::string getData();

private:
	std::string name;

	int unitsRun;

	int memoryRequired;
	int timeRequired;

	int timeToIO;
	int amountOfIO;
};
