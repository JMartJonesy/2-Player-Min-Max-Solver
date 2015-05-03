/**
 * Name: CrossoutGame.cpp
 *
 * Description:  A Kayles Game is a row of pins where players alternate
 *               knocking down pins.  A player can choose to knock down one
 *               or any two adjacent pins.  The player to knock down the last
 *               pin wins.
 *
 * $Id: CrossoutGame.cpp,v 1.2 2012/11/07 19:10:46 jem4687 Exp jem4687 $
 *
 * Revisions:
 * $Log: CrossoutGame.cpp,v $
 * Revision 1.2  2012/11/07 19:10:46  jem4687
 * Pretty up the comments
 *
 * Revision 1.1  2012/11/03 02:00:56  jem4687
 * Initial revision
 *
 *
 * @author:Jesse Martinez
 */

#include <sstream>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cstring>

#include "CrossoutGame.h"
#include "Game.h"

using namespace std;

//Typedef for our created triple type.
typedef triple< int, int, vector< vector<int> > > trip;

/**
 * Constructor
 *
 * Description:  Creates a game of crossout between the user and
 *               the pc with the initial max num and length
 *
 * @param int    - A "dummy" int to differentiate the
 *                 interactive mode from the solver mode.
 *        max    - The max amount you can take.
 *        length - Length of board.
 */
CrossoutGame::CrossoutGame( const int , int max , int num )
	:Game( num ),p1( "X","Human" ),p2( "O","PC" ), MAX( max ){
	vector< string > b;
	generateBoard( b );
}

/**
 * Constructor
 *
 * Description:  Creates a game of crossout to be ran in solver
 * mode.
 *
 * @param max    - The max amount you can take.
 *        length - Length of board.
 */
CrossoutGame::CrossoutGame( int max , int num )
	:Game( num ),p1( "X","Human" ),p2( "O","PC" ), MAX( max ){
	vector< string > b;
        generateBoard( b );
}

/**
 * Name:  generateBoard
 *
 * Description: Generates the board with 1 to length based off
 * of the strings received from the command line arguments.
 *
 * @param b     - The board( a dummy board for this game ).
 */
void CrossoutGame::generateBoard( vector<string> b ){
	board.push_back( vector<int>() );
	int cols = getData();
	int newRemaining = 0;
	for( int i = 1; i <= cols; ++i ){
		board[0].push_back( i );
		if( MAX >= i ){
			newRemaining++;
		}
	}
	changeData( getData() - newRemaining );
}

/**
 * Name: move
 *
 * Description:  Calls the proper move function based on the
 *               received player number.  Removes the ammount
 *               of columns the player chose.
 *
 * @param p      - The number representing whose turn it is.
 */
void CrossoutGame::move( const int p ){
	trip b( getData(), 0 ,board );
	if ( p == 1 ){
		if ( p1.second == "Human" )
			changeData( moveHuman( p1.first ));
		else{
			trip pin = movePC( 0, findSuccessors( b ) );
       	                changeData( pin.second );
			cout << "Player " << p1.first << " taking "
				<< pin.second << " numbers" << endl;
		}
	}
	else{
		if ( p2.second == "Human" )
			changeData( moveHuman( p2.first ));
		else{
			trip pin = movePC( 0,findSuccessors( b ));
			changeData( pin.second );
			cout << "Player " << p2.first << " taking "
				<< pin.second << " numbers" << endl;
		}
	}
	print();
}

/**
 * Name: moveHuman
 *
 * Description: Asks for user input on how many pins to take
 * away.
 *
 * @param p     - A string representing either player "X" or "O".
 *
 * @return      The number of columns chosen.
 */
