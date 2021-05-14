#pragma once
#include <vector>
#include "Player.h"
class GameRunner
{
private:
	int stats[2][7];
	vector <Player*> players;
	Player* starting_player;
	Player* current_player;
	Player* winner;
public:
	GameRunner(Player* player_1, Player* player_2);
	~GameRunner();

	void RunTests(int tests);
	void PrintResults(int tests);
	void RunCompetition();
	void RunSet();
	void RunGame();
	void RunTurn();
	void InteractiveGame();
};

