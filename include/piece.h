#ifndef piece_h
#define piece_h

#include "coordinate.h"
#include<string>

using namespace std;

class Piece {
    private:
    public:
        bool isAlive;
        Coordinate location;
        int color;
        string identifier;
        Piece();
        Piece(int row, int col, int lvl, int color);

        int getColor();
        Coordinate getLocation();
        void setLocation(int row, int col, int lvl);
        string toString();
};

#endif