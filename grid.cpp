#include "grid.h"

#include <cstdlib>
#include <time.h>
using namespace std;

Grid::Grid()
// Default constructor
{
	// NULL indicates that these are pointers! (to not yet allocated memory)
	number_grid = NULL;
	temp_score = 0;
	dimen = 0;
}

// Destructor to delete allocated memory
Grid::~Grid()
{

	 if(number_grid!=NULL)
	 {
		for (int i = 0; i < dimen ; i++)
	 	{
	 		delete []number_grid[i];
	 	}
		delete []number_grid;
	 }
}

// Getters: Return Values.
int Grid::get_dimen()
{
	return dimen;
}

// Getter: return values ... needs to send score for high score comparison
int Grid::get_temp_score()
{
	return temp_score;
}

// take in starting dimen, allocate, and call on other starting functions
void Grid::allocate()
{
	// Prompt the user to enter the dimen they want to play with
	cout << "Welcome to 2048! What length Grid would you like to play with?"
		 << endl;
	cin >> dimen;

	// dynamically allocate Grid
	number_grid = new int*[dimen];

	for (int i = 0; i < dimen; i++)
		{
			number_grid[i] = new int[dimen];
		}

	// prints out starting game and calls to populate and print the Grid
	cout << "Starting Game!" << endl;
	populate_number_grid();
	print_grid();
}

//void Grid::populate_number_grid()
// populate the starting Grid with 2'2s and the rest 0's
void Grid::populate_number_grid()
{
	int rand_row;
	int rand_col;
	int rand_row2;
	int	rand_col2;
	// makes 4 random tiles and makes sures that they aren't the same spot
	do
	{
		srand(time(NULL));
		// randomly populate with 2 2's
		rand_row = rand()%dimen;
		rand_col = rand()%dimen;
		rand_row2 = rand()%dimen;
		rand_col2 = rand()%dimen;

	} while((rand_row == rand_row2) && (rand_col == rand_col2));

	number_grid[rand_row][rand_col] = 2;
	number_grid[rand_row2][rand_col2] = 2;

	// make the rest of the Grid 0's (2's on boar stay)
	for (int i = 0; i < dimen; i++)
	{
		for (int j = 0; j < dimen; j++)
		{
			if (number_grid[i][j] != 2)
				number_grid[i][j] = 0;
		}
	}
}

// void Grid::print_Grid()
// print the Grid out and check line spacing
// depedning on how large the number is, the spacing will decrease accordingly
void Grid::print_grid()
{
		cout << "Current Score: " << temp_score << endl;

	for (int i = 0; i < dimen; i++)
	{
		for (int j = 0; j < dimen; j++)
		{
			// conditions to check for size of number
			// will then give it proper spacing so Grid is still organized
			if (number_grid[i][j] == 0)
				cout << "X" << "    " ;
			else if(number_grid[i][j] < 10)
				cout << number_grid[i][j] << "    ";
			else if(number_grid[i][j] >= 10 && number_grid[i][j] <100)
				cout << number_grid[i][j] << "   ";
			else if(number_grid[i][j] >= 100 && number_grid[i][j] <1000)
				cout << number_grid[i][j] << "  ";
			else if(number_grid[i][j] >= 1000 && number_grid[i][j] <10000)
				cout << number_grid[i][j] << " ";
			else
				cout << number_grid[i][j] << "";
		}
		cout << endl << endl;
	}
}

// bool Grid::check_Grid()
// checks every adjacent non diagonal piece that is IN BOUNDS
// checks to see if any more moves can be made
bool Grid::check_grid()
{
	// nested loop to check every piece... returns false if game is not over
	for (int i = 0; i < dimen; i++)
	{
		for (int j = 0; j < dimen; j++)
		{
			if (number_grid[i][j] == 0)
			{
				return false;
	   		}
	   		else if ((i+1 < dimen)&&(number_grid[i][j]==number_grid[i+1][j]))
	   			return false;
	   		else if ((i-1 >= 0)&&(number_grid[i][j]==number_grid[i-1][j]))
	   			return false;
	   		else if ((j+1 < dimen)&&(number_grid[i][j]==number_grid[i][j+1]))
	   			return false;
	   		else if ((j-1 >= 0)&&(number_grid[i][j]==number_grid[i][j-1]))
	   			return false;
  	    }
	}
	return true;
}

// bool Grid::move_right()
// this is a bool because it also checks to see if a move has been made
bool Grid::move_up()
{
	int count = 0;
	for (int k = 0; k < dimen; k++)
	{
		for (int i = 1; i < dimen; i++)
		{
			for (int j = 0; j < dimen; j++)
			{
				if (number_grid[i-1][j] == 0 ||
					number_grid[i][j] == number_grid[i-1][j])
				{
					if (number_grid[i][j] != 0)
						count++;

					// if the piece in the up direction is 0, move into it
					int temp = number_grid[i][j];
					number_grid[i][j] = number_grid[i-1][j];
					number_grid[i-1][j] = temp;

				}
			}
		}
	}
		// returns a bool to check to see if a new tile should be made
		if (count != 0)
			return true;
		else
			return false;
}

