/*
 *	Andrew McGuiness
 *	ITEC 371 - Project 2
 *	3/2/2018
*/

#ifndef PROGRAM_FILE_H
#define PROGRAM_FILE_H

#include "File.h"
#include <memory>

/*!
*	\brief NOT USED!!!!
*/
class ProgramFile : public File
{
public:
	//! Create a new ProgramFile given a filename, user will be prompted for input
	static std::shared_ptr<ProgramFile> makeProgramFile( const std::string& name, int time, int mem, int doesIO, int timeIO, int amountIO );
	
	//! Inflate a stored ProgramFile back into a full file
	static std::shared_ptr<ProgramFile> inflateProgramFile( std::string& name, std::ifstream& stream );

	//! Ensure that the supplied name is valid
	static bool validName( std::string* name);

	//! Should NOT be used outside of the class
	ProgramFile(const std::string& name, int timeReq, int memReq, int doesIO, int timeIO, int amountIO);

	//! Formatted data printer
	void printData(int tabs) override;
	
	//! Write the program file out to a stream
	void writeToFile(std::ofstream& stream) override;


	int memory_requirements() const;
	int time_requirements() const;
	int needs_io() const;
	int time_to_do_io() const;
	int amout_of_io_time() const;

private:
//	int cpuRequirements;
	int memoryRequirements;
	int timeRequirements;

	int needsIO;
	int timeToDoIO;
	int amoutOfIoTime;
};

#endif