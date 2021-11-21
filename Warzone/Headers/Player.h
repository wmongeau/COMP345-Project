#pragma once

#include <vector>
#include <string>
#include "PlayerStrategies.h"

using namespace std;

class Territory;
class Hand;
class OrdersList;
class Card;
class Deck;
enum class OrdersEnum;

enum class PlayerType { human, neutral, cheater, aggressive, benevolent };

//Class declaration for the Player class
class Player {
public:
	Deck* deck;
	PlayerStrategy* ps;
	Player();
	Player(const Player& p);
	Player(string playerName);
	Player(string playerName, PlayerType playerType);
	Player& operator =(const Player& p);
	~Player();
	vector<Territory*> getOwnedTerritories();
	Hand* getPlayerHand();
	OrdersList* getOrders();
	string getPlayerName();
	vector<Player*> getEnemies();
	void setEnemies(vector<Player*> enemies);
	void setCanDefend(vector<Territory*> territories);
	void setCanAttack(vector<Territory*> territories);
	void addTerritoryToDefend(Territory* territory);
	void addTerritoryToAttack(Territory* territory);
	void removeTerritoryToDefend(Territory* territory);
	void removeTerritoryToAttack(Territory* territory);
	bool playerCanAttack(Territory* territory);
	bool playerCanDefend(Territory* territory);
	vector<Territory*> getToDefend();
	vector<Territory*> getToAttack();
	vector<Territory*> toDefend();
	vector<Territory*> toAttack();
	void issueOrder(OrdersEnum orderType);
	void issueOrder();
	void addOwnedTerritory(Territory* territory);
	void removeOwnedTerritory(Territory* territory);
	void addCardToHand(Card* card);
	void setReinforcementPool(int pool);
	int getReinforcementPool();
	friend ostream& operator <<(ostream& out, Player& player);
	bool getIsTurnFinish();
	void setIsTurnFinish(bool val);
	PlayerType getPlayerType();
	void changePlayerType(PlayerType newType);
private:
	bool isTurnFinish;
	vector<Player*> enemies;
	vector<Territory*> CanDefend;
	vector<Territory*> CanAttack;
	string PlayerName;
	Hand* PlayerHand;
	OrdersList* Orders;
	vector<Territory*> OwnedTerritories;
	int reinforcementPool;
	PlayerType playerType;
	void adjustPlayerStrategy();
};

ostream& operator <<(ostream& out, Player& player);
