#include "game.h"
#include <iostream>
#include <fstream>

using namespace std;

// declare filename as a const
const char *FILENAME = "scores.txt";

// Default contructor sets
Game::Game()
{
	score = 0;
	gameover = false;

	count_people = 0;
	names = NULL;
	scores = NULL;
}
// Default desructor deletes dynamically allocated mem after running
Game::~Game()
{
	delete []names;
	delete []scores;
}

// setters and getters defintions
bool Game::get_bool()
{
	return gameover;
}

void Game::start_game()
{
	b.allocate();
}

void Game::player_move()
{
	char play_move;
		cout << "Your move!" << endl;
		cin >> play_move ;

		if (play_move == 'w')
			up();
		else if (play_move == 'a')
			left();
		else if(play_move == 'd')
			right();
		else if(play_move == 's')
			down();
		else if(play_move == 'q')
			gameover = true;
		else if(play_move == 'h')
		{
			number_users();
			allocate_scores();
			fill_arrays();
			five_highscores();
		}
}

// Void Game::right()
// moves the pieces to the right, and makes sure than a new tile can be made
// if there are pieces that can be moved or combined, if not, tile is not made
void Game::right()
{
	bool made_move;
	made_move = b.move_right();
	b.combine_right();
    b.move_right();
    // if the first call resulted in a moved piece, make a tile
	if (made_move == true)
		b.make_tile();

	b.print_grid();
}

// Void Game::left()
// moves the pieces to the left, and makes sure than a new tile can be made
// if there are pieces that can be moved or combined, if not, tile is not made
void Game::left()
{
	bool made_move;
	made_move = b.move_left();
	b.combine_left();
	b.move_left();
	// if the first call resulted in a moved piece, make a tile
	if (made_move == true)
		b.make_tile();

	b.print_grid();
}

// Void Game::up()
// moves the pieces up, and makes sure than a new tile can be made
// if there are pieces that can be moved or combined, if not, tile is not made
void Game::up()
{
	bool made_move;
	made_move = b.move_up();
	b.combine_up();
	b.move_up();
	// if the first call resulted in a moved piece, make a tile
	if (made_move == true)
		b.make_tile();

	b.print_grid();
}

// Void Game::down()
// moves the pieces down, and makes sure than a new tile can be made
// if there are pieces that can be moved or combined, if not, tile is not made
void Game::down()
{
	bool made_move;
	made_move = b.move_down();
	b.combine_down();
	b.move_down();
	// if the first call resulted in a moved piece, make a tile
	if (made_move == true)
		b.make_tile();

	b.print_grid();
}

// bool Game::check_game()
// checks to see if the board is full an unmovable, returns a bool accordingly
bool Game::check_game()
{
	return b.check_grid();
}

// void Game::number_users()
// uses file i/o to run through file and increments private var count_people
void Game::number_users()
{
	string name_current;
	int scores_current;
//	int count = 0;

	ifstream infile;
	infile.open(FILENAME);

	if (!infile.is_open())
	{
		create_file();
	}

	while (!infile.eof())
	{
		infile >> name_current;
		// Look for -1 as the end point
		if (name_current == "-1")
			break;
		count_people++;

		infile >> scores_current;
	}
	infile.close();
}

// void Game::allocate_scores()
// allocate two new arrays depending on size that number_users updated
void Game::allocate_scores()
{
	names = new string[count_people];
	scores = new int[count_people];
}

//void Game::fill_arrays()
//fill up the 2 arrays from the file
void Game::fill_arrays()
{
	// 3 variables, 2 for inputs and 1 to keep count
	string name_current;
	int scores_current;
	int count = 0;

	ifstream infile;
	infile.open(FILENAME);

	if (!infile.is_open())
		cerr << "Problem with file!" << endl;
	// pass in file data into 2 separate arrays
	while (!infile.eof())
	{
		infile >> name_current;
		if (name_current != "-1" && !infile.eof())
		{
			names[count] = name_current;
			infile >> scores_current;
			scores[count] = scores_current;
			count++;
		}
	}
	infile.close();
}

