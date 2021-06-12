#include "../include/solver.h"

random_device Solver::m_rd;
mt19937       Solver::m_rng(Solver::m_rd());
uniform_int_distribution<int> Solver::rng(0, INF);
unordered_map<char, double> Solver::pieceWeight = {
    {'b', 3}, {'k', 1}, {'n', 3}, {'p', 2}, {'q', 6}, {'r', 5}, {'u', 3}
};

Solver::Solver(int difficulty_) {
    difficulty = difficulty_;
}

int Solver::randRange(int low, int high){
    int range = high - low + 1;
    assert(range > 0);
    return low + rng(m_rng) % range;
}

double Solver::distance(Coordinate coord){
    return (6 - (abs(coord.row - 2) + abs(coord.col - 2) + abs(coord.lvl - 2))) / 6.0;
}

double Solver::evaluate(Board &board){
    if(difficulty == 0){
        // Beginner difficulty: Blind movement (The computer will choose by random)
        return 0;
    } else if(difficulty == 1){
        // Normal difficulty: Random leaf values (Utilize the Beal effect)
        return randRange(-INF, INF);
    }
    // Hard difficulty: Sum of difference active piece scores, each multiplied by their relative position to the center (calculated using manhattan distance)
    double score = 0;
    for(int row = 0; row < 5; ++row){
        for(int col = 0; col < 5; ++col){
            for(int lvl = 0; lvl < 5; ++lvl){
                if(!board.getPieceAt(row, col, lvl)->isAlive) continue;
                score += (pieceWeight[board.getPieceAt(row, col, lvl)->getId()] + distance({row, col, lvl})) * board.getPieceAt(row, col, lvl)->color;
            }
        }
    }
    return score;
}

vector<Turn> Solver::genMoves(Board &board, int color){
    vector<Turn> moves;
    for(int i = 0; i < 5; ++i) {
        for(int j = 0; j < 5; ++j) {
            for(int k = 0; k < 5; ++k) {
                if(board.board[i][j][k]->color == color && board.board[i][j][k]->isAlive){
                    // Go through all the moves, make sure you don't leave your king checked
                    for (Move m : board.board[i][j][k]->getMoves(board, false)) {
                        Piece* oldPiece = board.getPieceAt({i + m.row, j + m.col, k + m.lvl});
                        board.updateLocation({i, j, k}, m);
                        if(!board.isChecked(color)) {
                            // Valid move
                            moves.push_back(Turn(0, Coordinate(i, j, k), m));
                        }
                        // undo the move
                        board.updateLocation({i + m.row, j + m.col, k + m.lvl}, -m);
                        if (oldPiece->getId() != ' ') {
                            board.board[i + m.row][j + m.col][k + m.lvl] = oldPiece;
                            oldPiece->isAlive = true;
                        }
                    }
                }
            }
        }
    }
    // Shuffle moves for better pruning effect 
    shuffle(moves.begin(), moves.end(), m_rng);
    return moves;
}

Turn Solver::nextMove(Board board, int colour){
    return solve(board, 2, -INF, INF, colour);
}

Turn Solver::solve(Board &board, int depth, double ALPHA, double BETA, int color){
  
    // First look for checkmates, then stalemates
    if(board.isChecked(color)){
        if(board.isCheckmated(color)){
            // White Mate --> -INF, Black Mate --> INF 
            return Turn(INF * -color, Coordinate(-1, -1, -1), Move(0, 0, 0));
        }
    } else if(board.isStalemated(color)){
        // Nobody wins
        return Turn(0, Coordinate(-1, -1, -1), Move(0, 0, 0));
    }

    if(depth == 0){
        // Evaluate board
        return Turn(evaluate(board), Coordinate(-1, -1, -1), Move(0, 0, 0));
    }

    Turn best(color == WHITE ? -INF : INF, Coordinate(-1, -1, -1), Move(0, 0, 0));
    for(Turn curMove : genMoves(board, color)){
        // Move new piece
        Coordinate newLoc = curMove.currentLocation + curMove.change;
        Piece* oldPiece = board.getPieceAt(newLoc);
        board.updateLocation(curMove.currentLocation, curMove.change);
        // Recurse
        Turn candidate = Turn(solve(board, depth - 1, ALPHA, BETA, -color).score, curMove.currentLocation, curMove.change);
        // Revert move
        board.updateLocation(newLoc, -curMove.change);
        if(oldPiece->getId() != ' '){
            board.board[newLoc.row][newLoc.col][newLoc.lvl] = oldPiece;
            oldPiece->isAlive = true;
        }
        // White --> Maximizing
        // Black --> Minimizing
        if(color == WHITE){
            ALPHA = max(ALPHA, best.score);
            if(candidate.score > best.score){
                best = candidate;
                if(best.score >= BETA){ // alpha-beta pruning
                    break;
                }
            }
        } else {
            BETA = min(BETA, best.score);
            if(candidate.score < best.score){
                best = candidate;
                if(best.score <= ALPHA){ // alpha-beta pruning
                    break;
                }
            }
        }
    }
    return best;
}

