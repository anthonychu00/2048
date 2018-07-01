#include <iostream>
 using namespace std;

 #ifndef GRID_H_
 #define GRID_H_

 class Grid
 {
 	/* 2 private attributes: a dynamically allocated array of ints (this
 	will be set to null in constructor) and int dimen, which takes the
 	dimen user enters from allocate() in order to start the game */
 	private:
 		// Attributes of the grid
 		int **number_grid;
 		int dimen;
 		int temp_score;

 	public:
 		// Contructor and Desructor
 	    Grid();
 	    ~Grid();

 	    /* Setters and Getters ** TA's in halligan said don't make
 	    setters or getters for things you dont need to set or get */
 	    int get_dimen();
 	    int get_temp_score();

 	    // Functions
 	    void allocate(); /* prompts user for dimens - allocates starting
 	    Grid with this value and calls number_grid() and print_grid()
 	    ... returns nothing */

 		void populate_number_grid(); /* generates starting Grid of ints
 		where two randomly selected tiles are set to 2 and the rest are set
 		to 0
 		... returns nothing */

 		void print_grid(); /* aligns spacing,then prints out Grid to screen:
 		if number is 0, then print out an X while if not, print out that
 		number ... returns nothing */

 		bool check_grid(); /* check to see if the Grid is full or if no more
 		moves can be made - if game is full, return bool gameover = true,
 		if not, retrun bool variable as is (false) */

 		bool move_up(); // moves the tiles on Grid up, returns nothing
 		bool move_down(); // moves the tiles on Grid down, returns nothing
 		bool move_left(); // moves the tiles on Grid left. returns nothing
 		bool move_right(); // move the tiles on Grid right, returns nothing

 		void combine_up(); // actually combines like pieces
 		void combine_down(); // actually combines like pieces
 		void combine_left();// actually combines like pieces
 		void combine_right();// actually combines like pieces

 		void make_tile(); /* makes new tile (90%-2 10%-4) in random position
 		that has a value of 0... makes the 0 into either a 2 or a 4)
 		... returns nothing */

 };

 #endif