//void Game::prompt_name()
//ask the user for their name after the game and update the highscore
//list according to what their highscore is
void Game::prompt_name()
{
	cout << "Please enter your name!" << endl;
	cin >> user_name;
	int place = 0;
	int i = 0;

	// use a for loop to find where the user's score should be in the array
	// this is in order to keep the whole thing sorted properly
	for (i = 0; i < count_people; i++)
	{
		if (b.get_temp_score() >= scores[i])
		{
			place = i;
			break;
		}
	}
	// if the loop makes it all the way to the end, put the score at the end
	if (i == count_people)
		place = count_people;

	highscore_file(place);

}

//void Game:::highscore_file(int place)
//uses the place in highscore file found from given from prompt_name
//rewrites the file with new order
void Game::highscore_file(int place)
{
	// open the ofstream
	ofstream outfile;
	outfile.open(FILENAME);

	if (count_people == 0)
	{
		outfile << user_name << " " << b.get_temp_score() << endl;
		cout << "You are the top Highscore!" << endl;
	}
	else
	{	// overwrites with names and scores leading up to new input
		for (int j = 0; j < place; j++)
			outfile << names[j] << " " << scores[j] << endl;
		// puts in the new input
		outfile << user_name << " " << b.get_temp_score() << endl;
		// finishes writing in names and scores for people after new input
		for (int k = place; k < count_people; k++)
			outfile << names[k] << " " << scores[k] << endl;
		// if user has highscore, let them know
		if (place == 0)
			cout << "You are the TOP highscore!" << endl;

		outfile << "-1" << endl;
		outfile.close();
	}
}

// void Game::five_highscore()
// prints out the top 5 highscores while its not the end of the file
// this function works well if the highscore file already has 5 players in it
void Game::five_highscores()
{
	string name_current; //infiles string variable
	int scores_current;  //infiles int variable
	int count = 0; // count increments each time so the arrays can update
	ifstream infile;

	infile.open(FILENAME);

	if (!infile.is_open())
		cerr << "Problem with file!" << endl;
	// it will go through the file so its okay if there are less than 5 scores
	while (!infile.eof())
	{
		if (count == 5)
			break;
		else
		{
			infile >> name_current;
			if ((name_current != "-1"))
			{
				names[count] = name_current;
				infile >> scores_current;
				scores[count] = scores_current;
				cout << names[count] << " " << scores[count] << endl;
				count++;
			}
		}
	} infile.close();
}

// void Game::first_highscore()
// gets the first highscore and also tells user if no highscores have been set
void Game::first_highscore()
{
	string name_current;
	int scores_current;
	int count = 0;

	ifstream infile;
	infile.open(FILENAME);

	if (!infile.is_open())
		cerr << "Problem with file!" << endl;

	// takes the highest score from the file and then prints it out
	// when the game begins
	infile >> name_current;
	if (name_current != "-1")
	{
		names[count] = name_current;
		infile >> scores_current;
		scores[count] = scores_current;
		cout << "Top Highscore: " << scores[count] << endl;
	}
	else
		cout << "No Highscores Yet! You'll be the first!" << endl;

	infile.close();
}

// void Game::edit_highscore()
// calls the member functions that will allow the user to enter name into list
void Game::edit_highscores()
{
	number_users();
	allocate_scores();
	fill_arrays();
	prompt_name();
	five_highscores();
}

//void Game::print_first_highscore()
// prints out the first highscore when game is initally called
void Game::print_first_highscore()
{
	number_users();
	allocate_scores();
	fill_arrays();
	first_highscore();
}

//void Game::create_file()
//creates a file in case there is not one already made
void Game::create_file()
{
	ofstream outfile;
	outfile.open(FILENAME);
	outfile.close();
}
