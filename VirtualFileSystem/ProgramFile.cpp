/*
 *	Andrew McGuiness
 *	ITEC 371 - Project 2
 *	3/2/2018
*/

#include "ProgramFile.h"
#include <iostream>
#include <string>

std::shared_ptr<ProgramFile> ProgramFile::makeProgramFile( const std::string& name, int time, int mem, int doesIO, int timeIO, int amountIO  )
{
	// Check the name of the file
	std::string n = name;
	if( !validName(&n) )
	{
		std::cout << "Invalid program name!" << std::endl;
		return nullptr;
	}
	else
	{
		// Send back out new Prog
		return std::make_shared<ProgramFile>(n, time, mem, doesIO, timeIO, amountIO);
	}
}

ProgramFile::ProgramFile( const std::string& name, int timeReq, int memReq, int doesIO, int timeIO, int amountIO)
{
	fileName = name;

	timeRequirements = timeReq;
	memoryRequirements = memReq;

	needsIO = doesIO;
	timeToDoIO = timeIO;
	amoutOfIoTime = amountIO;
}

bool ProgramFile::validName( std::string* name)
{
	// The system will accept just a name as the name, or if there is an extension

	// Strip the extension
	auto back = name->end();
	if( *--back == 'p' && *--back == '.')
	{
		name->erase(back, name->end());
	}

	// Check the length
	if( name->length() > 8)
	{
		std::cout << "File names cannot exceed 8 characters.\n";
		return false;
	}
		
	// Verify all the characters are valid
	auto iter = name->begin();
	for(;iter != name->end(); ++iter)
	{
		char c = *iter;
		if( !((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z') ||((c >= '0' && c <= '9')) ) )
		{
			std::cout << "File names must be alpha-numeric.\n";
			return false;
		}
	}

	return true;
}


void ProgramFile::printData(int tabs)
{
	// Make us some sweet sweet tabs
	std::string t;
	for( int i = 0; i < tabs; i++)
		t += "\t";

	std::cout << t << fileName << ".p" << std::endl;
	std::cout << t << "\t" << "Time Requirement: " << timeRequirements << std::endl;
	std::cout << t << "\t" << "Mem Requirement : " << memoryRequirements << std::endl;

	if( needsIO)
	{
		std::cout << t << "\t" << "IO Time   : " << timeToDoIO << std::endl;
		std::cout << t << "\t" << "IO Amount : " << amoutOfIoTime << std::endl;
	}
	

}


void ProgramFile::writeToFile(std::ofstream& stream)
{
	stream << fileName;
	for( int i = fileName.length(); i < 8; i++)
	{
		stream << '\0';
	}
	stream << ".p";
	stream << '\0';

	// Ugly, but it writes the ints to the file as char arrays
	stream.write((char*)&timeRequirements, sizeof(timeRequirements));
	stream.write((char*)&memoryRequirements, sizeof(memoryRequirements));

	stream.write((char*)&needsIO, sizeof(needsIO));
	stream.write((char*)&timeToDoIO, sizeof(timeToDoIO));
	stream.write((char*)&amoutOfIoTime, sizeof(amoutOfIoTime));
	
}

int ProgramFile::memory_requirements() const
{
	return memoryRequirements;
}

int ProgramFile::time_requirements() const
{
	return timeRequirements;
}

int ProgramFile::needs_io() const
{
	return needsIO;
}

int ProgramFile::time_to_do_io() const
{
	return timeToDoIO;
}

int ProgramFile::amout_of_io_time() const
{
	return amoutOfIoTime;
}


std::shared_ptr<ProgramFile> ProgramFile::inflateProgramFile(std::string& name, std::ifstream& stream)
{
	std::string n = name;
	validName(&n);

	// Load process data
	int t;
	int m;

	// Load IO Data
	int doesIO;
	int timeIO;
	int amountIO;
	
	
	// Again, ugly, but it reads the ints back from char arrays
	stream.read((char*)&t, sizeof(t));
	stream.read((char*)&m, sizeof(m));

	stream.read((char*)&doesIO, sizeof(doesIO));
	stream.read((char*)&timeIO, sizeof(timeIO));
	stream.read((char*)&amountIO, sizeof(amountIO));

	return std::make_shared<ProgramFile>(n, t, m, doesIO, timeIO, amountIO);
}
