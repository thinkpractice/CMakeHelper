#ifndef MAIN_WINDOW_CONTROLLER_H
#define MAIN_WINDOW_CONTROLLER_H

#include <storage/Path.h>
#include <support/ObjectList.h>
#include <support/String.h>

class MainWindowController
{
	public:
		MainWindowController();
		virtual ~MainWindowController();
	
	public:
		void SetMakeFileLocation(BPath& path);
		BPath GetMakeFileLocation();
		
		void RunMake();
		void CleanMake();
		
	private:
		BPath _makeFileLocation;
		BObjectList<BString>* _errorsAndWarnings;
};

#endif
