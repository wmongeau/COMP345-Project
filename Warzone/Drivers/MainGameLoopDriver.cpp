#include <iostream>
#include <string>

using namespace std;
#include "../Headers/MainGameLoopDriver.h"
#include "../Headers/GameEngine.h"
#include "../Headers/MapDriver.h"


void mainGameLoopDriver(){
	string arg;
	arg = "../test.tx";
#ifdef _WIN32
	arg = "../../../test.txt";
#endif
	FileCommandProcessorAdaptor* fileProcessor =new FileCommandProcessorAdaptor(arg);
	GameEngine* engine = new GameEngine(fileProcessor);
	engine->startupPhase();
	engine->mainGameLoop();
}