/**
 * Name: takeaway.cpp
 * Description:  The main for a Takeaway Game.
 *
 * $Id: takeaway.cpp,v 1.13 2012/11/07 19:10:46 jem4687 Exp jem4687 $
 *
 * Revisions:
 * $Log: takeaway.cpp,v $
 * Revision 1.4  2012/11/07 19:10:46  jem4687
 * Pretty up the comments
 *
 * Revision 1.3  2012/10/29 02:40:02  mal4012
 * Minor comment changes.
 *
 * Revision 1.2  2012/10/25 00:45:24  jem4687
 * Changed findsuccessors to receive a trip
 *
 * Revision 1.1  2012/10/20 22:11:47  mal4012
 * Moved main into takeaway.cpp.
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

#include "TakeawayGame.h"
#include "Game.h"

using namespace std;

/**
 * Name: main
 *
 * Description:  Creates and runs a Takeaway Game.
 *
 * @param argc   - The number of arguments entered.
 *        argv[] - A pointer to an array of chars representing the arguments
 *                 entered.
 *
 * @return       0, to indicate a smooth program execution.
 */
int main( int argc, const char* argv[] ){
	stringstream ss;
	int thePennies;
	const char* PLAY("play");
	//Make sure there are two or three arguments.
	if ( argc != 2 && argc != 3 ){
		cerr << "Usage: " << argv[0] << " [play] num_pennies";
		cout << endl;
		exit( 1 );
	}
	//Enter solver mode for two arguments.
	if ( argc == 2 ){
		// Must receieve penny ammount greater than 0
		string p = argv[1];
		ss << p;
		ss >> thePennies;
		if ( p == "0" ){
                        cout << "The best move is no move with a score of -1."
                        << endl;
                        exit( 1 );
                }

		if( !thePennies || thePennies < 0 ){
			cerr << p << " is an invalid number of pennies to be"\
				  " specified. " << endl;
			exit(1);
		}

		// Create the game on the ammount of pennies given.
		TakeawayGame t( thePennies );
		if ( t.getData() == 0 )
			cout << "No pennies in the pile the best move is to "\
			"takeaway 0 pennies with a score of -1" << endl;
		else{
			triple<int,int,vector< vector<int> > >
			b( t.getData(), 0, t.board );
			//Find and print the best move and score.
			triple<int,int,vector< vector<int> > > moved =
			t.movePC( 0,t.findSuccessors( b ));
			if ( moved.first != -1 )
				cout << "Best ammount of pennies to take is " \
				<< moved.second << endl;
			else
				cout << "Score is " << moved.first << \
				" so default move to take 1." << endl;
		}
	}
	// If there are three arguments enter interactive mode.
	else if ( argc == 3 ){
		// Make sure the first argument given is exactly "play".
		if ( strcmp( PLAY,argv[1] )){
			cerr << "Usage: " << argv[0] << " [play] num_pennies";
               		cout << endl;
                	exit( 1 );
		}
		// Pennies must be greater than or equal to zero.
		string p = argv[2];
                ss << p;
                ss >> thePennies;
		if ( p == "0" ){
                        cout << "Starting with 0 pennies so no move can be"\
                        " made and human player loses by default" << endl;
                        exit( 1 );
                }
		if ( thePennies < 0 || !thePennies ){
			cerr << p << " is an invalid number of pennies to be"\
                                  " specified. " << endl;
                        exit(1);
                }
		// Create a takeaway game in interactive mode.
		TakeawayGame t( thePennies );
		// Keeps track of turns
	        int turn = 0;

      	        // Runs game
		while ( t.getData() != 0 ){
                	if ( turn % 2 == 0 )
                        	t.move( 1 );
                	else
                        	t.move( 2 );
                	turn++;
        	}
		// When the game is over print out the loser.
        	if (( turn-1 ) % 2 == 0 )
                	cout << "Player " << t.getName( 1 ) << " loses" << endl;
       		else
                	cout << "Player " << t.getName( 2 ) << " loses" << endl;
	}

	return 0;
}
