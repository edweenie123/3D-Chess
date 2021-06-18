/* Solver class, contains our CHESS AI featuring 3 levels of difficulty */

#ifndef solver_h
#define solver_h

#include "turn.h"
#include "board.h"
#include "piece.h"
#include "pawn.h"
#include "queen.h"
#include "globals.h"

class Solver {
    private:
        // Instance variables
        int difficulty;
        // Instance methods
        Turn solve(Board &board, int depth, int ALPHA, int BETA, int color, int score);
        int distance(Coordinate coord);
        int pieceScore(Piece *piece);
        bool canPromote(Piece* piece);
        // Static variables
        static unordered_map<char, int> pieceWeight;
        // Random number generator
        static random_device m_rd;
        static mt19937 m_rng;
        static uniform_int_distribution<int> rng;
    public:
        static const int INF = 1e7;
        // Constructor
        Solver(int);
        // Useful utility methods
        int evaluate(Board &board);
        Turn nextMove(Board &board, int colour);
        vector<Turn> genMoves(Board &board, int color);
        static int randRange(int low, int high);
};

#endif
