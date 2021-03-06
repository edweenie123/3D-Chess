/* Binding definitions. Makes methods in C++ backend available for javascript frontend */

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
    class_<Turn>("Turn")
        .constructor<int, Coordinate, Move>()
        .property("score", &Turn::score)
        .property("currentLocation", &Turn::currentLocation)
        .property("change", &Turn::change)
        ;
    class_<Piece>("Piece")
        .constructor<int, int, int, int>()
        .function("getMoves", &Piece::getMoves)
        .function("getIsAlive", &Piece::getIsAlive)
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
        .function("promote", &Pawn::promote, allow_raw_pointers())
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
    class_<Empty, base<Piece>>("Empty")
        .constructor<int, int, int, int>()
        .function("getMoves", &Empty::getMoves)
        .function("getId", &Empty::getId)
        ;
    class_<Board>("Board")
        .constructor()
        .function("getBoard", &Board::getBoard)
        .function("updateLocation", &Board::updateLocation)
        .function("isChecked", &Board::isChecked)
        .function("isCheckmated", &Board::isCheckmated)
        .function("isStalemated", &Board::isStalemated)
        .function("getGameState", &Board::getGameState)
        ;
    class_<Solver>("Solver")
        .constructor<int>()
        .function("nextMove", &Solver::nextMove)
        .function("evaluate", &Solver::evaluate)
        ;
    register_vector<Piece*>("vp*");
    register_vector<Move>("vm");
    register_vector<vector<Piece*>>("vvp*");
    register_vector<vector<vector<Piece*>>>("vvvp*");
}


#endif
