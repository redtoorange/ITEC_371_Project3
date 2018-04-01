/*
 *	Andrew McGuiness
 *	ITEC 371 - Project 3
 *	4/1/2018
*/

#include "Process.h"
#include <sstream>

Process::Process(ProgramFile* program, int timestarted) : timeStarted(timestarted)
{

	// Populate the process data
	memoryRequired = program->getMemoryRequirements();
	timeRequired = program->getTimeRequirements();

	timeToIO = program->getTimeToDoIO();
	amountOfIO = program->getAmoutOfIO();

	name = program->getFileName();

	unitsRun = 0;
}


bool Process::isFinished()
{
	return unitsRun == timeRequired;
}

void Process::tickMain( int currentTime )
{
	unitsRun++;

	if( isFinished() )
		timeFinished = currentTime + 1;
}

void Process::tickIO()
{
	amountOfIO--;
}

bool Process::shouldSleepForIO()
{
	return unitsRun == timeToIO;
}

bool Process::shouldWakeFromIO()
{
	return amountOfIO == 0;
}

int Process::getMemoryRequired()
{
	return memoryRequired;
}

int Process::getTimeRequired()
{
	return timeRequired;
}

int Process::getTimeRemaining()
{
	return timeRequired - unitsRun;
}


std::string Process::getData()
{
	std::stringstream ss;

	ss << name << " has " << getTimeRemaining() << " time left and is using " << getMemoryRequired() << " memory resources.";

	return ss.str();
}

int Process::getRemainingIOTime()
{
	return amountOfIO;
}

std::string Process::getFinishedData()
{
	std::stringstream ss;

	ss << name << " " << getTimeRequired() << " " << (timeFinished - timeStarted);

	return ss.str();
}


std::string Process::getName()
{
	return name;
}
