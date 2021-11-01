#pragma once
#include <string>
#include <iostream>
#include <fstream>
using namespace std;

class ILoggable{
   public:
      virtual string stringToLog() = 0; // Pure Virtual Function
      ~ILoggable();
};


class Observer {
public:
    virtual void update(ILoggable *log)=0;
    ~Observer();
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
    ~SubJect();
};
