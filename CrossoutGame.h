/**
 * Name: CrossoutGame.h
 *
 * Description:  Header file for a Crossout Game.
 *
 * $Id: CrossoutGame.h,v 1.2 2012/11/07 19:10:46 jem4687 Exp jem4687 $
 *
 * Revisions:
 * $Log: CrossoutGame.h,v $
 * Revision 1.2  2012/11/07 19:10:46  jem4687
 * Pretty up the comments
 *
 * Revision 1.1  2012/11/03 02:00:56  jem4687
 * Initial revision
 *
 *
 * @author:Jesse Martinez
 */

#ifndef CROSSOUT_H
#define CROSSOUT_H

#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include "Game.h"

typedef triple< int, int, std::vector< std::vector<int> > > trip;

class CrossoutGame: public Game
{
	private:
		// Pair that holds player character and player type
		std::pair<std::string,std::string> p1;
		std::pair<std::string,std::string> p2;

		// Default move to be made if no good move is found
		int MAX;

	public:
		/**
		 * Constructor
		 *
		 * Description:  Creates a game of crossout between the user and
		 *		 the pc with the initial max num and length
		 *
		 * @param int    - A "dummy" int to differentiate the
		 *		   interactive mode from the solver mode.
		 *        max    - The max amount you can take.
		 *        length - Length of board.
		 */
		CrossoutGame( const int , int max , int length );

		/**
		 * Constructor
		 *
		 * Description:  Creates a game of crossout to be ran in solver
		 * mode.
		 *
		 * @param max    - The max amount you can take.
                 *        length - Length of board.
		 */
		CrossoutGame( int max , int length );

		/**
		 * Name:  generateBoard
		 *
		 * Description: Generates the board with 1 to length based off
		 * of the strings received from the command line arguments.
		 *
		 * @param b     - The board( a dummy board for this game ).
		 */
		void generateBoard( std::vector<std::string> b );

		/**
		 * Name: move
		 *
		 * Description:  Calls the proper move function based on the
		 *               received player number.  Removes the ammount
		 *               of columns the player chose.
		 *
		 * @param p      - The number representing whose turn it is.
		 */
		void move( const int p );

		/**
		 * Name: moveHuman
		 *
		 * Description: Asks for user input on how many pins to take
		 * away.
		 *
		 * @param p     - A string representing either player "X" or
		 *		  "O".
		 *
		 * @return      The number of columns chosen.
		 */
		int moveHuman( const std::string p );

		/**
		 * Name: movePC
		 *
		 * Description: Move for PC player calls the solver algorithim
		 *		to find the best possible move given for the
		 * 		current successor, and sets to board to the
		 *		best possible board.
		 *
		 * @param turn      - Integer to keep track of the turn.
		 *        successor - The current successor of a crossout
		 * 		      configuration.
		 *
		 * @return      A triple that holds the best score, the best
		 * 		move, and the best board.
		 */
		trip movePC( const int turn, std::vector< trip > successor );

		/**
		 * Name: findSuccessors
		 *
		 * Description: Generates all possible valid moves.
		 *
		 * @param b     - The current board, the number of columns to take
		 *		away, and the number of remaining columns you can take from.
		 *
		 * @return      A vector of all the successors.
		 */
		std::vector< trip > findSuccessors( trip b );

		/**
		 * Name: print
		 *
		 * Description: Prints an number in each column
 		 */
		void print();

		/**
		 * Name: getName
		 *
		 * Description: Returns the name of the player received.
		 *
		 * @param p     - An integer representing whose turn it is.
		 *
		 * @return      String representation of the current player.
		 */
		std::string getName( const int ) const;

		/**
		 * Name: checkBaseCase
		 *
		 * Description:  Determines if a base case has been reached.
		 *
		 * @param check  - A vector of the remaining moves.
		 *
		 * @return       True iff there are no remaining moves.
		 */
		bool checkBaseCase( const std::vector< trip > check ) const;

		/**
		 * Name: baseCase
		 *
		 * Description: Returns a standard base case representation
		 * for the crossout game.  For this game it is a score of -1 a
		 * move of last legal column and an empty board.
		 *
		 * @return      A triple with a score, move, and board.
		 */
		trip baseCase() const;

		/**
		 * Name: invert
		 *
		 * Description: A dummy function to only be used in
		 * Connect3Game.
		 *
		 * @return      A board.
		 */
		std::vector< std::vector<int> > invert(
		std::vector< std::vector<int> > b );

		/**
 		 * Name: findNum
 		 * Decription: Find and return the location of the number received
 		 *             in the board, or -1 if not found
 		 *
 		 * @param n    - Number to search for in the board
 		 *
 		 * @return     Integer location of number in board or -1 if not found
 		 */
		int findNum( int n );

};

#endif
