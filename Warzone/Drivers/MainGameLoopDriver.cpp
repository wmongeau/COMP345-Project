#include <iostream>
#include <string>

using namespace std;
#include "../Headers/MainGameLoopDriver.h"
#include "../Headers/GameEngine.h"
#include "../Headers/MapDriver.h"


void mainGameLoopDriver(){
	string arg,arg2;
	arg = "test.txt";
	arg2 = "test2.txt";
	FileCommandProcessorAdaptor* fileProcessor = new FileCommandProcessorAdaptor(arg);
	GameEngine* engine = new GameEngine(fileProcessor);
	while (engine->getCurrentState()->getStateName() != Enums::quit)
	{
		engine->startupPhase();
		engine->mainGameLoop();
		delete engine;
		engine = new GameEngine(new FileCommandProcessorAdaptor(arg2));
	}
	delete engine;
	engine = NULL;
}