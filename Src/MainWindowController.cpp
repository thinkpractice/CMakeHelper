#include "MainWindowController.h"
#include <storage/FilePanel.h>
#include <storage/FindDirectory.h>
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

void MainWindowController::Init()
{
	BPath settingsPath = GetSettingsPath();
	
	BEntry appSettingsPath(settingsPath.Path());
	if (!appSettingsPath.Exists())	
	{
		_appSettings = std::shared_ptr<AppSettings>(new AppSettings);
		std::cout << "New app settings" << std::endl;
		return;
	}	
	std::cout << "Load app settings" << std::endl;
	_appSettings = AppSettings::Load(appSettingsPath);
	
	BEntry makeFilePath = _appSettings->FilePath();
	if (makeFilePath.Exists())
		SetMakeFileLocation(makeFilePath);
}

void MainWindowController::QuitRequested()
{
	BPath settingsPath = GetSettingsPath();
	BEntry appSettingsPath(settingsPath.Path());
	
	_appSettings->SetFilePath(_makeFileLocation);
	AppSettings::Save(_appSettings, appSettingsPath); 
}

void MainWindowController::ShowOpenFileDialog()
{
	BFilePanel* filePanel = new BFilePanel(B_OPEN_PANEL, &_windowMessenger, NULL, B_DIRECTORY_NODE);
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
	_errorsAndWarnings.clear();
	_runnerInterface->Clean(_makeFileLocation);
}

void MainWindowController::ErrorMessageClicked(int32 listIndex)
{
	if (listIndex < 0 || listIndex >= _errorsAndWarnings.size())
		return;
	
	ErrorMessage errorMessage = _errorsAndWarnings[listIndex];	
	BEntry path = errorMessage.FilePath();
	OpenFile(path);	
}

void MainWindowController::SetMakeFileLocation(BEntry& path)
{
	_makeFileLocation = path;
	NotifyPropertyChanged(kMakeFileProperty);	
}

BEntry MainWindowController::GetMakeFileLocation()
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

BPath MainWindowController::GetSettingsPath()
{
	BPath appSettingsPath;
	status_t status = find_directory(B_USER_SETTINGS_DIRECTORY, &appSettingsPath);
    appSettingsPath.Append("CMakeHelper_settings");		    
	return appSettingsPath;
}
