/**
 * Name: connect3.cpp
 * Description: The main for a Connect3 Game.
 *
 * $Id: connect3.cpp,v 1.4 2012/11/07 19:10:46 jem4687 Exp jem4687 $
 *
 * Revisions:
 * $Log: connect3.cpp,v $
 * Revision 1.8  2012/11/07 19:10:46  jem4687
 * Pretty up the comments
 *
 * Revision 1.7  2012/11/01 00:14:26  jem4687
 * Implemented play aswell as error checking
 *
 * Revision 1.6  2012/10/30 23:48:21  mal4012
 * Changed error handling and added cin mode.
 *
 * Revision 1.5  2012/10/30 02:27:41  jem4687
 * Added scores checking
 *
 * Revision 1.4  2012/10/29 02:40:02  mal4012
 * Minor comment changes.
 *
 * Revision 1.3  2012/10/25 00:45:24  jem4687
 * Changed findsuccessors to receive a trip
 *
 * Revision 1.2  2012/10/22 01:59:39  jem4687
 * Added comments.
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
#include <iterator>
#include <algorithm>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include <cassert>
#include <cstring>
#include <typeinfo>
#include <istream>

#include "Connect3Game.h"
#include "Game.h"

using namespace std;

/**
 * Name: main
 *
 * Description:  Creates and runs a Connect3 Game.
 *
 * @param argc   - The number of arguments entered.
 *        argv[] - A pointer to an array of chars representing the arguments
 *                 entered.
 *
 *
 * @return       0, to indicate a smooth program execution.
 */
int main( int argc, const char* argv[] )
{
	const char* PLAY( "play" );
        // Must receive at least two arguments.
	if ( argc != 2 && argc != 3 ){
		cerr << "Usage: " << argv[0] << " [play] -";
               	cout << endl;
                exit( 1 );
    	}
	else {
		vector<string> board1;
		string strX = "X";
		string strO = "O";
		string strD = ".";
	    	int count = 0;
		int rows;
		int cols;
		int theCounter = 0;
		string theboard;
		string addChar;
		string newboard;
		istringstream iss;
		istream *isp;
		ifstream ifs;
		if( (argc == 2 && !strcmp( "-", argv[1] ) )
			|| (argc == 3 && !strcmp( "-", argv[2] ) ) ){
			string rs;
			string rc;
			cout << "Enter Width: ";
			cin >> rs;
			cout << "Enter Height: ";
			cin >> rc;
			cin.ignore();
			board1.push_back( rs );
			board1.push_back( rc );
			stringstream(rs) >> cols;
			stringstream(rc) >> rows;
			if( !rows || !cols || cols <= 0 || rows <=0 ){
				cerr << "Invalid dimensions" << endl;
				exit(1);
			}
			cout << "Please enter a board config: ";
			getline( cin, theboard );
			string::iterator curChar( theboard.begin() );
			for ( curChar; curChar != theboard.end(); ++curChar ){
				if( (*curChar) != ' ' ){
					addChar = ( *curChar );
					board1.push_back( addChar );
				}
			}
		}
		else{
			if( argc == 2 ){
				ifs.open( argv[1] );
			}
			else{
				ifs.open( argv[2] );
			}
			isp = &ifs;
			istream_iterator<string> it(*isp);
			stringstream(*it) >> rows;
			board1.push_back( *it );
			++it;
			stringstream(*it) >> cols;
			board1.push_back( *it );
			istream_iterator<char> eos;
			cout << rows;
			cout << cols;
			for( istream_iterator<char> it(*isp); it != eos; ++it ){
                        	if( (*it) != ' ' ){
                               	 newboard = (*it);
                               	 board1.push_back( newboard );
                        	}
                	}
		}
		for( unsigned int i = 2; i < board1.size();
                                      ++i ){
			string str1 = board1[i];
			if( str1.compare( strO )
				!= 0 && str1.compare( strX )!= 0 &&
                        		str1.compare( strD )!= 0 ){
                        			cerr << "Incorrect "\
						"character"\
						" in the "\
						"board config.";
						cout << endl;
						exit( 1 );
			}
           		if( board1[i] == "." )
				++count;
			++theCounter;
		}
		if(( rows * cols ) != ( theCounter )){
			cerr << "Incorrect amount of board "\
				"pieces for those dimensions"
				<< endl;
				exit( 1 );
		}
		Connect3Game* cp;
		if( !strcmp( PLAY, argv[1] ) )
			cp = new Connect3Game( 1, count, board1 );
		else
			cp = new Connect3Game( count, board1 );
		Connect3Game& c = (*cp);
		unsigned i;
		for( i = 0; i < c.board[0].size(); ++i){
			triple<int,int,vector< vector<int> > > b2(c.getData(), i, c.board );
			cout << endl;
			cout << endl;
			if( c.checkWin(b2) ){
				cout << "Board already contains a win" << endl;
				delete cp;
				exit(1);
			}
		}
            	cout << "Initial board" << endl;
            	c.print();
		cout << endl;
		if( argc == 2 && strcmp( PLAY, argv[1] ) ){
			if( c.getData() == 0 ){
				cout << "No spaces available";
				delete cp;
				exit(1);
			}
			else{
				triple<int,int,vector< vector<int> > >
					b( c.getData(), -1, c.board );
                    		triple<int,int,vector< vector<int> > >
					moved = c.movePC(
						0,c.findSuccessors( b ));
                		if ( moved.first >= 1 ){
					cout << "Best move in col " <<
						moved.second << endl;
        	        		cout << "New board of " << endl;
                			c.print();
				}
				else{
					cout << "default no good move" << endl;
					c.print();
				}
			}
		}
		else if( !strcmp( PLAY, argv[1] ) ){
			// Play the game.
			int turn = 0;
			bool win = false;
			cout << "here";
            		while ( c.getData() != 0 ){
				if ( turn % 2 == 0 ){
					c.move( 1 );
                    		}
				else{
					c.move( 2 );
				}
				triple< int, int, vector< vector<int> > >
                                        b2( c.getData(), c.getLastPlaced(),
                                        c.board );
				cout << endl;
				cout << c.getLastPlaced();
				cout << endl;
				c.print();
				if( c.checkWin( b2 ) ){
						win = true;
                                                break;
                                }
				++turn;
            		}
			if( c.getData() == 0  && !win )
				cout << "Cats Game" << endl;
                	// Print out the loser.
            		else if (( turn-1 ) % 2 == 0 )
				cout << "Player " << c.getName( 1 )
					<< " loses" << endl;
            		else
				cout << "Player " << c.getName( 2 )
					<< " loses" << endl;
		}
		else{
			cerr << "Usage: " << argv[0] << " [play] -";
                	cout << endl;
		}
		delete cp;
	}
	return 0;
}
