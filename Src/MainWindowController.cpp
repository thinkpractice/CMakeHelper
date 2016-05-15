#include "MainWindowController.h"
#include <storage/FilePanel.h>
#include <Roster.h>
#include <iostream>
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
	BFilePanel* filePanel = new BFilePanel(B_OPEN_PANEL, &_windowMessenger, NULL);
	filePanel->Show();
}

void MainWindowController::RunMake()
{
	_errorsAndWarnings.clear();
	_runnerInterface->Run(_makeFileLocation);
	NotifyPropertyChanged(kErrorListProperty);
}

void MainWindowController::CleanMake()
{
	_runnerInterface->Clean(_makeFileLocation);
}

void MainWindowController::ErrorMessageClicked(int32 listIndex)
{
	std::cout << "Item Selected at Index:" << listIndex << std::endl;
	if (listIndex < 0 || listIndex >= _errorsAndWarnings.size())
		return;
	
	ErrorMessage errorMessage = _errorsAndWarnings[listIndex];	
	BEntry path = errorMessage.FilePath();
	OpenFile(path);	
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
}

void MainWindowController::OpenFile(BEntry& filePath)
{
	entry_ref ref;
	if (filePath.GetRef(&ref) == B_OK)
	{
		be_roster->Launch(&ref);
	}
}
