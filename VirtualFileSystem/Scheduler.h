#pragma once
#include "Process.h"
#include <queue>
#include "ProgramFile.h"

class Scheduler
{
public:
	Scheduler(int mem = -1, int burst = -1);

	void run();
	void tickIOJobs();
	void step( int amount );

	void setMemory( int amount );
	void setBurst( int amount );

	int getMemory();
	int getBurst();

	void addProcess( ProgramFile* program );
	void finishProcess(const std::shared_ptr<Process>& process);

	void printRunningQueue();
	void printWaitingQueue();
	void printFinishedQueue();
	void printCurrentJob();

	void printSystemUpdate();

private:
	void tickSystem();

	int memoryLimit;
	int memoryUsage = 0;

	int remainingBurst;
	int burstTime;

	int currentTime = 0;

	std::queue<std::shared_ptr<Process>> runningJobs;
	std::queue<std::shared_ptr<Process>> waitingOnIOJobs;
	std::queue<std::shared_ptr<Process>> finishedJobs;

	std::shared_ptr<Process> currentProcess = nullptr;
};
