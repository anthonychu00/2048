#include <iostream>
#include "game.h"
using namespace std;

int main()
{
	Game play;

	// introduce the game and give the instructions for it
	cout << "Instructions:" << endl << endl;
	cout << "w = up, a = left, s = down, d = right" << endl;
	cout << "q = quit, h = view scores" << endl << endl;

	// call start_game which allocates and prints board
	play.start_game();
	play.print_first_highscore();

	// plays the game for as long as game is not over
	while (!play.check_game() && !play.get_bool())
	{
		play.player_move();
	}

	// let user know game is over and then records their name/score
	cout << "Game is over! GG mate. " << endl;
	play.edit_highscores();

}
