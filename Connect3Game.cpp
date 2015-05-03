/**
 * Name: Connect3Game.cpp
 *
 * Description: A connect3 Game is a simplified version fo connect4 where two
 *		players alternate to ultimately try to have three pieces in a
 *		"row".
 *
 * $Id: Connect3Game.cpp,v 1.4 2012/11/07 19:10:46 jem4687 Exp jem4687 $
 *
 * Revisions:
 * $Log: Connect3Game.cpp,v $
 * Revision 1.9  2012/11/07 19:10:46  jem4687
 * Pretty up the comments
 *
 * Revision 1.8  2012/11/01 00:14:26  jem4687
 * Implemented play aswell as error checking
 *
 * Revision 1.7  2012/10/30 23:48:21  mal4012
 * Changed error handling and added cin mode.
 *
 * Revision 1.6  2012/10/30 02:27:41  jem4687
 * Added scores checking
 *
 * Revision 1.5  2012/10/29 02:40:02  mal4012
 * Minor comment changes.
 *
 * Revision 1.4  2012/10/25 00:45:24  jem4687
 * Changed findsuccessors to receive a trip
 *
 * Revision 1.3  2012/10/22 01:59:25  jem4687
 * *** empty log message ***
 *
 * Revision 1.2  2012/10/21 22:10:25  mal4012
 * Changed constructors.
 *
 * Revision 1.1  2012/10/21 18:16:29  mal4012
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

#include "Connect3Game.h"
#include "Game.h"

using namespace std;

//Typedef for our created triple type.
typedef triple< int, int, vector< vector<int> > > trip;

/**
 * Constructor
 *
 * Description: Creates a connect3 game based off the initial configuration to
 *              be ran in interactive mode.
 *
 * @param int    - A "dummy" int to differentiate the interactive mode from
 *                 the solver mode.
 *        spaces - The remaining spaces left on the board.
 *        b      - A vector of strings representing the board.
 */
Connect3Game::Connect3Game( const int, int spaces, vector<string> b )
        :Game( spaces ),p1( "X","Human" ),p2( "O","PC" ),IN_A_ROW(3)
	,lastplaced( 0 ),playMode(true){
        generateBoard( b );
}

/**
 * Constructor
 *
 * Description:  Creates a game of connect3 to be ran in solver mode.
 *
 * @param spaces - The remaining spaces left on the board.
 *        b      - A vector of strings representing the board.
 */
Connect3Game::Connect3Game( int spaces, vector<string> b )
        :Game( spaces ),p1( "X","Human" ),p2( "O","PC" ),IN_A_ROW(3)
	,lastplaced( 0 ),playMode(false){
        generateBoard( b );
}

/**
 * Name:  generateBoard
 *
 * Description: Generates a connect 3 board of 0's, 1's, and 2's.
 *
 * @param b     - The board.
 */
void Connect3Game::generateBoard( vector<string> b ){
	cout << b.size();
	int row;
	int col;
	stringstream ss( b[1] );
	ss >> col;
	stringstream ss2( b[0] );
	ss2 >> row;
	int pos = 2;
        for( int i = 0; i < col; ++i ){
		board.push_back( vector<int>() );
                for( int j = 0; j < row; ++j ){
			// X's are 2's.
			if( b[pos] == "X" ){
                        	board[i].push_back( 2 );
			// O's are 1's.
			} else if ( b[pos] == "O" ){
				board[i].push_back( 1 );
			} else {
				board[i].push_back( 0 );
			}
			pos++;
		}
        }

}

/**
 * Name: move
 *
 * Description:  Calls the proper move function based on the received player
 *               number.
 *
 * @param p      - The number representing whose turn it is.
 */
void Connect3Game::move( const int p ){
        trip b( getData(), 0, board );
	if ( p == 1 ){
                if ( p1.second == "Human" )
                        moveHuman( p1.first );
                else{
                        trip pin = movePC( 0,findSuccessors( b ));
                        cout << "Player " << p1.first << " dropping into column "
                                << pin.second << endl;
                }
        }
        else{
                if ( p2.second == "Human" )
                        moveHuman( p2.first );
                else{
                        trip pin = movePC( 1,findSuccessors( b ));
                        cout << "Player " << p2.first << " dropping into column "
                                << pin.second << endl;
                }
        }
	changeData( 1 );
        print();
}

