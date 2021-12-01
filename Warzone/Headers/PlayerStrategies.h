#pragma once
#include <vector>
	using std::vector;
#include <ostream>
	using std::ostream;
class Territory;
class Player;

class PlayerStrategy {
public:
	PlayerStrategy();
	PlayerStrategy(Player* player);
	virtual ~PlayerStrategy();
	PlayerStrategy(const PlayerStrategy& c);
	PlayerStrategy& operator=(const PlayerStrategy& c);
	friend ostream& operator<<(ostream& out, const PlayerStrategy& c);
	Player* player;
	virtual void issueOrder() = 0;
	virtual vector<Territory*> toAttack() = 0;
	virtual vector<Territory*> toDefend() = 0;
};

class HumanPlayerStrategy : public PlayerStrategy {
public:
	HumanPlayerStrategy();
	HumanPlayerStrategy(Player* player);
	~HumanPlayerStrategy();
	HumanPlayerStrategy(const PlayerStrategy& c);
	HumanPlayerStrategy& operator=(const HumanPlayerStrategy& c);
	friend ostream& operator<<(ostream& out, const HumanPlayerStrategy& c);
	void issueOrder();
	vector<Territory*> toAttack();
	vector<Territory*> toDefend();
};

class CheaterPlayerStrategy : public PlayerStrategy {
public:
	CheaterPlayerStrategy();
	CheaterPlayerStrategy(Player* player);
	~CheaterPlayerStrategy();
	CheaterPlayerStrategy(const CheaterPlayerStrategy& c);
	CheaterPlayerStrategy& operator=(const CheaterPlayerStrategy& c);
	friend ostream& operator<<(ostream& out, const CheaterPlayerStrategy& c);
	void issueOrder();
	vector<Territory*> toAttack();
	vector<Territory*> toDefend();
};

class NeutralPlayerStrategy : public PlayerStrategy {
public:
	NeutralPlayerStrategy();
	NeutralPlayerStrategy(Player* player);
	~NeutralPlayerStrategy();
	NeutralPlayerStrategy(const NeutralPlayerStrategy& c);
	NeutralPlayerStrategy& operator=(const NeutralPlayerStrategy& c);
	friend ostream& operator<<(ostream& out, const NeutralPlayerStrategy& c);
	void issueOrder();
	vector<Territory*> toAttack();
	vector<Territory*> toDefend();
};

class AggressivePlayerStrategy : public PlayerStrategy {
public:
	AggressivePlayerStrategy();
	AggressivePlayerStrategy(Player* player);
	~AggressivePlayerStrategy();
	AggressivePlayerStrategy(const AggressivePlayerStrategy& c);
	AggressivePlayerStrategy& operator=(const AggressivePlayerStrategy& c);
	friend ostream& operator<<(ostream& out, const AggressivePlayerStrategy& c);
	void issueOrder();
	vector<Territory*> toAttack();
	vector<Territory*> toDefend();
};

class BenevolentPlayerStrategy : public PlayerStrategy {
public:
	BenevolentPlayerStrategy();
	BenevolentPlayerStrategy(Player* player);
	~BenevolentPlayerStrategy();
	BenevolentPlayerStrategy(const BenevolentPlayerStrategy& c);
	BenevolentPlayerStrategy& operator=(const BenevolentPlayerStrategy& c);
	friend ostream& operator<<(ostream& out, const BenevolentPlayerStrategy& c);
	void issueOrder();
	vector<Territory*> toAttack();
	vector<Territory*> toDefend();
};