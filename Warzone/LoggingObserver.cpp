#include <iostream>
#include "./Headers/LoggingObserver.h"

using namespace std;

Subject::Subject()
{
	this->view = new LogObserver();
}

Subject::Subject(const Subject& c)
{
	this->view = c.view;
}

Subject& Subject::operator=(const Subject& c)
{
	this->view = c.view;

	return *this;
}

//Subject of the observer pattern
void Subject::notify(ILoggable *log)
{
	view->update(log);
}

//Subject destructor
Subject::~Subject()
{
	delete view;
	view = NULL;
}

//This method will save to a log file
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

//LogObserver constructor
LogObserver::LogObserver()
{
}

//LogObserver destructor
LogObserver::~LogObserver()
{
}

//Observer destructor
Observer::~Observer()
{
}

//ILoggable destructor
ILoggable::~ILoggable()
{
}

ostream& operator<<(ostream& os, const LogObserver& c)
{
	os << "LogObserver" << endl;

	return os;
}

ostream& operator<<(ostream& os, const Subject& c)
{
	os << "Subject" << endl;

	return os;
}
