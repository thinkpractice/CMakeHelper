#ifndef MAIN_WINDOW_CONTROLLER_H
#define MAIN_WINDOW_CONTROLLER_H

#include <vector>
#include <app/Messenger.h>
#include <storage/Path.h>
#include <support/ObjectList.h>
#include <support/String.h>
#include "RunnerInterface.h"

class MainWindowController : RunnerInterfaceObserver
{
	public:
		MainWindowController(BMessenger& windowMessenger, RunnerInterface* runnerInterface = new RunnerInterface());
		virtual ~MainWindowController();
	
	public:
		void ShowOpenFileDialog();
		void RunMake();
		void CleanMake();
		void ErrorMessageClicked(int32 listIndex);
		
		void SetMakeFileLocation(BPath& path);
		BPath GetMakeFileLocation();
		
		std::vector<ErrorMessage> ErrorMessages();
		
		void NotifyPropertyChanged(const char* propertyName);
		virtual void ErrorReceived(ErrorMessage& errorMessage);
		
	private:
		BMessenger _windowMessenger;
		BPath _makeFileLocation;
		std::vector<ErrorMessage> _errorsAndWarnings;
		RunnerInterface* _runnerInterface;
};

#endif
