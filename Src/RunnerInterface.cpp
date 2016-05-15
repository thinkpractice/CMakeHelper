#include "RunnerInterface.h"
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <ostream>
#include <sstream>
#include <memory>
#include <stdexcept>
#include <support/StringList.h>

RunnerInterface::RunnerInterface()
					: _runnerInterfaceObserver(NULL)
{
}

RunnerInterface::~RunnerInterface()
{
}

void RunnerInterface::SetObserver(RunnerInterfaceObserver* observer)
{
	_runnerInterfaceObserver = observer;
}

void RunnerInterface::Run(BPath& path)
{
	BString command = GetMakeCommand(path, "make -C");
	BString errors = Exec(command.String());
	
	BStringList errorList;
	errors.Split("\n", false, errorList);
	
	for (int i = 0; i < errorList.CountStrings(); i++)
	{
		BString error = errorList.StringAt(i);
		ErrorMessage errorMessage(error);
		_runnerInterfaceObserver->ErrorReceived(errorMessage);
	}
}

void RunnerInterface::Clean(BPath& path)
{
	BString command = GetMakeCommand(path, "make clean -C");
	BString error = Exec(command.String());
	ErrorMessage errorMessage(error);
	_runnerInterfaceObserver->ErrorReceived(errorMessage);
}

BString RunnerInterface::Exec(const char* cmd) 
{
	std::shared_ptr<FILE> pipe(popen(cmd, "r"), pclose);
    if (!pipe) 
    	throw std::runtime_error("popen() failed!");
    
    BString result = "";
    while (!feof(pipe.get())) 
    {
    	char buffer[128];
        if (fgets(buffer, 128, pipe.get()) != NULL)
            result += buffer;
    }
    return result;
}

BString RunnerInterface::GetMakeCommand(BPath& path, BString command)
{
	BString commandWithDirectory = command;
	
	BPath makeFilePath;
	//if ( != B_OK)
	//	return "";
	commandWithDirectory += " ";	
	commandWithDirectory += makeFilePath.Path();
	commandWithDirectory += " 2>&1"; 	
	std::cout << commandWithDirectory.String() << std::endl;
	return commandWithDirectory;
}
