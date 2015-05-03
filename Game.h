/**
 * Name: Game.h
 * Description: The header file for the Game class.
 *
 * $Id: Game.h,v 1.6 2012/11/07 19:10:46 jem4687 Exp jem4687 $
 *
 * Revisions:
 * $Log: Game.h,v $
 * Revision 1.9  2012/11/07 19:10:46  jem4687
 * Pretty up the comments
 *
 * Revision 1.8  2012/10/29 02:40:02  mal4012
 * Minor comment changes.
 *
 * Revision 1.7  2012/10/25 00:45:24  jem4687
 * Changed findsuccessors to receive a trip
 *
 * Revision 1.6  2012/10/22 01:58:21  jem4687
 * Redid Comments.
 *
 * Revision 1.5  2012/10/21 03:04:07  mal4012
 * Changed memoization.
 *
 * Revision 1.4  2012/10/18 03:22:10  p334-04e
 * Mem works now.
 *
 * Revision 1.3  2012/10/11 02:32:07  jem4687
 * Included inheritence.
 *
 * Revision 1.2  2012/10/10 23:58:42  jem4687
 * added memoization
 *
 * Revision 1.1  2012/10/10 21:46:42  jem4687
 * Initial revision
 *
 * @author:Jesse Martinez
 * @author:Michael Loper
 */

#ifndef GAME_H
#define GAME_H

#include <vector>
#include <utility>
#include <string>
#include <map>
#include <list>

/**
 * Name: triple
 *
 * Description: A template for a custom triple structure.
 */
template < class T1, class T2, class T3 > struct triple
{
        T1 first;
        T2 second;
        T3 board;
        triple()
                : first( T1() ), second( T2() ), board( T3() ) {}
        triple( const T1& x, const T2& y, const T3& z )
                : first( x ), second( y ), board( z ) {}
        template < class U, class V, class W >
        triple (const triple< U,V,W > &p)
                : first(p.first), second(p.second), board( p.board ) {}
};

//Typedef for our created triple type.
typedef triple< int, int, std::vector< std::vector<int> > > trip;

class Game
{
	private:
		/** A vector to store the scores of moves already evaluated. */
		std::map< const std::vector< std::vector<int> >, int > scores;

		/** An int to store the data of the current game. */
		int data;
	public:

		/**
		 * Constructor
		 *
		 * Description:  Creates a game with initial data "d".
		 *
		 * @param d      - The initial data of the game.
		 */
		Game( int d );

		/**
		 * Deconstructor
		 *
		 * Description:  Default deconstructor for a Game object.
		 */
		virtual ~Game() = 0;

		/**
		 * Name: getData
		 *
		 * Description: Retrieve the current data of the game.
		 *
		 * @return      The data.
		 */
		int getData();

		/**
		 * Name: changeData
		 *
		 * Description: Descreases the current data of the game by 
		 * the amount specified.
		 *
		 * @param m     - The amount to decrease the data.
		 */
		void changeData( int m );

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
		trip solver( int turn, std::vector< trip > successor );

		/**
		 * Name: findSuccessors
		 *
		 * Description: Generates all possible valid moves for
		 * whichever game is being played.
		 *
		 * @param int - The number of data left in the game.
		 *        vector< vector< int> >     - The current board.
		 *
		 * @return      A vector of all the successors.
		 */
		virtual std::vector< trip > findSuccessors( trip b ) = 0;

		/**
		 * Name: print
		 *
		 * Description: Prints out the redition of the current Game
		 * being played.
		 */
		virtual void print() = 0;

		/**
		 * Name: moveHuman
		 *
		 * Description: A move for a human player to be implemented in
		 * a specific game class.
		 *
		 * @param p    - A string representing either player "X" or "O".
		 *
		 * @return     The number of data chosen.
		 */
		virtual int moveHuman(std::string p) = 0;

		/**
		 * Name: move
		 *
		 * Description:  Implements a move for whoevers turn it is.
		 *
		 * @param p      - The number representing whose turn it is.
		 */
		virtual void move( int p ) = 0;

		/**
		 * Name: checkBaseCase
		 *
		 * Description:  Determines if a base case as been reached.
		 *
		 * @param check  - A vector of the remaining moves.
		 *
		 * @return       True iff there are one or less remaining moves.
		 */
		virtual bool checkBaseCase( std::vector< trip > check ) const
		= 0;

		/**
		 * Name: baseCase
		 *
		 * Description: Returns a standard base case representation for
		 *              whatever game is being played.
		 *
		 * @return      A triple with a score, move, and board.
		 */
		virtual trip baseCase() const = 0;

		/**
		 * Name: generateBoard
		 *
		 * Description: Generates the board for the specific game.
		 *
		 * @param b     - The board.
		 */
		virtual void generateBoard( std::vector<std::string> b ) = 0;

		/** A public board representing the current game. */
		std::vector< std::vector<int> > board;

		/** A public int that keeps track of the turn. */
		int turn;

		//TODO
		virtual std::vector< std::vector<int> > invert( std::vector<
		std::vector<int> > b ) = 0;
};

inline Game::~Game(){};

#endif
