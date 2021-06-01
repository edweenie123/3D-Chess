#include "../include/solver.h"

Solver::Solver(int difficulty_) {
    difficulty = difficulty_;
}

double Solver::evaluate(Board board){
    // Todo: implement board evaluator
    return 0;
}

Turn Solver::nextMove(Board board, int colour){
    // Todo: call solve() to obtain next move here
    return Turn(0, Coordinate(0, 0, 0), Move(0, 0, 0));
}

Turn Solver::solve(Board board, int colour){
    // Todo: implement minimax algo here
    return Turn(0, Coordinate(0, 0, 0), Move(0, 0, 0));
}
