#ifndef RUNNER_INTERFACE_H
#define RUNNER_INTERFACE_H

#include <storage/Path.h>
#include "RunnerInterfaceObserver.h"

class RunnerInterface
{
	public:
		RunnerInterface();
		virtual ~RunnerInterface();
	
	public:
		virtual void Run(BPath& path);
		virtual void Clean(BPath& path);
		void SetObserver(RunnerInterfaceObserver* observer);
		
	private:
		RunnerInterfaceObserver* _runnerInterfaceObserver;
		
};

#endif
