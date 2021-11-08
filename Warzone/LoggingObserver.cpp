#include <iostream>
#include "./Headers/LoggingObserver.h"

using namespace std;

void SubJect::notify(ILoggable *log)
{
	view->update(log);
}

SubJect::~SubJect()
{
	delete view;
	view = NULL;
}

void LogObserver::update(ILoggable *log)
{
	gameLog.open("gamelog.txt", ios_base::app);
	if (!gameLog.is_open()) {
		cout << "Couldn't open file";
		return;
	}

	gameLog << log->stringToLog();
	gameLog.close();
}

LogObserver::LogObserver()
{

}

LogObserver::~LogObserver()
{

}

Observer::~Observer()
{
}

ILoggable::~ILoggable()
{
}
