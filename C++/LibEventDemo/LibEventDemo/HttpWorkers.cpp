#include "stdafx.h"
#include "HttpWorkers.h"
#include "EventHttpWorker.h"

HttpWorker* HttpWorkers::newEventWorker()
{
	return new EventHttpWorker();
}