#include "RunnerInterface.h"
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <ostream>
#include <sstream>
#include <memory>
#include <stdexcept>
#include "MakeOutputParser.h"

RunnerInterface::RunnerInterface()
					: RunnerInterface(new MakeOutputParser)
{
}

RunnerInterface::RunnerInterface(CommandLineOutputParser* commandLineOutputParser)
			:	_runnerInterfaceObserver(NULL),
				_commandLineOutputParser(commandLineOutputParser)
{
}

RunnerInterface::~RunnerInterface()
{
	delete _commandLineOutputParser;
}

void RunnerInterface::SetObserver(RunnerInterfaceObserver* observer)
{
	_runnerInterfaceObserver = observer;
}

void RunnerInterface::Run(BPath& path)
{
	BString command = GetMakeCommand(path, "make -C");
	BString errors = Exec(command.String());
	
	std::vector<ErrorMessage> errorMessages = _commandLineOutputParser->ParseOutput(errors);
	for (auto errorMessage : errorMessages)
	{
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
	commandWithDirectory += " ";	
	commandWithDirectory += path.Path();
	commandWithDirectory += " 2>&1"; 	
	std::cout << commandWithDirectory.String() << std::endl;
	return commandWithDirectory;
}
