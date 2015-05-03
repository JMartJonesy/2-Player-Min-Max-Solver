/**
 * Name: KaylesGame.cpp
 *
 * Description:  A Kayles Game is a row of pins where players alternate
 *               knocking down pins.  A player can choose to knock down one
 *               or any two adjacent pins.  The player to knock down the last
 *               pin wins.
 *
 * $Id: KaylesGame.cpp,v 1.6 2012/11/07 19:10:46 jem4687 Exp jem4687 $
 *
 * Revisions:
 * $Log: KaylesGame.cpp,v $
 * Revision 1.12  2012/11/07 19:10:46  jem4687
 * Pretty up the comments
 *
 * Revision 1.11  2012/10/29 02:40:02  mal4012
 * Minor comment changes.
 *
 * Revision 1.10  2012/10/25 00:45:24  jem4687
 * Changed findsuccessors to receive a trip
 *
 * Revision 1.9  2012/10/22 16:59:31  mal4012
 * Fixed an unsigned int warning.
 *
 * Revision 1.8  2012/10/22 16:53:04  mal4012
 * Removed warnings.
 *
 * Revision 1.7  2012/10/21 18:16:29  mal4012
 * Changed comments.
 *
 * Revision 1.6  2012/10/21 03:04:07  mal4012
 * Redid comments.
 *
 * Revision 1.5  2012/10/18 03:22:10  p334-04e
 * works now
 *
 * Revision 1.4  2012/10/17 21:43:02  mal4012
 * Added play feature.
 *
 * Revision 1.3  2012/10/17 01:38:41  mal4012
 * Changed base cases.
 *
 * Revision 1.2  2012/10/16 02:29:08  jem4687
 * added functionality to print
 *
 * Revision 1.1  2012/10/16 02:25:21  jem4687
 * Initial revision
 *
 *
 *
 * @author:Jesse Martinez
 * @author:Michael Loper
 */

#include <sstream>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cstring>

#include "KaylesGame.h"
#include "Game.h"

using namespace std;

//Typedef for our created triple type.
typedef triple< int, int, vector< vector<int> > > trip;

/**
 * Constructor
 *
 * Description:  Creates a game of kayles between the user and the pc with
 *               the initial amount of pins and board received.
 *
 * @param int    - A "dummy" int to differentiate the interactive mode from
 *                 the solver mode.
 *        pins   - The initial amount of pins in the row.
 *        b      - A vector of strings representing the pins.
 */
KaylesGame::KaylesGame( const int , int pins , vector<string> b )
	:Game( pins ),p1( "X","Human" ),p2( "O","PC" ){
	generateBoard( b );
}

/**
 * Constructor
 *
 * Description:  Creates a game of kayles to be ran in solver mode.
 *
 * @param pins   - The initial amount of pins in the row.
 *        b      - A vector of strings representing the pins.
 */
KaylesGame::KaylesGame( int pins , vector<string> b )
	:Game( pins ),p1( "X","Human" ),p2( "O","PC" ){
	generateBoard( b );
}

/**
 * Name:  generateBoard
 *
 * Description: Generates the board with 1's and 0's based off of the strings
 *              received from the command line arguments.
 *
 * @param b     - The board.
 */
void KaylesGame::generateBoard( vector<string> b ){
	board.push_back( vector<int>() );
	for( unsigned i = 0; i < b.size(); ++i ){
		for( int j = 0; j < atoi( b[i].c_str() ); ++j )
			board[0].push_back( 1 );
		if( i != b.size() - 1 )
			board[0].push_back( 0 );
	}
}

/**
 * Name: move
 *
 * Description:  Calls the proper move function based on the received player
 *               number.  Removes the ammount of pins the player chose.
 *
 * @param p      - The number representing whose turn it is.
 */
void KaylesGame::move( const int p ){
	trip b( getData(), 0 ,board );
	if ( p == 1 ){
		if ( p1.second == "Human" )
			changeData( moveHuman( p1.first ));
		else{
			trip pin = movePC( 0, findSuccessors( b ) );
       	                changeData( pin.second );
			cout << "Player " << p1.first << " taking "
				<< pin.second << " pins" << endl;
		}
	}
	else{
		if ( p2.second == "Human" )
			changeData( moveHuman( p2.first ));
		else{
			trip pin = movePC( 0,findSuccessors( b ));
			changeData( pin.second );
			cout << "Player " << p2.first << " taking "
				<< pin.second << " pins" << endl;
		}
	}
	print();
}

/**
 * Name: moveHuman
 *
 * Description: Asks for user input on how many pins to take away.
 *
 * @param p     - A string representing either player "X" or "O".
 *
 * @return      The number of pins chosen.
 */