/**
 * Name: moveHuman
 *
 * Description: Asks for user input on where they would like to mak a move.
 *
 * @param p     - A string representing either player "X" or "O".
 *
 * @return
 */
int Connect3Game::moveHuman( const string p ){
        int col;
	int bsize = board[0].size();
	bool empty = false;
        do {
                // Print the current board
                cout << "The current board is: " << endl;
                print();
                cout << "Input column to drop piece in." << endl;
                cin >> col;
		if ( board[0][col] == 0 ){
			empty = true;
		}
                if ( col < 0 || col >= bsize || empty == false ){
                        cerr << "Invalid column" << endl;
		}
        }
        // Keep looping until we have a valid column,
        while ( col < 0 || col >= bsize || empty == false );
	cout << "Player " << p << " placing in column " << col << endl;
	int row = board.size() - 1;
	// Update the board.
	for ( row; row >= 0; --row ){
		if ( board[row][col] == 0 ){
			board[row][col] = 2;
			break;
        	}
	}
	lastplaced = col;
	return 1;
}

/**
 * Name: movePC
 *
 * Description: Move for PC player calls the solver algorithim to find the best
 *              possible move given for the current successor, and sets the
 *              board to the best possible board.
 *
 * @param turn      - Integer to keep track of the turn.
 *        successor - The current successor of a connect3 configuration.
 *
 * @return      A triple that holds the best score, the best move, and the
 *              best board.
 */
trip Connect3Game::movePC( const int turn1, vector< trip > successor ){
        trip solved = solver( turn1,successor );
	if( solved.board.size() == 0 )
	{
		int move = 0;
		int rowSize = board.size() - 1;
		bool found = false;
		for( unsigned int col = 0; col < board[0].size(); ++col ){
                	for( int row = rowSize; row >= 0; --row ){
                        	if( board[row][col] == 0 ){
                                	move = col;
					if( playMode )
                               			board[row][col] = 1;
					else
						board[row][col] = 2;
                                	found = true;
                                	break;
				}
                        }
                	if( found ){
                        	break;
                	}
		}
		solved.second = move;
		solved.board = board;
        }
	else{
        	board = solved.board;
	}
        lastplaced = solved.second;
	return solved;
}

/**
 * Name: findSuccessors
 *
 * Description: Generates all possible valid moves.
 *
 * @param b     - A triple containing the current board, the remaining spaces,
 *		and the last placed col.
 *
 * @return      A vector of all the successors.
 */
vector< trip > Connect3Game::findSuccessors( trip b ){
        vector< trip > successor( 0 );
	if( checkWin( b ) )
	{
		return successor;
	}
	int place;
	if( playMode )
		place = 1;
	else
		place = 2;
	int bsize = board[0].size();
        // Loop through the columns.
        for ( int c = 0; c < bsize; ++c ){
                // Loop through the rows.
                for ( int r = ( board.size()-1 ); r >= 0; --r ){
                        vector< vector<int> > newBoard( b.board );
                        // If we found an empty spot in the column..
                        if( newBoard[r][c] == 0 ){
                                // Place the proper "X" or "O" based on whose
				// turn it is.
                                newBoard[r][c] = place;
                                successor.push_back( trip(
				b.first-1,c,newBoard ));
				// Go to the next column.
				break;
			}
                }
        }
        return successor;
}

/**
 * Name: checkWin
 *
 * Description: Given a column, checks for a win.
 *
 * @param b     - The column of the last played piece.
 *
 * @return      True iff the configuration is now a win.
 */

