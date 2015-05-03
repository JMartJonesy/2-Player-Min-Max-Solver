/**
 * Name: Game.cpp
 * Description: Game is a generic like class used for inheritence to implement
 *              a best posible move algorithm for multiple games.
 *
 * $Id: Game.cpp,v 1.6 2012/11/07 19:10:46 jem4687 Exp jem4687 $
 *
 * Revisions:
 * $Log: Game.cpp,v $
 * Revision 1.13  2012/11/07 19:10:46  jem4687
 * Pretty up the comments
 *
 * Revision 1.12  2012/11/01 00:14:26  jem4687
 * Added lastplaced variable
 *
 * Revision 1.11  2012/10/30 02:27:41  jem4687
 * Added scores checking
 *
 * Revision 1.10  2012/10/29 02:40:02  mal4012
 * Minor comment changes.
 *
 * Revision 1.9  2012/10/25 00:45:24  jem4687
 * Changed findsuccessors to receive a trip
 *
 * Revision 1.8  2012/10/22 16:53:04  mal4012
 * Removed warnings.
 *
 * Revision 1.7  2012/10/22 01:58:21  jem4687
 * Redid Comments.
 *
 * Revision 1.6  2012/10/21 03:04:07  mal4012
 * Changed memoization.
 *
 * Revision 1.5  2012/10/18 02:32:07  jem4687
 * Mem works now.
 *
 * Revision 1.4  2012/10/11 23:58:42  jem4687
 * Included inheritence.
 *
 * Revision 1.3  2012/10/10 21:43:02  mal4012
 * added memoization
 *
 * Revision 1.2  2012/10/10 02:27:10  jem4687
 * added a few things for kayles
 *
 * Revision 1.1  2012/10/10 20:47:03  jem4687
 * Initial revision
 *
 *
 * @author:Jesse Martinez
 * @author:Michael Loper
 */

#include "Game.h"
#include <iostream>


using namespace std;

//Typedef for our created triple type.
typedef  triple< int,int,vector< vector<int> > > trip;

/**
 * Constructor
 *
 * Description:  Creates a game with initial data "d".
 *
 * @param d      - The initial data of the game.
 */
Game::Game( int d ):data( d ),turn(0){}

/**
 * Name: getData
 *
 * Description: Retrieve the current data of the game.
 *
 * @return      The data.
 */
int Game::getData(){
	return data;
}

/**
 * Name: changeData
 *
 * Description: Descreases the current data of the game by the amount
 * specified.
 *
 * @param m     - The amount to decrease the data.
 */
void Game::changeData( int m ){
	data = data - m;
}

/**
 * Name: solver
 *
 * Description: Finds the best possible move given an initial configuration.
 *
 * @param turn      - Integer representing whose turn it is.
 *        successor - The current configuration of the game.
 *
 * @return            The best possible move.
 */
trip Game::solver( int curTurn, vector< trip > successor ){
	int bScore = -99;
        int bMove = -99;
	vector< vector<int> > bb;
	vector< vector<int> > j;
	//turn = curTurn;
	// Check for the base case.
        if ( checkBaseCase( successor ) ){
                return baseCase();
        }
        else{
		trip score;
		// Loop through the successors.
                for ( unsigned int i = 0; i < successor.size(); i++ ){
			if( scores.find( successor[i].board ) != scores.end() ){
				score.first = scores.find(
				successor[i].board )->second;
			}
			else{
				// Invert the board.
				j = invert( successor[i].board );
				successor[i].board = j;
				turn = i;
				// Recurse on the current succesor.
				score = solver( turn, findSuccessors(
						successor[i] ));
				// Negate the score because our oponents worst
				// is our best.
				score.first = -( score.first );
				// Store the score and the board for
				// memoization.
				scores.insert( pair<
					const vector< vector<int> >, int >
					( successor[i].board, score.first ));
			}
			// If the score is better then our current best
			// replace the current best.
                        if ( score.first > bScore ){
                                bScore = score.first;
                                bMove = successor[i].second;
				bb = invert( successor[i].board );
                        }
                }
		// Return the best move.
                return trip( bScore, bMove, bb );
        }
}
