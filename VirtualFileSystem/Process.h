#pragma once
#include "ProgramFile.h"

class Process
{
public:
	Process( ProgramFile* program, int timestarted );
	
	int getMemoryRequired();
	int getTimeRequired();
	int getTimeRemaining();
	int getRemainingIOTime();

	bool shouldSleepForIO();
	bool shouldWakeFromIO();

	void tickMain( int currentTime );
	void tickIO();

	bool isFinished();

	std::string getData();
	std::string getFinishedData();
	std::string getName();

private:
	std::string name;

	int unitsRun;

	int memoryRequired;
	int timeRequired;

	int timeToIO;
	int amountOfIO;

	int timeStarted;
	int timeFinished;
};
