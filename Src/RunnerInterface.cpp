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
}

void RunnerInterface::Clean(BPath& path)
{
}
