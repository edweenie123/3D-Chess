/* Move class, describing piece movement on 3D chess board, including operator overloads for piece movement arithmetic */

#ifndef move_h
#define move_h

#include "globals.h"

class Move {
    private:
    public:
        // Bundles change in row, change in column, and change in lvl into one Move object
        int row, col, lvl;

        // Constructors
        Move();
        Move(int row, int col, int lvl);

        string toString();

        // Operator overloads for easy Move arithmetic
        Move operator+(const Move&);
        Move& operator+=(const Move&);
        Move& operator=(const Move&);
        Move operator-();
};

#endif