int KaylesGame::moveHuman( const string p ){
	int num = 0;
	int col = 0;
	bool take2 = true;
	int bSize = board[0].size();
	string theAmount;
	string theCol;
	do {
		take2 = true;
		// Print the current board
		cout << "The current board is: ";
		print();
		cout << "Input number of pins to take away (1,2)"
			<< endl;
		cin >> theAmount;
		stringstream ss( theAmount );
		ss >> num;
		// Make sure the number of pins is either one or two and there
		// are enough pins remaining to take.
		if ( num <= 0 || num > 2 || ( getData() - num ) < 0 ||
			( !num && theAmount != "0" ))
			cerr << "Invalid number of pins to take" << endl;
		else {
			cout << "Input column starting with column 0 "\
                                "(if taking 2 pins choose left most column"\
				" of pair)" << endl;
			// Take the column from user input.
			cin >> theCol;
			stringstream ss2( theCol );
			ss2 >> col;
			// Make sure there is a pin at the column.
			if( col < 0 || col > bSize ||
				board[0][col] == 0 || ( !col && theCol != "0" ))
				cerr << "Invalid column" << endl;
			if( num == 2 ){
				// If we are taking two make sure there is a
				// pin in the second column.
				if (( col+1 ) < board[0].size() ){
					if ( board[0][col+1] == 0 ){
						cerr << "Cant take"\
						" 2 from this column"
						<< endl;
						take2 = false;
					}
				} else {
					cerr << "Cant take 2 from this"
						" column" << endl;
					take2 = false;
				}
			}
                }
	}
	// Keep looping until we have a valid number of pins, a valid column,
	// and a valid second column if there is one.  ( We set take2 to true
	// for a valid second column ).
	while ( num <= 0 || num > 3 || ( getData() - num ) < 0 || col < 0
		|| col > bSize || board[0][col] == 0 || !take2 || 
		( !num && theAmount != "0" ) || ( !col && theCol != "0" ));
		cout << "Player " << p << " taking " << num << " pins"
			<< endl;
	// Update the board.
	board[0][col] = 0;
	if( num == 2 )
		board[0][col+1] = 0;
	return num;
}

/**
 * Name: movePC
 *
 * Description: Move for PC player calls the solver algorithim to find the best
 *              possible move given for the current successor, and sets the
 *              board to the best possible board.
 *
 * @param turn      - Integer to keep track of the turn.
 *        successor - The current successor of a kayles configuration.
 *
 * @return      A triple that holds the best score, the best move, and the
 *		best board.
 */
trip KaylesGame::movePC( const int turn, vector< trip > successor ){
	trip solved = solver( turn,successor );
	board = solved.board;
	return solved;
}

/**
 * Name: findSuccessors
 *
 * Description: Generates all possible valid moves.
 *
 * @param       b     - The current board, the number of pins to take away, and
 *			the number of remaining pins.
 *
 * @return      A vector of all the successors.
 */
vector< trip > KaylesGame::findSuccessors( trip b ){
	vector< trip > successor;
	// Can only take one or two pins.
	for ( unsigned int i = 1; i < 3; ++i ){
		// Loop through the row of pins.
		for ( unsigned int j = 0; j < b.board[0].size(); ++j ){
			vector< vector<int> > newBoard( b.board );
			// If we are at a move of only one pin.
			if( i == 1 )
				// If there is a pin remove it from the board
				// copy and add the move to the vector of
				// sucessors.
				if( newBoard[0][j] == 1 ){
					newBoard[0][j] = 0;
					successor.push_back(
					trip( b.first-i,i,newBoard ));
				}
			// Repeat the process for two pins verifying we have
			// two adjacent pins.
			if( i == 2 )
				if( newBoard[0][j] == 1 )
					if( j + 1 < newBoard[0].size() )
						if( newBoard[0][j+1] == 1 ){
							newBoard[0][j] = 0;
							newBoard[0][j+1] = 0;
							successor.push_back(
							trip( b.first-i,i,newBoard ));
						}
		}
	}
	return successor;
}

/**
 * Name: print
 *
 * Description: Prints an "X" for each pin left and "_" for missing pins.
 */
void KaylesGame::print(){
	for ( unsigned i = 0; i < board[0].size(); i++ ){
		if( board[0][i] == 1 )
			cout << "X";
		else
			cout << "_";
	}
	cout << endl;
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
string KaylesGame::getName( const int p ) const{
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
 * @return       True iff there are no remaining moves.
 */
bool KaylesGame::checkBaseCase( const vector< trip > check ) const{
	return ( check.size() == 0 );
}

/**
 * Name: baseCase
 *
 * Description: Returns a standard base case representation for the kayles
 *              game.  For this game it is a score of -1 a move of 0 and an
 *              empty board.
 *
 * @return      A triple witha score, move, and board.
 */
trip KaylesGame::baseCase() const{
	vector< vector<int> > b;
	return trip( -1, 0, b );
}

/**
 * Name: invert
 *
 * Description: A dummy function to only be used in Connect3Game.
 *
 * @return      A board.
 */
vector< vector<int> > KaylesGame::invert( vector< vector<int> > b ) {
        return b;
}
