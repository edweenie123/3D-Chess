#ifndef bindings_h
#define bindings_h

#include <emscripten/bind.h>
using namespace emscripten;

EMSCRIPTEN_BINDINGS() {
    class_<Move>("Move")
        .constructor<int, int, int>()
        .property("row", &Move::row)
        .property("col", &Move::col)
        .property("lvl", &Move::lvl)
        ; 
    class_<Coordinate>("Coordinate")
        .constructor<int, int, int>()
        .property("row", &Coordinate::row)
        .property("col", &Coordinate::col)
        .property("lvl", &Coordinate::lvl)
        ; 
    class_<Piece>("Piece")
        .constructor<int, int, int, int>()
        .function("getMoves", &Piece::getMoves)
        .property("isAlive", &Piece::isAlive)
        .function("getId", &Piece::getId)
        .function("getColor", &Piece::getColor)
        ;
    class_<Rook, base<Piece>>("Rook")
        .constructor<int, int, int, int>()
        .function("getMoves", &Rook::getMoves)
        .function("getId", &Rook::getId)
        ;
    class_<Pawn, base<Piece>>("Pawn")
        .constructor<int, int, int, int>()
        .function("getMoves", &Pawn::getMoves)
        .function("getId", &Pawn::getId)
        ;
    class_<Bishop, base<Piece>>("Bishop")
        .constructor<int, int, int, int>()
        .function("getMoves", &Bishop::getMoves)
        .function("getId", &Bishop::getId)
        ;
    class_<Queen, base<Piece>>("Queen")
        .constructor<int, int, int, int>()
        .function("getMoves", &Queen::getMoves)
        .function("getId", &Queen::getId)
        ;
    class_<King, base<Piece>>("King")
        .constructor<int, int, int, int>()
        .function("getMoves", &King::getMoves)
        .function("getId", &King::getId)
        ;
    class_<Knight, base<Piece>>("Knight")
        .constructor<int, int, int, int>()
        .function("getMoves", &Knight::getMoves)
        .function("getId", &Knight::getId)
        ;
    class_<Unicorn, base<Piece>>("Unicorn")
        .constructor<int, int, int, int>()
        .function("getMoves", &Unicorn::getMoves)
        .function("getId", &Unicorn::getId)
        ;

    class_<Board>("Board")
        .constructor()
        .property("board", &Board::board)
        .function("updateLocation", &Board::updateLocation)
        ;

    register_vector<Piece*>("vp*");
    register_vector<Move>("vm");
    register_vector<vector<Piece*>>("vvp*");
    register_vector<vector<vector<Piece*>>>("vvvp*");
}


#endif