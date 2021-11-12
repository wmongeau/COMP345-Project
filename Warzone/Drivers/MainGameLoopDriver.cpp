#include <iostream>
#include <string>

using namespace std;
#include "../Headers/MainGameLoopDriver.h"
#include "../Headers/GameEngine.h"


void mainGameLoopDriver(){
    GameEngine* engine = new GameEngine();
    
    engine->startupPhase();
    engine->mainGameLoop();
}