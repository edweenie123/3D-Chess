/* Board class. Initializes the 3D chessboard, along with methods to move pieces and detect game states */

#ifndef board_h
#define board_h

#include "piece.h"
#include "coordinate.h"
#include "move.h"
#include "globals.h"

class Piece;

class Board {
    private:
    public:
        // Vector is used to allow c++ code to be compiled into Webassembly to be run by Javascript
        vector<vector<vector<Piece*>>> board =
            vector<vector<vector<Piece*>>>(BOARD_SIZE, vector<vector<Piece*>>(BOARD_SIZE, vector<Piece*>(BOARD_SIZE, NULL)));

        Board();
        Piece* getPieceAt(Coordinate square);
        Piece* getPieceAt(int row, int col, int lvl);
        void updateLocation(Coordinate square, Move movement);
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
