#include "pch.h"
#include <iostream>
#include <time.h>
#include <string>
#include <vector>
#include <cstdlib>
#include "Player.h"
#include "GameRunner.h"
using namespace std;

int main() {

	char choice;
	int tests;

	//define attributes of players
	GameRunner game_runner(new Player("sid", 71, 61, "simple"), new Player("joe", 73, 63, "enhanced"));
	
	//randomizing the seed of random
	srand(time(NULL));

	cout << "Would you like to interact with the test?('y' or 'n')" << endl;
	cin >> choice;

	if (choice == 'n') {
		cout << "how many tests would you like to run?" << endl;
		cin >> tests;
		game_runner.RunTests(tests);
	}
	else if (choice == 'y') {
		game_runner.InteractiveGame();
	}


	return 0;
}
