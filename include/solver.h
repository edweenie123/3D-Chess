#ifndef solver_h
#define solver_h

#include "turn.h"
#include "board.h"
using namespace std;

struct Solver {
    private:
        int difficulty;
        Turn solve(Board board, int colour);
    public:
        Solver(int);
        double evaluate(Board board);
        Turn nextMove(Board board, int colour);
};

#endif