bool Connect3Game::checkWin( trip b ){
	if( b.second == -1 ){
		return false;
	}
	int counter=0;
	vector<int> placed;
	bool foundRow = false;
	int brow = b.board.size();
	int bcol = b.board[0].size();
	int brow2 = ( b.board.size() -1 );
	// Given the column, find the corresponding row of the most recently
	// placed piece.
	for( int r = brow2; r >= 0; --r ){
		if( b.board[r][b.second] == 0 ){
			if( r == b.board.size()-1 )
				return false;
			placed.push_back( r+1 );
			foundRow = true;
			break;
		}
	}

	if( !foundRow ){
		placed.push_back( 0 );
	}
	placed.push_back( b.second );
	// Get the most recently placed piece off of the row/col.
	int pl = b.board[placed[0]][placed[1]];
	for( int times = 0; times < brow; ++times ){
		// Check for 3 in a row.
		if( b.board[times][placed[1]] == pl){
			counter++;
			if( counter >= IN_A_ROW ){
				return true;
			}
		}
		else{
			counter = 0;
		}
	}

	counter = 0;
	for( int times = 0; times < bcol; ++times ){
		// Check for 3 in a col.
		if( b.board[placed[0]][times] == pl ){
			counter++;
			if( counter >= IN_A_ROW){
				return true;
			}
		}
		else{
			counter = 0;
		}
	}

	int r2 = placed[0];
	int c2 = placed[1];
	counter = 0;
	while( r2 > 0 && c2 > 0){
		r2--;
		c2--;
	}
	while( r2 < brow && c2 < bcol ){
		// Check for 3 in a downright diagonal.
		if( b.board[r2][c2] == pl ){
			counter++;
			if( counter >= IN_A_ROW){
				return true;
			}
		}
		else{
			counter = 0;;
		}
		r2++;
		c2++;
	}

	r2 = placed[0];
	c2 = placed[1];
	counter = 0;
	while( r2 < brow-1 && c2 > 0 ){
		r2++;
		c2--;
	}
	while( r2 >= 0 && c2 < bcol ){
		// Check for 3 in a upright diagonal.
		if( b.board[r2][c2] == pl ){
			counter++;
			if( counter >= IN_A_ROW){
				return true;
			}
		}
		else{
			counter = 0;;
		}
		r2--;
		c2++;
	}
	return false;
}

/**
 * Name: print
 *
 * Description: Prints out a connect3 rendition using X's and O's.
 */
void Connect3Game::print(){
	for( unsigned i = 0; i < board.size(); ++i ){
		for( unsigned int j = 0; j < board[0].size(); ++j ){
                        if( board[i][j] == 2 ){
                                cout << "X";
                        } else if ( board[i][j] == 1 ){
                                cout << "O";
                        } else {
                                cout << "_";
                        }
			cout << " ";
		}
		cout << endl;
        }
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
string Connect3Game::getName( const int p ) const{
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
bool Connect3Game::checkBaseCase( const vector< trip > check ) const{
	return ( check.size() == 0 );
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
trip Connect3Game::baseCase() const{
        vector< vector<int> > b(board);
	int score = ( 9999 - ( turn * 2 ));
	int move = 0;
	bool found = false;
	int rowSize = ( board.size() - 1 );
	for( unsigned int col = 0; col < board[0].size(); ++col ){
		for( int row = rowSize; row >= 0; --row ){
			if( board[row][col] == 0 ){
				move = col;
				b[row][col] = 2;
				found = true;
				break;
			}
		}
		if( found ){
			break;
		}
	}
        return trip( -score, move, b );
}

/**
 * Name: invert
 *
 * Description: Inverts the board by converting all the X's to O's and O's
 *              to X's.
 *
 * @param b     - The board.
 *
 * @return      The inverted board.
 */
vector< vector<int> > Connect3Game::invert( vector< vector<int> > b ){
        for( unsigned i = 0; i < b.size(); ++i ){
                for( unsigned int j = 0; j < b[0].size(); ++j ){
                        if( b[i][j] == 2 ){
                                b[i][j] = 1;
                        } else if ( b[i][j] == 1 ){
                                b[i][j] = 2;
                        }
                }
        }
        return b;
}

/**
 * Name: getLastPlace
 *
 * Description: Returns humans last move played
 *
 * @return      The column of humans last move
 */
int Connect3Game::getLastPlaced(){
	return lastplaced;
}