// bool Grid::move_right()
// this is a bool because it also checks to see if a move has been made
bool Grid::move_down()
{
	int count = 0;
	for (int k = 0; k < dimen; k++)
	{
		for (int i = dimen-2; i >= 0 ; i--)
		{
			for (int j = 0; j < dimen; j++)
			{
				if (number_grid[i+1][j] == 0||
					number_grid[i][j] == number_grid[i+1][j])
				{
					if (number_grid[i][j] != 0)
						count++;

					// if the piece in the down direction is 0, move into it
					int temp = number_grid[i][j];
					number_grid[i][j] = number_grid[i+1][j];
					number_grid[i+1][j] = temp;
				}
			}
		}
	}
	// returns a bool to check to see if a new tile should be made
		if (count != 0)
			return true;
		else
			return false;
}

// bool Grid::move_right()
// this is a bool because it also checks to see if a move has been made
bool Grid::move_left()
{
	int count = 0;
	for (int k = 0; k < dimen; k++)
	{
		for (int i = 0; i < dimen; i++)
		{
			for (int j = 1; j < dimen ; j++)
			{
				if (number_grid[i][j-1] == 0 ||
					number_grid[i][j] == number_grid[i][j-1])
				{
					if (number_grid[i][j] != 0)
						count++;

					// if the piece in the left direction is 0, move into it
					int temp = number_grid[i][j];
					number_grid[i][j] = number_grid[i][j-1];
					number_grid[i][j-1] = temp;

				}
			}
		}
	}
	// returns a bool to check to see if a new tile should be made
		if (count != 0)
			return true;
		else
			return false;
}

// bool Grid::move_right()
// this is a bool because it also checks to see if a move has been made
bool Grid::move_right()
{
	int count = 0;
	for (int k = 0; k < dimen; k++)
	{
		for (int i = 0; i < dimen; i++)
		{
			for (int j = dimen-2; j >= 0 ; j--)
			{
				if (number_grid[i][j+1] == 0 ||
					number_grid[i][j+1] == number_grid[i][j])
				{
					if (number_grid[i][j] != 0)
						count++;

					// if the piece in the right direction is 0, move into it
					int temp = number_grid[i][j+1];
					number_grid[i][j+1] = number_grid[i][j];
					number_grid[i][j] = temp;

				}
			}
		}
	}
	// returns a bool to check to see if a new tile should be made
		if (count != 0)
			return true;
		else
			return false;
}

//void Grid::combine_up()
//combines all feasible possibilites that can be made moving up
void Grid::combine_up()
{
	// nested loop to check the pieces moving while shifting upwards
	for (int i = 1; i < dimen; i++)
	{
		for (int j = 0; j < dimen; j++)
		{
			if (number_grid[i-1][j] == number_grid[i][j])
			{
				number_grid[i-1][j] += number_grid[i][j];
				temp_score += number_grid[i-1][j];
				number_grid[i][j] = 0;
			}
		}
	}
}

//void Grid::combine_dowb()
//combines all feasible possibilites that can be made moving down
void Grid::combine_down()
{
	// nested loop to check the pieces moving while shifting downward
	for (int i = dimen-2; i >= 0 ; i--)
	{
		for (int j = 0; j < dimen; j++)
		{
			if (number_grid[i+1][j] == number_grid[i][j])
			{
				number_grid[i+1][j] += number_grid[i][j];
				temp_score += number_grid[i+1][j];
				number_grid[i][j] = 0;
			}
		}
	}
}

//void Grid::combine_left()
//combines all feasible possibilites that can be made moving left
void Grid::combine_left()
{
	// nested loop to check the pieces moving while shifting in the left direction
	for (int i = 0; i < dimen; i++)
	{
		for (int j = 1; j < dimen ; j++)
		{
			if (number_grid[i][j-1] == number_grid[i][j])
			{
				number_grid[i][j-1] += number_grid[i][j];
				temp_score += number_grid[i][j-1];
				number_grid[i][j] = 0;
			}
		}
	}
}

//void Grid::combine_right()
//combines all feasible possibilites that can be made moving right
void Grid::combine_right()
{
	// nested loop to check the pieces moving while shifting in the right direction
	for (int i = 0; i < dimen; i++)
	{
		for (int j = dimen-2; j >= 0 ; j--)
		{
			if (number_grid[i][j+1] == number_grid[i][j])
			{
				number_grid[i][j+1] += number_grid[i][j];
				temp_score += number_grid[i][j+1];
				number_grid[i][j] = 0;
			}
		}
	}
}

// void Grid::make_tile()
// generate a random tile on an edge piece
void Grid::make_tile()
{
	bool filled = false;
	int new_tile = rand()%10+1;
	// while loop to make sure that it generates a tile
	while (filled != true)
	{
		int row = rand()%dimen;
		int col = rand()%dimen;
		// must check that the piece is on an edge, 90% chance for a 2
		if ((new_tile <= 9) && (number_grid[row][col] == 0 ) &&
			((row == 0) || (row == dimen-1) ||(col == 0)|| (col == dimen-1)))
		{
				number_grid[row][col] = 2;
				filled = true;
		}
		else
		{
			if (((row == 0) || (row == dimen-1) ||(col == 0)|| (col==dimen-1))
				&& (number_grid[row][col] == 0 ))
			{
				number_grid[row][col] = 4;
				filled = true;
			}
		}
	}
}
