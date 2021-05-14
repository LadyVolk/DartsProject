#include "pch.h"
#include "Player.h"
#include "Plays.h"
#include <iostream>
using namespace std;
Player::Player(string _name, int _b_rate, int _t_rate, string _strategy)
{
	interactive = false;
	name = _name;
	b_rate = _b_rate;
	t_rate = _t_rate;
	strategy = _strategy;
}

Player::~Player()
{
}

// getters
int Player::GetScore() {
	return score;
}
int Player::GetDarts() {
	return darts;
}
string Player::GetName() {
	return name;
}
int Player::GetRateB() {
	return b_rate;
}
int Player::GetRateT() {
	return t_rate;
}
int Player::GetSets() {
	return sets_wins;
}
int Player::GetGameWins() {
	return game_wins;
}
string Player::GetStrategy()
{
	return strategy;
}
bool Player::GetInteractive() {
	return interactive;
}


// setters
void Player::SetScore(int _score) {
	score = _score;
}
void Player::SetDarts(int _darts) {
	darts = _darts;
}
void Player::SetSets(int win) {
	sets_wins = win;
}
void Player::SetGameWins(int win) {
	game_wins = win;
}
void Player::SubScore(int amount) {
	score -= amount;
}
void Player::SetInteractive(bool _interactive) {
	interactive = _interactive;
}

//tries to always get maximum amount of points
Player* Player::SimpleStrategy() {
	int target;

	if (GetScore() >= 62) {
		SubScore(throw_treble(20, GetRateT()));
	}
	else if (GetScore() > 50) {
		target = GetScore() - 50;
		SubScore(throw_single(target));
	}
	else if (GetScore() == 50) {
		SubScore(throw_bull(GetRateB()));
		if (GetScore() == 0) {
			return this;
		}
	}
	else if (GetScore() > 40) {
		target = GetScore() - 40;
		SubScore(throw_single(target));
	}
	else if ((GetScore() % 2 == 0) && (GetScore() != 0)) {
		target = GetScore() / 2;
		SubScore(throw_double(target));
		if (GetScore() == 0) {
			return this;
		}
	}
	else if ((GetScore() % 2 == 1) && (GetScore() != 1)) {
		SubScore(throw_single(1));
	}
	return nullptr;
}

//created by me with try and error
//several techniques that improve the win ration over the simple strategy
Player* Player::EnhancedStrategy(){
	//small increase
	//take more risk to try to compensate having less darts, get to 50 to win with bull
   if(GetDarts() == 2 && GetScore() <= 107 && GetScore() >= 98 && GetScore()%3 == 2){
	   SubScore(throw_treble((GetScore() - 50) / 3, t_rate));
   }
	
	//high increase
	//plays to get to 40 points with single
	else if (GetScore() >= 41 && GetScore() <= 60 && GetScore() != 50) {
			SubScore(throw_single(GetScore() - 40));
	}
	
    //small increase
	//plays to get to 32 with single
	else if ((GetScore() <= 52 && GetScore() >= 41 && GetScore() != 50) ||
		GetScore() <= 39 && GetScore() >= 33 && GetScore() % 2 == 1){
			SubScore(throw_single(GetScore() - 32));
		}
	
	//small increase
	//plays to get to 40 points with doubles
	else if (GetScore() >= 62 && GetScore() <= 80 && GetScore() % 2 == 0){
		SubScore(throw_double((GetScore() - 40) / 2));
	}
	else {
		return SimpleStrategy();
	}
	return nullptr;
}

//give user the play options in-game
Player* Player::InteractiveStrategy() {
	int play_choice, number, result;

	cout << "you have " << GetDarts() << " dart(s)" << endl;
	cout << "what do you want to do?" << endl << endl;
	cout << "you can aim for single(1), double(2), treble(3) and bull(4)" << endl;
	cin >> play_choice;
	
	switch (play_choice) {
	case 1:
		cout << "now choose one number from 1 to 20" << endl;
		cin >> number;
		result = throw_single(number);
		cout << ">you got " << result << " points" << endl;
		SubScore(result);
		break;
	case 2:
		cout << "now choose one number from 1 to 20" << endl;
		cin >> number;
		result = throw_double(number);
		cout << ">you got " << result << " points" << endl;
		SubScore(result);
		if (GetScore() == 0) {
			return this;
		}
		break;
	case 3:
		cout << "now choose one number from 1 to 20" << endl;
		cin >> number;
		result = throw_treble(number, t_rate);
		cout << ">you got " << result << " points" << endl;
		SubScore(result);
		break;
	case 4:
		result = throw_bull(b_rate);
		cout << ">you got " << result << " points" << endl;
		SubScore(result);
		if (GetScore() == 0) {
			return this;
		}
		break;
	}
	cout << ">you have " << GetScore() << " points left" << endl << endl;
	return nullptr;
		
}
