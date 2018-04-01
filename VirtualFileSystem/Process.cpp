#include "Process.h"
#include <sstream>

Process::Process(ProgramFile* program, int timestarted) : timeStarted(timestarted)
{

	// Populate the process data
	memoryRequired = program->memory_requirements();
	timeRequired = program->time_requirements();

	timeToIO = program->time_to_do_io();
	amountOfIO = program->amout_of_io_time();

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
