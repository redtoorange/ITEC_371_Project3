#pragma once
#include "Process.h"
#include <queue>
#include "ProgramFile.h"

class Scheduler
{
public:
	Scheduler(int mem = -1, int burst = -1);

	void run();
	void step( int amount );

	void setMemory( int amount );
	void setBurst( int amount );

	int getMemory();
	int getBurst();

	void addProcess( ProgramFile* program );

private:
	int memoryLimit;
	int memoryUsage = 0;
	int burstTime;

	int currentTime = 0;

	std::queue<std::shared_ptr<Process>> runningJobs;
	std::queue<std::shared_ptr<Process>> waitingJobs;
	std::queue<std::shared_ptr<Process>> finishedJobs;

	std::shared_ptr<Process> currentProcess = nullptr;
};
