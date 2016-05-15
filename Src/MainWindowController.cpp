#include "MainWindowController.h"
#include <storage/FilePanel.h>
#include <storage/Entry.h>
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
	_runnerInterface->Run(_makeFileLocation);
	NotifyPropertyChanged(kErrorListProperty);
}

void MainWindowController::CleanMake()
{
	_runnerInterface->Clean(_makeFileLocation);
}

void MainWindowController::ErrorMessageClicked(int32 listIndex)
{
	std::cout << "Item Clicked at index: " << index << std::endl;
	
	BEntry path("/boot/home/Projects/CMakeHelper/Src/ErrorMessage.h");
	entry_ref ref;
	if (path.GetRef(&ref) == B_OK)
	{
		be_roster->Launch(&ref);
	}
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
	//NotifyPropertyChanged(kErrorListProperty);
}
