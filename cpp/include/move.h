#ifndef move_h
#define move_h

#include "globals.h"

class Move {
    private:
    public:
        int row, col, lvl;
        Move();
        Move(int row, int col, int lvl);
        string toString();
        Move operator+(const Move&);
        Move& operator+=(const Move&);
        Move& operator=(const Move&);
        Move operator-();
};

#endif
