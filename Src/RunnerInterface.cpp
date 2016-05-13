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
	//BString error = exec("make");
	BString command = "make";
	command += " 2>&1"; 
	
	BString errors = exec(command.String());
	
	BStringList errorList;
	errors.Split("\n", false, errorList);
	
	for (int i = 0; i < errorList.CountStrings(); i++)
	{
		BString error = errorList.StringAt(i);
		ErrorMessage errorMessage(error);
		_runnerInterfaceObserver->ErrorReceived(errorMessage);
	}
}

BString RunnerInterface::exec(const char* cmd) 
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

void RunnerInterface::Clean(BPath& path)
{
	BString error = exec("make clean");
	ErrorMessage errorMessage(error);
	_runnerInterfaceObserver->ErrorReceived(errorMessage);
}
