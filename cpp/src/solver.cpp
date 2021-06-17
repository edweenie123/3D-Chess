#include "../include/solver.h"

random_device Solver::m_rd;
mt19937       Solver::m_rng(Solver::m_rd());
uniform_int_distribution<int> Solver::rng(0, INF);
unordered_map<char, int> Solver::pieceWeight = {
    {'b', 40}, {'k', 100}, {'n', 40}, {'p', 30}, {'q', 60}, {'r', 50}, {'u', 40}
};

Solver::Solver(int difficulty_) {
    difficulty = difficulty_;
}

int Solver::randRange(int low, int high){
    int range = high - low + 1;
    assert(range > 0);
    return low + rng(m_rng) % range;
}

int Solver::distance(Coordinate coord){
    return -(abs(coord.row - 2) * 3 + abs(coord.col - 2) + abs(coord.lvl - 2) * 5);
}

int Solver::pieceScore(Piece *piece){
    // Hard difficulty: Sum of difference active piece scores, each multiplied by their relative position to the center (calculated using manhattan distance)
    if(!piece->isAlive) return 0;
    if(piece->getId() == 'k'){
        // The king should stay away from the center instead
        return (pieceWeight[piece->getId()] - distance(piece->location)) * piece->color;
    }
    return (pieceWeight[piece->getId()] + distance(piece->location)) * piece->color;
}

bool Solver::canPromote(Piece* piece){
    return piece->getId() == 'p' &&
    ((piece->color == WHITE && piece->location.row + piece->location.lvl == 8) ||
     (piece->color == BLACK && piece->location.row + piece->location.lvl == 0));
}

int Solver::evaluate(Board &board){
    int score = 0;
    for(int row = 0; row < 5; ++row){
        for(int col = 0; col < 5; ++col){
            for(int lvl = 0; lvl < 5; ++lvl){
                score += pieceScore(board.getPieceAt(row, col, lvl));
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
                        Piece* oldPiece = board.board[i + m.row][j + m.col][k + m.lvl];
                        int newScore = -pieceScore(board.board[i][j][k]) - pieceScore(oldPiece);
                        board.updateLocation({i, j, k}, m);
                        if(!board.isChecked(color)) {
                            // Valid move
                            moves.push_back(Turn(newScore + pieceScore(board.board[i + m.row][j + m.col][k + m.lvl]), Coordinate(i, j, k), m));
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
    // Sort moves in decreasing score for better pruning effect
    if(color == WHITE) sort(moves.begin(), moves.end(), [](const Turn &lhs, const Turn &rhs){ return lhs.score > rhs.score;});
    else sort(moves.begin(), moves.end(), [](const Turn &lhs, const Turn &rhs){ return lhs.score < rhs.score;});
    return moves;
}

Turn Solver::nextMove(Board &board, int colour){
    // Count the number of pieces left to determine the stage of the game (start, middle, end)
    int countPieces = 0;
    for(int i = 0; i < 5; ++i)
        for(int j = 0; j < 5; ++j)
            for(int k = 0; k < 5; ++k)
                if(board.board[i][j][k]->color == -colour && board.board[i][j][k]->isAlive)
                    ++countPieces;
    if(difficulty == 0 && countPieces >= 10){
        // Easy mode -- randomly choose a move
        vector<char> active;
        vector<Turn> moves = genMoves(board, colour);
        shuffle(moves.begin(), moves.end(), m_rng);
        // Just in case someone tried to get another move after a checkmate
        if(moves.empty()){
            return Turn(0, Coordinate(-1, 0, 0), Move(0, 0, 0));
        }
        for(auto turn : moves){
            active.push_back(board.getPieceAt(turn.currentLocation)->getId());
        }
        sort(active.begin(), active.end());
        active.erase(unique(active.begin(), active.end()), active.end());
        // Choose a random piece
        char tgt = active[randRange(0, active.size() - 1)];
        for(auto turn : moves){
            if(board.getPieceAt(turn.currentLocation)->getId() == tgt){
                return turn;
            }
        }
        return Turn(0, Coordinate(-1, 0, 0), Move(0, 0, 0));
    }
    return solve(board, 3, -INF, INF, colour, evaluate(board));
}

Turn Solver::solve(Board &board, int depth, int ALPHA, int BETA, int color, int score){

    // First look for checkmates, then stalemates
    if(board.isChecked(color)){
        if(board.isCheckmated(color)){
            // White Mate --> -INF, Black Mate --> INF
            return Turn(INF * -color, Coordinate(-2, -1, -1), Move(0, 0, 0));
        }
    } else if(board.isStalemated(color)){
        // Nobody wins
        return Turn(0, Coordinate(-1, -1, -1), Move(0, 0, 0));
    }

    if(depth == 0){
        // Evaluate board
        return Turn(score + (difficulty == 2 ? randRange(-3, 3) : randRange(-20, 20)), Coordinate(-4, -1, -1), Move(0, 0, 0));
    }

    Turn best(color == WHITE ? -INF : INF, Coordinate(-3, -1, -1), Move(0, 0, 0));
    for(Turn curMove : genMoves(board, color)){
        // Move new piece
        Coordinate newLoc = curMove.currentLocation + curMove.change;
        Piece *pawn, *oldPiece = board.getPieceAt(newLoc);
        int newScore = score + curMove.score;
        board.updateLocation(curMove.currentLocation, curMove.change);
        bool promoted = canPromote(board.getPieceAt(newLoc));
        if(promoted){
            pawn = board.getPieceAt(newLoc);
            newScore -= pieceScore(board.getPieceAt(newLoc));
            ((Pawn*)pawn)->promote(board, new Queen(newLoc.row, newLoc.col, newLoc.lvl, color), false);
            newScore += pieceScore(board.getPieceAt(newLoc));
        }
        // Recurse
        Turn candidate = Turn(solve(board, depth - 1, ALPHA, BETA, -color, newScore).score, curMove.currentLocation, curMove.change);
        // Revert move
        if(promoted){
            delete board.board[newLoc.row][newLoc.col][newLoc.lvl];
            board.board[newLoc.row][newLoc.col][newLoc.lvl] = pawn;
        }
        board.updateLocation(newLoc, -curMove.change);
        if(oldPiece->getId() != ' '){
            board.board[newLoc.row][newLoc.col][newLoc.lvl] = oldPiece;
            oldPiece->isAlive = true;
        }
        // White --> Maximizing
        // Black --> Minimizing
        if(color == WHITE){
            ALPHA = max(ALPHA, best.score);
            if(candidate.score >= best.score){
                best = candidate;
                if(best.score >= BETA){ // alpha-beta pruning
                    break;
                }
            }
        } else {
            BETA = min(BETA, best.score);
            if(candidate.score <= best.score){
                best = candidate;
                if(best.score <= ALPHA){ // alpha-beta pruning
                    break;
                }
            }
        }
    }
    return best;
}

