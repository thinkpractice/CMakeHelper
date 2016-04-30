#ifndef MAIN_WINDOW_CONTROLLER_H
#define MAIN_WINDOW_CONTROLLER_H

#include <storage/Path.h>
#include <support/ObjectList.h>
#include <support/String.h>
#include "RunnerInterface.h"

class MainWindowController
{
	public:
		MainWindowController(RunnerInterface* runnerInterface = new RunnerInterface());
		virtual ~MainWindowController();
	
	public:
		void RunMake();
		void CleanMake();
		
		void SetMakeFileLocation(BPath& path);
		BPath GetMakeFileLocation();
		
	private:
		BPath _makeFileLocation;
		BObjectList<BString>* _errorsAndWarnings;
		RunnerInterface* _runnerInterface;
};

#endif
