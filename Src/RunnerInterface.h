#ifndef RUNNER_INTERFACE_H
#define RUNNER_INTERFACE_H

#include <storage/Path.h>
#include <support/String.h>
#include "RunnerInterfaceObserver.h"
#include "CommandLineOutputParser.h"

class RunnerInterface
{
	public:
		RunnerInterface();
		RunnerInterface(CommandLineOutputParser* commandLineOutputParser);
		virtual ~RunnerInterface();
	
	public:
		virtual void Run(BPath& path);
		virtual void Clean(BPath& path);
		void SetObserver(RunnerInterfaceObserver* observer);

	private:
		BString Exec(const char* cmd);
		BString GetMakeCommand(BPath& path, BString command);
			
	private:
		RunnerInterfaceObserver* _runnerInterfaceObserver;
		CommandLineOutputParser* _commandLineOutputParser;
		
};

#endif
