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
    // As an extension, a different evaluation function should be derived which takes in the mobility of every piece
    double score = 0;
    for(int row = 0; row < 5; ++row){
        for(int col = 0; col < 5; ++col){
            for(int lvl = 0; lvl < 5; ++lvl){
                if(!board.getPieceAt(row, col, lvl)->isAlive) continue;
                score += pieceWeight[board.getPieceAt(row, col, lvl)->getId()] * board.getPieceAt(row, col, lvl)->color;
            }
        }
    }
    return score;
}

vector<Turn> Solver::genMoves(Board &board, int color){
    /*int verdict = board.getGameState();
    vector<Turn> moves;
    if(verdict == 1){ // Checkmate

    }*/
    return {Turn(0, Coordinate(0, 0, 0), Move(0, 0, 0))};
}

Turn Solver::nextMove(Board board, int colour){
    // Todo: call solve() to obtain next move here
    return Turn(0, Coordinate(0, 0, 0), Move(0, 0, 0));
}

Turn Solver::solve(Board &board, int depth, int color){

    // Will add checkmate and check conditions once those are implemented
    // As a result, this is very untested

    /*int verdict = board.getGameState();
    // First, look for checks
    if(verdict == board.BLACK_CHECK){
        return -INF;
    } else if(verdict == board.BLACK_CHECK){
        return
    }*/

    if(depth == 0){
        return Turn(evaluate(board), Coordinate(-1, -1, -1), Move(0, 0, 0));
    }

    Turn best(color == WHITE ? -INF : INF, Coordinate(-1, -1, -1), Move(0, 0, 0));
    vector<Turn> legalMoves = genMoves(board, color);
    for(Turn curMove : legalMoves){
        Coordinate oldLoc = curMove.currentLocation;
        Coordinate newLoc = curMove.currentLocation + curMove.change;
        Piece* curPiece = board.getPieceAt(oldLoc);
        Piece* oldPiece = board.getPieceAt(newLoc);
        bool isOldAlive = oldPiece->isAlive;
        board.updateLocation(oldLoc, curMove.change);
        Turn candidate = Turn(solve(board, depth - 1, -color).score, oldLoc, curMove.change);
        // Revert move
        if(isOldAlive){
            oldPiece->isAlive = true;
            board.setPieceAt(oldPiece);
        }
        // White =  1 --> Maximizing
        // Black = -1 --> Minimizing
        if(candidate.score * color > best.score){
            best = candidate;
        }
    }
    return best;
}

