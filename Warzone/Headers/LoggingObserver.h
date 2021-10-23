#pragma once
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

string stringToLog();

class ILoggable{
   public:
      virtual string stringToLog() = 0; // Pure Virtual Function
};


class Observer {
public:
    virtual void update(ILoggable *log)=0;
};

class LogObserver :Observer {
public:
    ofstream gameLog;
    LogObserver();
    void update(ILoggable* log);
    ~LogObserver();
};

class SubJect {
public:
    LogObserver* view = new LogObserver();
    void notify(ILoggable* log);
};
