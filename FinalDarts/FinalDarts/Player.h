#pragma once
#include <string>
using namespace std;
class Player
{
private:

	string name;
	int score;
	int sets_wins;
	int game_wins;
	int darts;
	int b_rate;//rate to hit bull
	int t_rate;//rate to hit treble
	string strategy;
	bool interactive; //to check if it is human playing

public:
	Player(string name, int _b_rate, int _t_rate, string _strategy);
	~Player();

	//getters
	int GetScore();
	int GetDarts();
	string GetName();
	int GetRateB();
	int GetRateT();
	int GetSets();
	int GetGameWins();
	string GetStrategy();
	bool GetInteractive();

	//setters
	void SetScore(int _score);
	void SetDarts(int _darts);
	void SetSets(int win);
	void SetGameWins(int win);
	void SubScore(int amount);
	void SetInteractive(bool _interactive);

	//strategies
	Player* SimpleStrategy();
	Player* EnhancedStrategy();
	Player* InteractiveStrategy();
};
