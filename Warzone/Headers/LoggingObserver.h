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
};

class Subject {
public:
    LogObserver* view = new LogObserver();
    void notify(ILoggable* log);
    virtual ~Subject();
};
