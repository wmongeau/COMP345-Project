#pragma once
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class ILoggable{
   public:
      virtual string stringToLog() = 0; // Pure Virtual Function
      virtual ~ILoggable();
};

class Observer {
public:
    virtual void update(ILoggable *log)=0;
    virtual ~Observer();
};

class LogObserver :Observer {
public:
    ofstream gameLog;
    LogObserver();
    void update(ILoggable* log);
    ~LogObserver();
    friend ostream& operator<<(ostream& os, const LogObserver& c);
};

class Subject {
public:
    LogObserver* view;
    Subject();
    Subject(const Subject& c);
    Subject& operator=(const Subject& c);
    friend ostream& operator<<(ostream& os, const Subject& c);
    void notify(ILoggable* log);
    virtual ~Subject();
};