int CrossoutGame::moveHuman( const string p ){
	int n = 0;
	int n2 = 0;
	bool good = true;
	int size = board[0].size() - 1;
	do{
		cout << "Input number to remove :" << endl;
		cin >> n;
		cout << "Input second number to remove or -1 :" << endl;
		cin >> n2;
		if( findNum(n) == -1 || n > MAX ){
			cout << "Invalid first Column" << endl;
			good = false;
		}
		else{
			good = true;
		}
		if( n2 != -1){
			if( findNum(n2) == -1 || n2 > MAX ){
                        	cout << "Invalid second Column" << endl;
				good = false;
			}
			else{
        	                good = true;
				if( ( n + n2 ) > MAX ){
					cout << "Added numbers are greater than Max number";
					cout << endl;
					good = false;
				}
			}
                }

	}
	while( !good  );

	board[0].erase( board[0].begin() + findNum( n ) );
	if( n2 != -1 ){
		board[0].erase( board[0].begin() + findNum( n2 ) );
		return 2;
	}
	return 1;
}

/**
 * Name: findNum
 * Decription: Find and return the location of the number received
 *             in the board, or -1 if not found
 *
 * @param n    - Number to search for in the board
 *
 * @return     Integer location of number in board or -1 if not found
 */
int CrossoutGame::findNum( int n ){
	int found = -1;
	int size = board[0].size();
	for( int i = 0; i < size; ++i ){
		if( board[0][i] == n ){
			return i;
		}
	}
	return found;
}

/**
 * Name: movePC
 *
 * Description: Move for PC player calls the solver algorithim
 *              to find the best possible move given for the
 *              current successor, and sets to board to the
 *              best possible board.
 *
 * @param turn      - Integer to keep track of the turn.
 *        successor - The current successor of a crossout
 *                    configuration.
 *
 * @return      A triple that holds the best score, the best
 *              move, and the best board.
 */
trip CrossoutGame::movePC( const int turn, vector< trip > successor ){
	trip solved = solver( turn,successor );
	board = solved.board;
	return solved;
}

/**
 * Name: findSuccessors
 *
 * Description: Generates all possible valid moves.
 *
 * @param b     - The current board, the number of columns to take
 *              away, and the number of remaining columns you can take from.
 *
 * @return      A vector of all the successors.
 */
vector< trip > CrossoutGame::findSuccessors( trip b ){
	vector< trip > successor;
	int size = b.board[0].size();
	for( int i = 0; i < size; ++i ){
		vector< vector<int> > newBoard( b.board );
		if( b.board[0][i] <= MAX ){
                	newBoard[0].erase( newBoard[0].begin() + i );
			successor.push_back( trip( b.first - 1, 1, newBoard ) );
		}
		for( int ii = i+1; ii < size; ++ii ){
			vector< vector<int> > newBoard( b.board );
			if( (b.board[0][i] + b.board[0][ii] ) <=  MAX ){
				newBoard[0].erase( newBoard[0].begin() + ii );
				newBoard[0].erase( newBoard[0].begin() + i );
				successor.push_back( trip( b.first - 2, 2, newBoard ) );
			}
		}
	}
	return successor;
}

/**
 * Name: print
 *
 * Description: Prints an number in each column
 */
void CrossoutGame::print(){
	cout << "Numbers # ";
	for( unsigned i = 0; i < board[0].size(); i++ ){
		cout << board[0][i];
		cout << " ";
	}
	cout << endl;
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
string CrossoutGame::getName( const int p ) const{
	if ( p == 1 )
		return p1.first;
	else
		return p2.first;
}

/**
 * Name: checkBaseCase
 *
 * Description:  Determines if a base case has been reached.
 *
 * @param check  - A vector of the remaining moves.
 *
 * @return       True iff there are no remaining moves.
 */
bool CrossoutGame::checkBaseCase( const vector< trip > check ) const{
	return ( check.size() == 0 );
}

/**
 * Name: baseCase
 *
 * Description: Returns a standard base case representation
 * for the crossout game.  For this game it is a score of -1 a
 * move of last legal column and an empty board.
 *
 * @return      A triple with a score, move, and board.
 */
trip CrossoutGame::baseCase() const{
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
vector< vector<int> > CrossoutGame::invert( vector< vector<int> > b ) {
        return b;
}
