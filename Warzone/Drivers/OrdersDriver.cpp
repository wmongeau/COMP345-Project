/* ------------------------- */
/* The #include Of this file */
/* ------------------------- */

#include <iostream>
#include <string>
#include <vector>

using namespace std;
#include "../Headers/Orders.h"
#include "../Headers/Cards.h"

void ordersDriver(){
	//Creating a player list
	cout << "Creating player list..." << endl;
	vector<Player*> playerList =  vector<Player*>();
	cout << "Player list successfully created!" << endl;

	cout << "-----------------------------------" << endl;

	//Creating our players for testing
	cout << "Creating players and adding them to the player list..." << endl;
	Player* amadou = new Player("Amadou");
	playerList.push_back(amadou);

	cout << "--> Player 1 successfully created: " + amadou->getPlayerName() << endl;

	Player* matt = new Player("Matt");
	playerList.push_back(matt);
	cout << "--> Player 2 successfully created: " + matt->getPlayerName() << endl;

	Player* samil = new Player("Samil");
	playerList.push_back(samil);
	cout << "--> Player 3 successfully created: " + samil->getPlayerName() << endl;

	cout << "-----------------------------------" << endl;

	//Creating territories
	cout << "Creating territories and assigning them to specific players..." << endl;
	Territory* territory1 = new Territory(1, "Territory 1", 1, 0, 0);
	Territory* territory3 = new Territory(3, "Territory 3", 1, 0, 0);
	Territory* territory5 = new Territory(5, "Territory 5", 2, 0, 0);
	amadou->addOwnedTerritory(territory1);
	amadou->addOwnedTerritory(territory3);
	amadou->addOwnedTerritory(territory5);

	Territory* territory2 = new Territory(2, "Territory 2", 1, 0, 0);
	Territory* territory4 = new Territory(4, "Territory 4", 1, 0, 0);
	matt->addOwnedTerritory(territory2);
	matt->addOwnedTerritory(territory4);

	Territory* territory6 = new Territory(6, "Territory 6", 2, 0, 0);
	samil->addOwnedTerritory(territory6);
	cout << "Territories have been successfully created and assigned!" << endl;

	cout << "-----------------------------------" << endl;

	//Creating territories that players can attack
	cout << "Assigning the territories that each player can attack to the specific players..." << endl;
	amadou->addTerritoryToAttack(territory2);
	amadou->addTerritoryToAttack(territory4);
	amadou->addTerritoryToAttack(territory6);

	matt->addTerritoryToAttack(territory1);
	matt->addTerritoryToAttack(territory3);
	matt->addTerritoryToAttack(territory5);
	matt->addTerritoryToAttack(territory6);

	samil->addTerritoryToAttack(territory1);
	samil->addTerritoryToAttack(territory2);
	samil->addTerritoryToAttack(territory3);
	samil->addTerritoryToAttack(territory4);
	samil->addTerritoryToAttack(territory5);
	cout << "Territories have been successfully assigned!" << endl;

	cout << "-----------------------------------" << endl;

	cout << "Initializing army values for each territory..." << endl;
	territory1->updateArmyValue(10);
	territory2->updateArmyValue(10);
	territory3->updateArmyValue(10);
	territory4->updateArmyValue(10);
	territory5->updateArmyValue(25);
	territory6->updateArmyValue(10);
	cout << "Army values successfully initialized!" << endl;

	cout << "-----------------------------------" << endl;

	cout << "Initializing borders for each territory..." << endl;
	territory1->addBorder(territory2);
	territory1->addBorder(territory3);
	territory2->addBorder(territory1);
	territory2->addBorder(territory4);
	territory3->addBorder(territory1);
	territory4->addBorder(territory2);
	territory5->addBorder(territory6);
	territory6->addBorder(territory5);
	cout << "Borders successfully initialized!" << endl;

	cout << "-----------------------------------" << endl;

	//Testing valid Deploy Order
	cout << "Creating valid Deploy Order..." << endl;
	DeployOrder* deployOrder;
	deployOrder = new DeployOrder(*amadou, *territory1, 50);
	cout << "--> Deploy Order was created! " << endl;
	cout << "Preparing execution of Deploy Order..." << endl;
	deployOrder->execute();
	cout << *deployOrder << endl;

	//Testing invalid Deploy Order
	cout << "Creating invalid Deploy Order..." << endl;
	delete deployOrder;
	deployOrder = new DeployOrder(*amadou, *territory2, 50);
	cout << "--> Deploy Order was created! " << endl;
	cout << "Preparing execution of Deploy Order..." << endl;
	deployOrder->execute();
	cout << *deployOrder << endl;

	cout << "-----------------------------------" << endl;

	//Testing valid Advance Orders
	cout << "Creating valid Advance Order (advancing on owned territory)..." << endl;
	AdvanceOrder* advanceOrder;
	advanceOrder = new AdvanceOrder(*amadou, *territory1, *territory3, 10);
	cout << "--> Advance Order was created! " << endl;
	cout << "Preparing execution of Advance Order..." << endl;
	advanceOrder->execute();
	cout << *advanceOrder << endl;

	cout << "Creating valid Advance Order (advancing on ennemy territory)..." << endl;
	delete advanceOrder;
	advanceOrder = new AdvanceOrder(*amadou, *territory1, *territory2, 10);
	cout << "--> Advance Order was created! " << endl;
	cout << "Preparing execution of Advance Order..." << endl;
	advanceOrder->execute();
	cout << *advanceOrder << endl;

	//Testing invalid Advance Orders
	cout << "Creating invalid Advance Order (source territory does not belong to the player that issued the order)..." << endl;
	delete advanceOrder;
	advanceOrder = new AdvanceOrder(*amadou, *territory2, *territory1, 10);
	cout << "--> Advance Order was created! " << endl;
	cout << "Preparing execution of Advance Order..." << endl;
	advanceOrder->execute();
	cout << *advanceOrder << endl;

	cout << "Creating invalid Advance Order (source territory is not adjacent to target territory)..." << endl;
	delete advanceOrder;
	advanceOrder = new AdvanceOrder(*amadou, *territory1, *territory4, 10);
	cout << "--> Advance Order was created! " << endl;
	cout << "Preparing execution of Advance Order..." << endl;
	advanceOrder->execute();
	cout << *advanceOrder << endl;

	cout << "-----------------------------------" << endl;

	//Testing valid Airlift Order
	cout << "Creating valid Airlift Order..." << endl;
	AirliftOrder* airliftOrder;
	airliftOrder = new AirliftOrder(*amadou, *territory1, *territory3, 10);

	cout << "--> Airlift Order was created! " << endl;
	cout << "Preparing execution of Airlift Order..." << endl;
	airliftOrder->execute();
	cout << *airliftOrder << endl;

	//Testing valid Airlift Order
	cout << "Creating invalid Airlift Order..." << endl;
	delete airliftOrder;
	airliftOrder = new AirliftOrder(*amadou, *territory2, *territory3, 10);

	cout << "--> Airlift Order was created! " << endl;
	cout << "Preparing execution of Airlift Order..." << endl;
	airliftOrder->execute();
	cout << *airliftOrder << endl;

	cout << "-----------------------------------" << endl;

	//Testing valid Bomb Order
	cout << "Creating valid Bomb Order..." << endl;
	BombOrder* bombOrder;
	bombOrder = new BombOrder(*amadou, *matt, *territory2);

	cout << "--> Bomb Order was created! " << endl;
	cout << "Preparing execution of Bomb Order..." << endl;
	bombOrder->execute();
	cout << *bombOrder << endl;
	
	//Testing invalid Bomb Orders
	cout << "Creating invalid Bomb Order (target territory is owned by issuing player)..." << endl;
	delete bombOrder;
	bombOrder = new BombOrder(*amadou, *matt, *territory1);

	cout << "--> Bomb Order was created! " << endl;
	cout << "Preparing execution of Bomb Order..." << endl;
	bombOrder->execute();
	cout << *bombOrder << endl;

	cout << "Creating invalid Bomb Order (target territory is not adjacent to a territory owned by the issuing player)..." << endl;
	delete bombOrder;
	bombOrder = new BombOrder(*amadou, *matt, *territory4);
	cout << "--> Bomb Order was created! " << endl;
	cout << "Preparing execution of Bomb Order..." << endl;
	bombOrder->execute();
	cout << *bombOrder << endl;

	cout << "-----------------------------------" << endl;

	//Testing valid Blockade Order
	cout << "Creating valid Blockade Order..." << endl;
	BlockadeOrder* blockadeOrder;
	blockadeOrder = new BlockadeOrder(*amadou, *territory1, playerList);

	cout << "--> Blockade Order was created! " << endl;
	cout << "Preparing execution of Blockade Order..." << endl;
	blockadeOrder->execute();
	cout << *blockadeOrder << endl;

	//Testing invalid Blockade Order
	cout << "Creating invalid Blockade Order..." << endl;
	playerList.push_back(blockadeOrder->getPlayerList().back());
	delete blockadeOrder;
	blockadeOrder = new BlockadeOrder(*amadou, *territory2, playerList);

	cout << "--> Blockade Order was created! " << endl;
	cout << "Preparing execution of Blockade Order..." << endl;
	blockadeOrder->execute();
	cout << *blockadeOrder << endl;

	cout << "-----------------------------------" << endl;

	//Testing valid Negotiate Order
	cout << "Creating valid Negotiate Order..." << endl;
	NegotiateOrder* negotiateOrder;
	negotiateOrder = new NegotiateOrder(*amadou, *matt);

	cout << "--> Negotiate Order was created! " << endl;
	cout << "Preparing execution of Negotiate Order..." << endl;
	negotiateOrder->execute();
	cout << *negotiateOrder << endl;

	//Testing invalid Negotiate Order
	cout << "Creating invalid Negotiate Order..." << endl;
	delete negotiateOrder;
	negotiateOrder = new NegotiateOrder(*amadou, *amadou);

	cout << "--> Negotiate Order was created! " << endl;
	cout << "Preparing execution of Negotiate Order..." << endl;
	negotiateOrder->execute();
	cout << *negotiateOrder << endl;

	cout << "-----------------------------------" << endl;

	//Testing conquering territory after Advance Order
	cout << "Creating valid Advance Order to test the conquering of a territory..." << endl;
	cout << "--> Advance Order was created! " << endl;
	cout << "Preparing execution of Advance Order..." << endl;
	while (amadou != territory6->getPlayer()) {
		delete advanceOrder;
		advanceOrder = new AdvanceOrder(*amadou, *territory5, *territory6, territory5->getArmyValue() - 1);
		advanceOrder->execute();
		cout << *advanceOrder << endl;
	}
	

	//Adding a card to a player after conquering a territory (following an Advance Order)
	if (territory6->getPlayer() == amadou)
	{
		Deck* newDeck = new Deck();
		cout << endl;

		amadou->addCardToHand(newDeck->draw());
		cout << amadou->getPlayerName() + " has drawn a card from the deck after conquering " + territory6->getName() + "!" << endl;
		amadou->getPlayerHand()->showHand();

		delete newDeck;
		newDeck = NULL;
	}
	
	cout << "-----------------------------------" << endl;

	//Testing Advance Order on a territory that belongs to a player we cannot attack (because of Negotiate Order)
	cout << "Creating an Advance Order to test the Negotiate functionality..." << endl;
	delete advanceOrder;
	advanceOrder = new AdvanceOrder(*amadou, *territory1, *territory2, 10);
	cout << "--> Advance Order was created! " << endl;
	cout << "Preparing execution of Advance Order..." << endl;
	advanceOrder->execute();
	cout << *advanceOrder << endl;

	delete amadou;
	amadou = NULL;

	delete matt;
	matt = NULL;

	delete samil;
	samil = NULL;

	delete playerList.back();

	delete territory1;
	territory1 = NULL;

	delete territory3;
	territory3 = NULL;

	delete territory5;
	territory5 = NULL;

	delete territory4;
	territory4 = NULL;

	delete territory6;
	territory6 = NULL;

	delete deployOrder;
	deployOrder = NULL;

	delete advanceOrder;
	advanceOrder = NULL;

	delete airliftOrder;
	airliftOrder = NULL;

	delete bombOrder;
	bombOrder = NULL;

	delete blockadeOrder;
	blockadeOrder = NULL;

	delete negotiateOrder;
	negotiateOrder = NULL;
}
