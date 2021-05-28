#include "../include/rook.h"

Rook::Rook(int row_, int col_, int lvl_, int color_){
    location = Coordinate(row_, col_, lvl_);
    color = color_;
};

vector<Move> Rook::getMoves() {
    vector<Move> moves;

   // NEED TO ADD PIECE BLOCKING

    for (int i=location.row+1;i<=5;i++) {
        // moves.push_back(moves)
    }

    for (int i=location.row-1;i>=1;i--) {
       
    }

    for (int i=location.col+1;i<=5;i++) {
       
    }

    for (int i=location.col-1;i>=1;i--) {
       
    }
    
    for (int i=location.lvl+1;i>=5;i++) {
       
    }

    for (int i=location.lvl-1;i<=1;i--) {
       
    }
}