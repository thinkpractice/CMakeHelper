#include "RunnerInterface.h"
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <ostream>
#include <sstream>
#include <memory>
#include <stdexcept>

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
	BString error = exec("make");
	ErrorMessage errorMessage(error);
	_runnerInterfaceObserver->ErrorReceived(errorMessage);
}

BString RunnerInterface::exec(const char* cmd) 
{
	std::stringstream buffer;
	//std::streambuf* old = std::cerr.rdbuff(buffer.rdbuf());   


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
    
    std::string errors = buffer.str();
    result << errors.c_str();
    
    return result;
}

void RunnerInterface::Clean(BPath& path)
{
	BString error = exec("make clean");
	ErrorMessage errorMessage(error);
	_runnerInterfaceObserver->ErrorReceived(errorMessage);
}
