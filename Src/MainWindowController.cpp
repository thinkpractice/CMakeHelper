#include "MainWindowController.h"
#include <storage/FilePanel.h>
#include "Constants.h"

MainWindowController::MainWindowController(BMessenger& windowMessenger,RunnerInterface* runnerInterface)
						:_windowMessenger(windowMessenger),
						 _runnerInterface(runnerInterface)
{
	_runnerInterface->SetObserver(this);
}

MainWindowController::~MainWindowController()
{	
	delete _runnerInterface;
}

void MainWindowController::ShowOpenFileDialog()
{
	BFilePanel* filePanel = new BFilePanel(B_OPEN_PANEL, &_windowMessenger, NULL, B_DIRECTORY_NODE);
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
	NotifyPropertyChanged(kMakeFileProperty);	
}

BPath MainWindowController::GetMakeFileLocation()
{
	return _makeFileLocation;
}

std::vector<ErrorMessage> MainWindowController::ErrorMessages()
{
	return _errorsAndWarnings;
}

void MainWindowController::NotifyPropertyChanged(const char* propertyName)
{
	BMessage* message = new BMessage(kPropertyChanged);
	message->AddString(kPropertyName, propertyName);
	_windowMessenger.SendMessage(message);
}

void MainWindowController::ErrorReceived(ErrorMessage& errorMessage)
{
	_errorsAndWarnings.push_back(errorMessage);
	NotifyPropertyChanged(kErrorListProperty);
}
