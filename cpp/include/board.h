#ifndef board_h
#define board_h

#include "piece.h"
#include "coordinate.h"
#include "move.h"
#include <vector>
#include <iostream>
#include <set>
#include "globals.h"
using namespace std;

typedef pair<int, int> ii;
typedef pair<ii, int> iii;

class Piece;

class Board {
    private:
    public:

        // I can't get embind to work with arrays, so gotta use yucky vector lol
        vector<vector<vector<Piece*>>> board = 
            vector<vector<vector<Piece*>>>(5, vector<vector<Piece*>>(5, vector<Piece*>(5, NULL)));
        // Piece* board[5][5][5];

        set<iii> threatenedByWhite;
        set<iii> threatenedByBlack;

        Board();
        Piece* getPieceAt(Coordinate square);
        Piece* getPieceAt(int row, int col, int lvl);
        void updateThreatenedSquares();
        void updateLocation(Coordinate square, Move movement);
        void setPieceAt(Piece *piece);
        void printBoard();

        bool isChecked(int pieceColor); // is king of color "pieceColor" checked?
        bool isCheckmated(int pieceColor); // is king of color "pieceColor" checkmated? (only run this is isChecked() == true)
        bool isStalemated(int pieceColor); // is side of color "pieceColor" stalemated?
        string getGameState(int turnPlayer); // returns the state of the game in a string
        /*
        * Possible Game States:
        *
        * White King is Checked!
        * Black King is Checked!
        * Checkmate! White Wins.
        * Checkmate! Black Wins.
        * Stalemate.
        * No special events. Game proceeding normally...
        */

        bool isVacant(Coordinate cord); // returns true if cord is vacant
        bool isOnBoard(Coordinate cord); // return true if cord is on board
        bool isEnemySquare(Coordinate cord, int pieceColor); // returns true if cord contains an ememy piece
};

#endif
