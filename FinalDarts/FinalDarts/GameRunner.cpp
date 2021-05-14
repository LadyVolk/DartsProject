#include "pch.h"
#include "GameRunner.h"
#include "Player.h"
#include <iostream>
using namespace std;

GameRunner::GameRunner(Player* player_1, Player* player_2)
{
	int i, j;

	starting_player = nullptr;
	current_player = nullptr;
	winner = nullptr;

	players.resize(2);
	players[0] = player_1;
	players[1] = player_2;

	//reseting the array stats to zero
	for (i = 0; i < 2; i++) {
		for (j = 0; j < 7; j++) {
			stats[i][j] = 0;
		}
	}
}


GameRunner::~GameRunner()
{
	delete players[0];
	delete players[1];
}

void GameRunner::RunTests(int tests) {

	int i;

	//several competitions to generate graph
	for (i = 0; i < tests; i++) {

		cout << "calculating test... " << i << endl;


		//start competition
		this->RunCompetition();
	}
	this->PrintResults(tests);
}
void GameRunner::PrintResults(int tests) {
	int i, j;
	double total_result;
	cout << endl << "result based on " << tests << " tests:" << endl;
	cout << players[0]->GetName() << "/" << players[1]->GetName() << "   frequency" << endl;
	//printing the stats of which player
	for (i = 0; i < 2; i++) {
		total_result = 0;
		for (j = 0; j < 7; j++) {
			total_result += ((double)stats[i][j]/tests);
			if (i == 0) {
				cout << "  7/" << j << "   " << ((double)stats[i][j] / tests) * 100 << "%" << endl;
			}
			else {
				cout << "  " << j << "/7" << "   " << ((double)stats[i][j] / tests) * 100 << "%" << endl;
			}
		}
		cout << "total percentage of wins is " << total_result*100 << "%" << endl;
	}
}
void GameRunner::RunCompetition() {
	
	players[0]->SetSets(0);
	players[1]->SetSets(0);

	//start competition
	while (players[0]->GetSets() < 7 && players[1]->GetSets() < 7) {

		starting_player = players[0];

		

		//start set
		this->RunSet();

		//increase players wins
		if (players[0]->GetGameWins() > players[1]->GetGameWins()) {
			players[0]->SetSets(players[0]->GetSets() + 1);
			if (players[0]->GetInteractive() || players[1]->GetInteractive()) {
				cout << "########" << endl << "the player that won the set was " << players[0]->GetName() << endl;
			}
		}
		else {
			players[1]->SetSets(players[1]->GetSets() + 1);
			if(players[0]->GetInteractive() || players[1]->GetInteractive()) {
				cout << "########" << endl << "the player that won the set was " << players[1]->GetName() << endl;
			}
		}
	}

	//adding score to stats matrix, check if player got more sets than the other
	if (players[0]->GetSets() > players[1]->GetSets()) {
		stats[0][players[1]->GetSets()]++;
		if(players[0]->GetInteractive() || players[1]->GetInteractive()) {
			cout << endl << endl << "OH BOY LOOK AT THAT" << endl << "the player that won the competition was " << players[0]->GetName() << endl << endl;
		}
	}
	else {
		stats[1][players[0]->GetSets()]++;
		if (players[0]->GetInteractive() || players[1]->GetInteractive()) {
			cout << endl << endl << "OH BOY LOOK AT THAT" << endl << "the player that won the competition was " << players[1]->GetName() << endl << endl;
		}
	}
	
}
void GameRunner::RunSet() {
	
	players[0]->SetGameWins(0);
	players[1]->SetGameWins(0);

	//start of set
	while ((players[0]->GetGameWins() != 3) && (players[1]->GetGameWins() != 3)) {

		current_player = starting_player;

		//starts a game
		this->RunGame();
		if (players[0]->GetInteractive() || players[1]->GetInteractive()) {
			cout << endl << "***the player that WON the game was " << winner->GetName() << "***" << endl << endl;
		}
		//add 1 to the wins of player that won this round
		winner->SetGameWins(winner->GetGameWins() + 1);

		//change first player
		starting_player = current_player;

	}
}
void GameRunner::RunGame() {
	int save;

	players[0]->SetScore(501); // reseting sids score
	players[1]->SetScore(501); // reseting joes score

	winner = nullptr;

	while (winner == nullptr) {

		//reset darts
		current_player->SetDarts(3);



		//turn
		this->RunTurn();
	}
}
void GameRunner::RunTurn() {
	int save;
	//printing the relevant information for user after each play
	if (current_player->GetInteractive()) {
		string name;

		cout << endl << "IT IS YOUR TURN" << endl;

		if (players[0]->GetInteractive()) {
			name = "you have";
		}
		else {
			name = players[0]->GetName();
		    name.append(" has");
		}
		cout << "-----------------------" << endl;
		cout << name << " won " << players[0]->GetSets() << " sets" << endl;
		cout << name << " won " << players[0]->GetGameWins() << " games" << endl;
		cout << name << " " << players[0]->GetScore() << " points" << endl << endl;
		

		if (players[1]->GetInteractive()) {
			name = "you have";
		}
		else {
			name = players[1]->GetName();
			name.append(" has");
		}
		cout << name << " won " << players[1]->GetSets() << " sets" << endl;
		cout << name << " won " << players[1]->GetGameWins() << " games" << endl;
		cout << name << " " << players[1]->GetScore() << " points" << endl;
		cout << "-----------------------" << endl << endl;
	}
	//saving score so that i can go back to it 
	//in case it gets to invalid score
	save = current_player->GetScore();
	//run the appropriate strategy to the player 
	while (current_player->GetDarts() > 0) {

		if (current_player->GetInteractive()) 
		{
			winner = current_player->InteractiveStrategy();
		}
		else if(current_player->GetStrategy() == "simple")
		{
			winner = current_player->SimpleStrategy();
		}
		else if(current_player->GetStrategy() == "enhanced")
		{
			winner = current_player->EnhancedStrategy();
		}
		else
		{
			cout << "no valid strategy" << endl;
		}
		if (winner != nullptr) {
			break;
		}

		// avoid negative values
		if (current_player->GetScore() <= 1) {
			current_player->SetScore(save);
			current_player->SetDarts(0);
		}
		//decrease amount of darts by 1
		current_player->SetDarts(current_player->GetDarts() - 1);
	}
	// invert player after end of turn
	if (current_player == players[0]) {
		current_player = players[1];
	}
	else {
		current_player = players[0];
	}
}
void GameRunner::InteractiveGame() {
	int which;
	cout << "about player 1 (" << players[0]->GetName() << "): chance to hit bull is " << players[0]->GetRateB() << "%"
		 << " treble is " << players[0]->GetRateT() << "%" << endl;
	cout << "about player 2 (" << players[1]->GetName() << "): chance to hit bull is " << players[1]->GetRateB() << "%"
		<< " treble is " << players[1]->GetRateT() << "%" << endl << endl;
	cout << "which player would you like to be?(1 or 2)" << endl;
	cin >> which;
	players[which-1]->SetInteractive(true);
	RunCompetition();
}