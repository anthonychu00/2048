#include <iostream>
#include <string>
#include "grid.h"
using namespace std;

#ifndef GAME_H_
#define GAME_H_


class Game
{
	/* 3 private attributes, int score holds the updated score after each
	move the user makes, and a boolean checks if the game is over since
	player_move(), check_game(), and print_score() will be in a while loop
	for as long as gameover = false) */

	private:
	Grid b;
	int score;
	bool gameover;

	// these are variables specific to file i/o
	// no need to get/set
	int count_people;
	string user_name;
	string *names;
	int *scores;

	public:
	// constructor
		Game();
		~Game();

		// getter that checks if game is over
		 /* Setters and Getters ** TA's in halligan said don't make
 	    setters or getters for things you dont need to set or get */
		bool get_bool();


	// FUNTIONS TO PLAY

		void start_game(); /* calls allocate() function from Grid class
		... returns nothing */

		void player_move(); /* prompt's for user's move/decides what to do
		& calls function make_move() from Grid class if a, s, d, or w,
		else if q, set gameover = true, else if h, call five_highscore
		function ... returns nothing*/

		bool check_game(); /* calls check_Grid from Grid class, if game
		is over, returns the bool gameover as true and game is over */

		void print_score(int); /* prints the score out every round
		... passes in current score ... returns nothing */

		void right(); // moves the Grid to the right
		void left(); // moves the Grid to the lest
		void up(); // moves the Grid up
		void down(); // moves the Grid down


		void number_users(); // gets the # of how many players have played
		void allocate_scores(); // aollocate the arrays
		void fill_arrays(); // overwrite the file with values from arrays
		void prompt_name(); // gets users name and stores in highscore file

		void five_highscores(); /* opens file i/o and gets the top 5 highscores
		to store in an array that is then printed to the screen... this
		function is used if user selects "h" during the move
		... returns nothing */
		void first_highscore(); // gets the first highscore

		void edit_highscores(); /* take's user's name (promted for)
		after game is over, opens/edits file i/o, and places name so that
		name above that a higher score and name below has a lower score
		... returns nothing */
		void print_first_highscore(); // prints out the first highscore
		void create_file() ;// make a few file in case there is not one

		void highscore_file(int); //organizes the highscore file

};

#endif
