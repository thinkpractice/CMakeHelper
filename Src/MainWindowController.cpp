#include "MainWindowController.h"

MainWindowController::MainWindowController()
{
	_errorsAndWarnings = new BObjectList<BString>();
}

MainWindowController::~MainWindowController()
{
	delete _errorsAndWarnings;
}

void MainWindowController::SetMakeFileLocation(BPath& path)
{
	_makeFileLocation = path;
}

BPath MainWindowController::GetMakeFileLocation()
{
	return _makeFileLocation;
}


void MainWindowController::RunMake()
{
}

void MainWindowController::CleanMake()
{
}
