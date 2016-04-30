#include "MainWindowController.h"
#include <storage/FilePanel.h>

MainWindowController::MainWindowController(RunnerInterface* runnerInterface)
						: _runnerInterface(runnerInterface)
{
	_runnerInterface->SetObserver(this);
}

MainWindowController::~MainWindowController()
{	
	delete _runnerInterface;
}

void MainWindowController::ShowOpenFileDialog()
{
	BFilePanel* filePanel = new BFilePanel(B_OPEN_PANEL, NULL, NULL, B_DIRECTORY_NODE);
	filePanel->Show();
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

void MainWindowController::ErrorReceived(ErrorMessage& errorMessage)
{
	_errorsAndWarnings.push_back(errorMessage);
}
