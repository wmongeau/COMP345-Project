#pragma once
#include "Player.h"
#include "Map.h"
#include "Orders.h"
#include "Cards.h"
using namespace std;
class Human {
private:
	Player* p;
public:
	Human();
	Human(Player* p);
	Human(Human* human);
	Player* getPlayer();
	void issueOrder();
	vector<Territory*> toAttack();
	vector<Territory*> toDefend();
};


class Neutral {
private:
	Player* p;
public:
	Neutral();
	Neutral(Player& p);
	Neutral(Human& human);
	void issueOrder();
	vector<Territory*> toAttack();
	vector<Territory*> toDefend();
};