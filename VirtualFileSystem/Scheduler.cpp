#include "Scheduler.h"
#include <ostream>
#include <iostream>


Scheduler::Scheduler(int mem, int burst)
	: memoryLimit(mem), burstTime(burst), currentTime(0)
{
}

void Scheduler::run()
{
	if( burstTime <= 0 )
	{
		std::cout << "Burst Time must be configured and greater than 0 before running.\n";
		return;
	}

	std::cout << "Scheduler is running" << std::endl;

	while( !runningJobs.empty() && !waitingJobs.empty())
	{
		step(1);
	}
}

void Scheduler::step(int amount)
{
	if( burstTime <= 0 )
	{
		std::cout << "Burst Time must be configured and greater than 0 before running.\n";
		return;
	}
		
	if( !currentProcess )
	{
		if( !runningJobs.empty() )
		{
			currentProcess = runningJobs.front();
			runningJobs.pop();
		}
	}

	if( currentProcess )
		std::cout << currentProcess->getData() << std::endl;
	else
		std::cout << "No processes to run." << std::endl;

	int remainingBurst = burstTime;
	
	// Find the next process
	while( remainingBurst > 0)
	{
		
	}


	// Run that process

	// Step all IO processes

	// If they are done, remove to the running
}

void Scheduler::setMemory(int amount)
{
	if( amount >= 0)
		memoryLimit = amount;
	else
		std::cout << "Error: System cannot have negative memory...\n";
}

void Scheduler::setBurst(int amount)
{
	if( amount >= 0)
		burstTime = amount;
	else
		std::cout << "Error: System cannot have negative burst time...\n";
}

int Scheduler::getMemory()
{
	return memoryLimit;
}

int Scheduler::getBurst()
{
	return burstTime;
}

void Scheduler::addProcess(ProgramFile* program)
{
	if( program->memory_requirements() <= (memoryLimit - memoryUsage))
	{

		runningJobs.push( std::make_shared<Process>(program));
		std::cout << program->getFileName() << " has been added to scheduler.\n";
	}
	else
	{
		std::cout << program->getFileName() << " cannot be started, not enough memory.\n";
	}
}
