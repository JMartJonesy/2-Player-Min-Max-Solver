/**
 * Name: kayles.cpp
 * Description: The main for a Kayles Game.
 *
 * $Id: kayles.cpp,v 1.7 2012/11/07 19:10:46 jem4687 Exp jem4687 $
 *
 * Revisions:
 * $Log: kayles.cpp,v $
 * Revision 1.6  2012/11/07 19:10:46  jem4687
 * Pretty up the comments
 *
 * Revision 1.5  2012/10/29 02:40:02  mal4012
 * Minor comment changes.
 *
 * Revision 1.4  2012/10/25 00:45:24  jem4687
 * Changed findsuccessors to receive a trip
 *
 * Revision 1.3  2012/10/21 18:16:29  mal4012
 * Changed comments.
 *
 * Revision 1.2  2012/10/20 22:14:13  mal4012
 * Editted comments.
 *
 * Revision 1.1  2012/10/20 22:11:16  mal4012
 * Moved main into kayles.cpp.
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

/**
 * Name: main
 *
 * Description:  Creates and runs a Kayles Game.
 *
 * @param argc   - The number of arguments entered.
 *        argv[] - A pointer to an array of chars representing the arguments
 *                 entered.
 *
 * @return       0, to indicate a smooth program execution.
 */
int main( int argc, const char* argv[] )
{
	const char* PLAY("play");
	// Must receive at least two arguments.
	if ( argc < 2 ){
		cerr << "Usage: " << argv[0] << " [play] num_pins_1"\
			" num_pins_2 ...";
		cout << endl;
		exit( 1 );
	} else {
		vector<string> c;
		int count = 0;
		int thePins;
		// If the first argument given is not play enter solver mode.
		if( strcmp( PLAY,argv[1] )){
			// Loop through the arguments.
			for( int i = 1; i < argc; ++i ){
				c.push_back(argv[i]);
				string p = argv[i];
				stringstream ss( p );
				ss >> thePins;
				//int p = atoi( argv[i] );
				count += thePins;
				// Make sure the arguments are positive
				// integers.
				if ( thePins < 0 ){
					cerr << "Invalid pin ammount, must"\
						" be an integer >= 0.";
	                		cout << endl;
        	        		exit( 1 );
				}
				if ( !thePins && p != "0" ){
					cerr << "Invalid pin ammount, must"\
                                                " be an integer >= 0.";
                                        cout << endl;
                                        exit( 1 );
				}
			}
			// Create the game on the ammount of pins and the pins
			// given.
			KaylesGame k( count , c );
			// Check for no pins.
			if ( k.getData() == 0 )
				cout << "No pins on the board so best move is "\
					"no move with a score of one." << endl;
			else {
				// Find the best possible move, score, and
				// board.
				triple<int,int,vector< vector<int> > > 
				b( k.getData(), 0 , k.board );
				triple<int,int,vector< vector<int> > > moved =
				k.movePC( 0,k.findSuccessors( b ));
				k.board = moved.board;
				// Print the best move if the score is
				// positive otherwise default move is to take
				// one.
				if ( moved.first == 1 ){
					cout << "Best ammount of pins to take"\
					" is " << moved.second << endl;
					cout << "With a board of ";
					k.print();
				} else {
					cout << "Score is " << moved.first << \
					" so default move to take 1 from the "\
					"leftmost column." << endl;
				}
			}
		}
		// If we see the word play enter interactive mode.
		else if( !strcmp( PLAY,argv[1] )){
			vector<string> c;
			// Loop through the pins given.
			for( int i = 2; i < argc; ++i ){
                                c.push_back(argv[i]);
				string p = argv[i];
                                stringstream ss( p );
                                ss >> thePins;
                                count += thePins;
				// Make sure the arguments are positive
				// integers.
				if ( thePins < 0 ){
                                        cerr << "Invalid pin ammount, must"\
                                                " be an integer >= 0.";
                                        cout << endl;
                                        exit( 1 );
                                }
				if ( !thePins && p != "0" ){
                                        cerr << "Invalid pin ammount, must"\
                                                " be an integer >= 0.";
                                        cout << endl;
                                        exit( 1 );
                                }

                        }
			// Create the game on the ammount of pins and the pins
                        // given.
                        KaylesGame k( count , c );
			// Player to move first wins by default if there are
			// no pins.
                        if ( k.getData() == 0 )
                                cout << "No pins on the board, so human"\
				" player wins by default." << endl;
                        else {
				// Play the game.
				int turn = 0;
				while ( k.getData() !=0 ){
					if ( turn % 2 == 0 )
						k.move( 1 );
					else
						k.move( 2 );
					++turn;
				}
				// Print out the loser.
				if (( turn-1 ) % 2 == 1 )
		                        cout << "Player " << k.getName( 1 )
						<< " loses" << endl;
               			else
                        		cout << "Player " << k.getName( 2 )
						<< " loses" << endl;

			}
		} else {
			// Print usage statement for bad arguments.
			cerr << "Usage: " << argv[0] << " [play] num_pins_1"\
                        " num_pins_2 ...";
		}
	}
	return 0;
}
