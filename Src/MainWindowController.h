#ifndef MAIN_WINDOW_CONTROLLER_H
#define MAIN_WINDOW_CONTROLLER_H

#include <memory>
#include <vector>
#include <app/Messenger.h>
#include <storage/Path.h>
#include <storage/Entry.h>
#include <support/ObjectList.h>
#include <support/String.h>
#include "RunnerInterface.h"
#include "AppSettings.h"

class MainWindowController : RunnerInterfaceObserver
{
	public:
		MainWindowController(BMessenger& windowMessenger, RunnerInterface* runnerInterface = new RunnerInterface());
		virtual ~MainWindowController();
	
	public:
		void Init();
		void QuitRequested();
		void ShowOpenFileDialog();
		void RunMake();
		void CleanMake();
		void ErrorMessageClicked(int32 listIndex);
		
		void SetMakeFileLocation(BEntry& path);
		BEntry GetMakeFileLocation();
		
		std::vector<ErrorMessage> ErrorMessages();
		
		void NotifyPropertyChanged(const char* propertyName);
		virtual void ErrorReceived(ErrorMessage& errorMessage);
	
	private:
		void OpenFile(BEntry& filePath);
		
	private:
		BMessenger _windowMessenger;
		BEntry _makeFileLocation;
		std::vector<ErrorMessage> _errorsAndWarnings;
		RunnerInterface* _runnerInterface;
		std::shared_ptr<AppSettings> _appSettings;
};

#endif
