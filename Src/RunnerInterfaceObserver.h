#ifndef RUNNER_INTERFACE_OBSERVER_H
#define RUNNER_INTERFACE_OBSERVER_H

#include "ErrorMessage.h"

class RunnerInterfaceObserver
{
	public:
		virtual void ErrorReceived(ErrorMessage& errorMessage) = 0;
};

#endif
