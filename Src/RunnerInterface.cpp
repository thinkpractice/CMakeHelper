#include "RunnerInterface.h"

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
	for (int i = 0; i < 10; i++)
	{
		BString error = "Error"; 
		error << i;
		ErrorMessage errorMessage(error);
		_runnerInterfaceObserver->ErrorReceived(errorMessage);
	}
}

void RunnerInterface::Clean(BPath& path)
{
}
