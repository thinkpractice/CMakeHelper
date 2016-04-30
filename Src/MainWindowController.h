#ifndef MAIN_WINDOW_CONTROLLER_H
#define MAIN_WINDOW_CONTROLLER_H

#include <vector>
#include <storage/Path.h>
#include <support/ObjectList.h>
#include <support/String.h>
#include "RunnerInterface.h"

class MainWindowController : RunnerInterfaceObserver
{
	public:
		MainWindowController(RunnerInterface* runnerInterface = new RunnerInterface());
		virtual ~MainWindowController();
	
	public:
		void ShowOpenFileDialog();
		void RunMake();
		void CleanMake();
		
		void SetMakeFileLocation(BPath& path);
		BPath GetMakeFileLocation();
		
		virtual void ErrorReceived(ErrorMessage& errorMessage);
		
	private:
		BPath _makeFileLocation;
		std::vector<ErrorMessage> _errorsAndWarnings;
		RunnerInterface* _runnerInterface;
};

#endif
