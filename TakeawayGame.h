/**
 * Name: TakeawayGame.h
 * Description: The header file for a Takeaway Game.
 *
 * $Id: TakeawayGame.h,v 1.5 2012/11/07 19:10:46 jem4687 Exp jem4687 $
 *
 * Revisions
 * $Log: TakeawayGame.h,v $
 * Revision 1.21  2012/11/07 19:10:46  jem4687
 * Pretty up the comments
 *
 * Revision 1.20  2012/10/29 02:40:02  mal4012
 * Minor comment changes.
 *
 * Revision 1.19  2012/10/25 00:45:24  jem4687
 * Changed findsuccessors to receive a trip
 *
 * Revision 1.18  2012/10/21 18:16:29  mal4012
 * Changed comments.
 *
 * Revision 1.17  2012/10/16 02:28:28  jem4687
 * changed findsuccessor params
 *
 * Revision 1.16  2012/10/15 22:05:03  jem4687
 * added generateBoard
 *
 * Revision 1.15  2012/10/15 21:40:40  jem4687
 * added triple container
 *
 * Revision 1.14  2012/10/15 18:05:07  mal4012
 * Changed a few formatting issues.
 *
 * Revision 1.13  2012/10/15 17:18:21  jem4687
 * changed pennies to data
 *
 * Revision 1.12  2012/10/10 22:30:06  jem4687
 * included inhetiance
 *
 * Revision 1.11  2012/10/10 20:51:23  jem4687
 * added functions for inheritance
 *
 * Revision 1.10  2012/10/10 20:02:57  jem4687
 * Initial revision
 *
 * Revision 1.9  2012/10/02 19:20:41  jem4687
 * removed include for player since not needed
 *
 * Revision 1.8  2012/10/02 19:13:05  jem4687
 * added comments
 *
 * Revision 1.7  2012/10/01 22:41:42  jem4687
 * testing
 *
 * Revision 1.6  2012/09/27 01:10:12  jem4687
 * remodeling with all functionality in takeaway
 *
 * Revision 1.5  2012/09/27 00:47:35  jem4687
 * debugging
 *
 * Revision 1.4  2012/09/23 21:22:48  jem4687
 * fixed some bugs so it compiles correctly
 *
 * Revision 1.3  2012/09/22 22:00:56  jem4687
 * added print and move functions
 *
 * Revision 1.2  2012/09/22 21:04:08  jem4687
 * Started
 *
 * Revision 1.1  2012/09/22 21:01:57  jem4687
 * Initial revision
 *
 *
 * @author:Jesse Martinez
 * @author:Michael Loper
 */

#ifndef TAKEAWAY_H
#define TAKEAWAY_H

#include <string>
#include <iostream>
#include <vector>
#include <utility>
#include "Game.h"

//Typedef for our created triple type.
typedef triple< int, int, std::vector< std::vector<int> > > trip;


class TakeawayGame: public Game
{
	private:
		/** Pair that holds player character and player type */
		std::pair<std::string,std::string> p1;
		std::pair<std::string,std::string> p2;

	public:

		/**
		 * Constructor
 		 *
 		 * Description:  Creates a game of takeaway between the user
		 *               and pc with the initial ammount of pennies
		 *		 received.
 		 *
		 * @param int      -  A "dummy" int to differentiate the
		 *                    interactive mode from
		 *                    the solver mode.
		 *        apennies -  The initial amount of pennies in the pile.
		 */
		TakeawayGame( int , int apennies );


		/**
		 * Constructor
		 *
		 * Description:  Creates a game of takeaway to be ran in
		 *               solver mode.
		 *
		 * @param apennies -  The initial amount of pennies in the pile.
		 */
		TakeawayGame( int apennies );

		/**
		 * Name:   generateBoard
		 *
		 * Description: Creates an empty board.  This function is
		 * 		implemnted in the other games.
		 *
		 * @param b     - The board.
		 */
		void generateBoard( std::vector< std::string > b );

		/**
		 * Name:   move
		 *
		 * Description:  Calls the proper move function based on the
		 * 		 received player number.  Removes the ammount
		 * 		 of pennies the player chose.
		 *
		 * @param p      - The number representing whose turn it is.
		 */
		void move( const int p );

		/**
		 * Name:  moveHuman
		 *
		 * Description: Asks for user input on how many pennies to
		 * 		take away.
		 *
		 * @param p    - A string representing either player "X" or "O".
		 *
		 * @return     The number of pennies chosen.
		 */
		int moveHuman( const std::string p );

		/**
		 * Name: movePC
		 *
		 * Description: Move for PC player calls the solver algorithm
		 * 		to find the best possible move given the
		 *		current successor.
		 *
		 * @param turn       - Integer to keep track of the turn.
		 *        successor  - The current successor of a takeaway
		 *                     configuration.
		 *
		 * @return      A triple that holds the best score, the best
		 *              move, and the best board.
		 */
		trip  movePC( const int turn,std::vector< trip > successor );

		/**
		 * Name: findSuccessors
		 *
		 * Description: Generates all possible valid moves.
		 *
		 * @param b     - The current board, the number of pennies to
		 *		take away, and the number of pennies remaining.
		 *
		 * @return      A vector of all the successors.
		 */
		std::vector< trip > findSuccessors( trip );

		/**
		 * Name: print
		 *
		 * Description: Prints an "O" to standard output for each
		 * penny left.
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
		 * Description:  Determines if a base case as been reached.
		 *
		 * @param check  - A vector of the remaining moves.
		 *
		 * @return       True iff there are one or less remaining moves.
		 */
		bool checkBaseCase( const std::vector< trip > check ) const;

		/**
		 * Name: baseCase
		 *
		 * Description: Returns a standard base case representation
		 *		for the takeaway game.  For this game it is a
		 *		score of 1 a move of 0 and an empty board.
		 *
		 * @return      A triple witha score, move, and board.
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
};

#endif
