#include "MainWindowController.h"

MainWindowController::MainWindowController(RunnerInterface* runnerInterface)
						: _runnerInterface(runnerInterface)
{
	_errorsAndWarnings = new BObjectList<BString>();
}

MainWindowController::~MainWindowController()
{	
	delete _errorsAndWarnings;
	delete _runnerInterface;
}

void MainWindowController::RunMake()
{
	_runnerInterface->Run(_makeFileLocation);
}

void MainWindowController::CleanMake()
{
	_runnerInterface->Clean(_makeFileLocation);
}

void MainWindowController::SetMakeFileLocation(BPath& path)
{
	_makeFileLocation = path;
}

BPath MainWindowController::GetMakeFileLocation()
{
	return _makeFileLocation;
}
