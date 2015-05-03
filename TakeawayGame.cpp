/**
 * Name: TakeawayGame.cpp
 * Description:  A Takeaway Game starts with an initial pile of pennies and
 *               players alternate turns taking 1, 2, or 3 pennies.  The
 *               player to take the last penny loses.
 *
 * $Id: TakeawayGame.cpp,v 1.5 2012/11/07 19:10:46 jem4687 Exp jem4687 $
 *
 * Revisions:
 * $Log: TakeawayGame.cpp,v $
 * Revision 1.22  2012/11/07 19:10:46  jem4687
 * Pretty up the comments
 *
 * Revision 1.21  2012/10/29 02:40:02  mal4012
 * Minor comment changes.
 *
 * Revision 1.20  2012/10/25 00:44:28  jem4687
 * Changed findsuccessors to receive a trip
 *
 * Revision 1.19  2012/10/24 21:24:38  mal4012
 * Improved speed of the solver for takeaway.
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
 * Revision 1.14  2012/10/15 19:23:21  mal4012
 * Changed error prints.
 *
 * Revision 1.13  2012/10/15 18:05:07  mal4012
 * Changed a few formatting issues.
 *
 * Revision 1.12  2012/10/10 22:30:06  jem4687
 * included inhetiance
 *
 * Revision 1.11  2012/10/10 20:51:23  jem4687
 * added functions for inheritance
 *
 * Revision 1.10  2012/10/03 03:59:49  jem4687
 * added standard error output
 *
 * Revision 1.9  2012/10/02 19:13:05  jem4687
 * added comments
 *
 * Revision 1.8  2012/10/01 23:29:00  jem4687
 * Correct!!!!!!!!!!
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

#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <sstream>

#include "TakeawayGame.h"
#include "Game.h"

using namespace std;

//Typedef for our created triple type.
typedef triple< int, int, vector< vector<int> > > trip;

/**
 * Constructor
 *
 * Description:  Creates a game of takeaway between the user and pc with
 *               the initial amount of pennies received.
 *
 * @param int      -  A "dummy" int to differentiate the interactive mode from
 *                    the solver mode.
 *        apennies -  The initial amount of pennies in the pile.
 */
TakeawayGame::TakeawayGame( int , int apennies )
	:Game( apennies ),p1( "X","Human" ),p2( "O","PC" ){
	generateBoard( vector<string>() );
}

/**
 * Constructor
 *
 * Description:  Creates a game of takeaway to be ran in solver mode.
 *
 * @param apennies -  The initial amount of pennies in the pile.
 */
TakeawayGame::TakeawayGame( int apennies )
	:Game( apennies ),p1( "X","Human" ),p2( "O","PC" ){
	generateBoard( vector<string>() );
}

/**
 * Name: generateBoard
 *
 * Description: Creates an empty board.  This function is implemnted in the
 *              other games.
 *
 * @param b     - The board.
 */
void TakeawayGame::generateBoard(  vector<string> ){
	board.push_back( vector<int>() );
	board[0].push_back( -1 );
}

/**
 * Name: move
 *
 * Description:  Calls the proper move function based on the received player
 *               number.  Removes the ammount of pennies the player chose.
 *
 * @param p      - The number representing whose turn it is.
 */
void TakeawayGame::move( const int p ){
	trip b( getData(), 0 , board );
	if ( p == 1 ){
		if ( p1.second == "Human" )
			changeData( moveHuman( p1.first ));
		else{
			trip penny = movePC( 0, findSuccessors( b ));
       	                changeData( penny.second );
			cout << "Player " << p1.first << " taking "
				<< penny.second << " pennies" << endl;
		}
	}
	else {
		if ( p2.second == "Human" )
			changeData( moveHuman( p2.first ));
		else {
			trip penny = movePC( 0,findSuccessors( b ));
			changeData( penny.second );
			cout << "Player " << p2.first << " taking "
				<< penny.second << " pennies" << endl;
		}
	}
	print();
}

/**
 * Name: moveHuman
 *
 * Description: Asks for user input on how many pennies to take away.
 *
 * @param p    - A string representing either player "X" or "O".
 *
 * @return     The number of pennies chosen.
 */
int TakeawayGame::moveHuman( const string p ){
	string num;
	int theAmount;
	do {
		cout << "Input number of pennies to takeaway (1,2,or 3)"
			<< endl;
		cin >> num;
		stringstream ss( num );
		ss >> theAmount;
		if ( theAmount <= 0 || theAmount > 3 || theAmount > getData() 
			|| !theAmount )
			cout << "Invalid number of pennies!" << endl;
	}
	while ( theAmount <=0 || theAmount > 3 || theAmount > getData() || 
		!theAmount );
		cout << "Player " << p << " taking " << num << " pennies"
			<< endl;
	return theAmount;
}

/**
 * Name: movePC
 *
 * Description: Move for PC player calls the solver algorithm to find the best
 *              possible move given the current successor.
 *
 * @param turn       - Integer to keep track of the turn.
 *        successor  - The current successor of a takeaway configuration.
 *
 * @return      A triple that holds the best score, the best move, and the
 *              best board.
 */
trip TakeawayGame::movePC( const int turn,vector< trip > successor ){
	return solver( turn,successor );
}

/**
 * Name: findSuccessors
 *
 * Description: Generates all possible valid moves.
 *
 * @param b     - The current board, number of pennies to takeaway, and the
 *		number of pennies remaining.
 *
 * @return      A vector of all the successors.
 */
vector< trip > TakeawayGame::findSuccessors( trip b ){
	vector< vector<int> > newBoard( b.board );
	vector< trip > successor;
	for ( int i = 1; i <= 3; i++ ){
		if ( b.first - i >= 0 ){
			newBoard[0][0] = b.first - i;
			successor.push_back( trip( b.first-i, i, newBoard ));
		}
	}
	return successor;
}

/**
 * Name: print
 *
 * Description: Prints an "O" to standard output for each penny left.
 */
void TakeawayGame::print(){
	for ( int i = 0; i < getData(); i++ ){
		cout << "0";
	}
	cout << endl;
	cout << "Pennies left " << getData() << endl;
}

/**
 * Name: getName
 *
 * Description: Returns the name of the player received.
 *
 * @param p     - An integer representing whose turn it is.
 *
 * @return      String representation of the current player.
 */
string TakeawayGame::getName( const int p ) const{
	if ( p == 1 )
		return p1.first;
	else
		return p2.first;
}

/**
 * Name: checkBaseCase
 *
 * Description:  Determines if a base case as been reached.
 *
 * @param check  - A vector of the remaining moves.
 *
 * @return       True iff there are one or less remaining moves.
 */
bool TakeawayGame::checkBaseCase( const vector< trip > check ) const{
	return ( check.size() == 0 );
}

/**
 * Name: baseCase
 *
 * Description: Returns a standard base case representation for the takeaway
 *              game.  For this game it is a score of 1 a move of 0 and an
 *              empty board.
 *
 * @return      A triple with a score, move, and board.
 */
trip TakeawayGame::baseCase() const{
	vector< vector<int> > b;
	return trip( 1, 0, b );
}


/**
 * Name: invert
 *
 * Description: A dummy function to only be used in Connect3Game.
 *
 * @return      A board.
 */
vector< vector<int> > TakeawayGame::invert( vector< vector<int> > b ){
	return b;
}
