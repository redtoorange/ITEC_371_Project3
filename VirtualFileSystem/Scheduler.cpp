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

	std::cout << "Advancing the system until all jobs finished\n";

	while( currentProcess || !runningJobs.empty() || !waitingOnIOJobs.empty())
	{
		tickSystem();
	}

	printSystemUpdate();
}


void Scheduler::tickSystem()
{
	if( !currentProcess || remainingBurst == 0)
	{
		if( currentProcess )
			runningJobs.push( currentProcess );

		if( !runningJobs.empty() )
		{
			currentProcess = runningJobs.front();
			runningJobs.pop();
			remainingBurst = burstTime;

			printSystemUpdate();
		}
		else if(!waitingOnIOJobs.empty())
		{
			std::cout << "No processes to run, waiting on IO.\n";
		}
		else
		{
			std::cout << "All queues are empty.\n";
			return;
		}
	}


	// Find a process
	if( currentProcess )
	{
		currentProcess->tickMain( currentTime );
	}

	// Run that process
	tickIOJobs();

	if (currentProcess && currentProcess->shouldSleepForIO())
	{
		waitingOnIOJobs.push( currentProcess );
		currentProcess = nullptr;
	}

	// If they are done, remove to the running
	if( currentProcess && currentProcess->isFinished())
	{
		finishProcess( currentProcess );
		currentProcess = nullptr;
	}


	std::queue<std::shared_ptr<Process>> tempJobs;
	while( !waitingOnIOJobs.empty() )
	{
		auto j = waitingOnIOJobs.front();
		waitingOnIOJobs.pop();

		if( j->shouldWakeFromIO() )
		{
			runningJobs.push(j);
		}
		else
		{
			tempJobs.push(j);
		}
	}
	waitingOnIOJobs = tempJobs;

	currentTime++;
	remainingBurst--;
}

void Scheduler::tickIOJobs()
{
	// Step all IO processes
	std::queue<std::shared_ptr<Process>> tempJobs;
	while( !waitingOnIOJobs.empty() )
	{
		auto j = waitingOnIOJobs.front();
		waitingOnIOJobs.pop();

		j->tickIO();
		tempJobs.push(j);
	}
	waitingOnIOJobs = tempJobs;
}

void Scheduler::step(int amount)
{
	if( burstTime <= 0 )
	{
		std::cout << "Burst Time must be configured and greater than 0 before running.\n";
		return;
	}

	std::cout << "Advancing the system for " << amount << " units or until all jobs finished\n";

	while( amount > 0 && (currentProcess || !runningJobs.empty() || !waitingOnIOJobs.empty()) )
	{
		tickSystem();
		amount--;
	}

	std::cout << "System state at the end of stepping:\n";
	printSystemUpdate();
}


void Scheduler::printCurrentJob()
{
	if( currentProcess )
		std::cout << "Running job " << currentProcess->getData() << "\n";
	else
		std::cout << "Running job is empty\n";
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
	{
		burstTime = amount;
		remainingBurst = burstTime;
	}
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
		memoryUsage += program->memory_requirements();
		runningJobs.push( std::make_shared<Process>(program, currentTime));
		
		std::cout << program->getFileName() << " has been added to scheduler.\n";
	}
	else
	{
		std::cout << program->getFileName() << " cannot be started, not enough memory.\n";
	}
}

void Scheduler::finishProcess( const std::shared_ptr<Process>& process)
{
	memoryUsage -= process->getMemoryRequired();
	finishedJobs.push(process);
}


void Scheduler::printRunningQueue()
{
	if( runningJobs.empty() )
	{
		std::cout << "The queue is empty\n";
		return;
	}
		

	std::cout << "The queue is:\n";
	int count = 1;

	std::queue<std::shared_ptr<Process>> tempJobs;
	while( !runningJobs.empty() )
	{
		auto j = runningJobs.front();
		runningJobs.pop();

		std::cout << "\tPosition " << count++ << ": job " << j->getData() << std::endl;
		tempJobs.push(j);
	}
	runningJobs = tempJobs;
}

void Scheduler::printWaitingQueue()
{
	if( waitingOnIOJobs.empty() ) return;

	std::queue<std::shared_ptr<Process>> tempJobs;
	while( !waitingOnIOJobs.empty() )
	{
		auto j = waitingOnIOJobs.front();
		waitingOnIOJobs.pop();

		std::cout << "The process " << j->getName() << " is obtaining IO and will be back in " << j->getRemainingIOTime() << " unit.\n";
		tempJobs.push(j);
	}
	waitingOnIOJobs = tempJobs;
}

void Scheduler::printFinishedQueue()
{
	if( finishedJobs.empty() ) return;

	std::cout << "Finished Jobs are: \n";

	std::queue<std::shared_ptr<Process>> tempJobs;
	while( !finishedJobs.empty() )
	{
		auto j = finishedJobs.front();
		finishedJobs.pop();

		std::cout << "\t" << j->getFinishedData() << std::endl;
		tempJobs.push(j);
	}
	finishedJobs = tempJobs;
}


void Scheduler::printSystemUpdate()
{
	std::cout << "Current time <" << currentTime << ">\n";

	printCurrentJob();		
	printRunningQueue();
	printWaitingQueue();
	printFinishedQueue();
}
