/* (Almost) Abstract base class, serving as parent class for all child chess pieces */

#ifndef piece_h
#define piece_h

#include "coordinate.h"
#include "move.h"
#include "globals.h"

class Board;

class Piece {
    protected:
        bool isAlive = true;
        Coordinate location;
        int color;
    public:
        Piece();
        Piece(int row, int col, int lvl, int color);
        //virtual ~Piece() = 0;

        int getColor();
        void setColor(int color);
        Coordinate getLocation();
        void setLocation(int row, int col, int lvl);
        bool getIsAlive();
        void setIsAlive(bool alive);

        string toString();
        vector<Move> getAllMovesInLine(vector<Move>, Board, bool); // bool is to specify if we want to prune for checks
        vector<Move> pruneMoves(vector<Move>, Board, Coordinate);
        bool hasAnyMoves(Board, Coordinate); // Checks if a piece has any legal moves

        //virtual vector<Move> getMoves(Board, bool) = 0; // Pure virtual function. Each piece has unique set of moves
        //virtual char getId() = 0;
        virtual vector<Move> getMoves(Board, bool);
        virtual char getId();
        /* NOTE that we would have used pure virtual functions, and made Piece an abstract base class.
        * However emscripten (the program that compiles our C++ code) into webassembly such that it can
        * be run by javascript in the frontend does not support pure virtual methods.
        */
};

#endif
