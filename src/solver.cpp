#include "../include/solver.h"

random_device Solver::m_rd;
mt19937       Solver::m_rng(Solver::m_rd());
uniform_int_distribution<int> Solver::rng(0, INF);
unordered_map<char, double> Solver::pieceWeight = {
    {'b', 3}, {'k', 200}, {'n', 3}, {'p', 1}, {'q', 9}, {'r', 5}, {'u', 3}
};

Solver::Solver(int difficulty_) {
    difficulty = difficulty_;
}

int Solver::randRange(int low, int high){
    int range = high - low + 1;
    assert(range > 0);
    return low + rng(m_rng) % range;
}

double Solver::evaluate(Board &board){
    if(difficulty == 0){
        // Beginner difficulty: Blind movement (The computer will choose by random)
        return 0;
    } else if(difficulty == 1){
        // Normal difficulty: Random leaf values (Utilize the Beal effect)
        return randRange(-INF, INF);
    }
    assert(difficulty == 2);
    // Hard difficulty: Sum of difference active piece scores
    double score = 0;
    for(int row = 0; row < 5; ++row){
        for(int col = 0; col < 5; ++col){
            for(int lvl = 0; lvl < 5; ++lvl){
                if(!board.getPieceAt(row, col, lvl).isAlive) continue;
                //cout << to_string(board.getPieceAt(row, col, lvl).id) + "?" << endl;
                //cout << board.getPieceAt(row, col, lvl).color << endl;
                score += pieceWeight[board.getPieceAt(row, col, lvl).id] * max(0, board.getPieceAt(row, col, lvl).color);
            }
        }
    }
    return score;
}

vector<Turn> Solver::genMoves(Board board, int colour){
    // Todo: implement minimax algo here
    return {Turn(0, Coordinate(0, 0, 0), Move(0, 0, 0))};
}

Turn Solver::nextMove(Board board, int colour){
    // Todo: call solve() to obtain next move here
    return Turn(0, Coordinate(0, 0, 0), Move(0, 0, 0));
}

Turn Solver::solve(Board board, int depth, int colour){
    // Todo: implement minimax algo here
    return Turn(0, Coordinate(0, 0, 0), Move(0, 0, 0));
}

