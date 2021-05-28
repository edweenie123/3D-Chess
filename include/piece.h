#ifndef piece_h
#define piece_h

#include "coordinate.h"
#include<string>

using namespace std;

class Piece {
    private:
        bool isAlive;
        Coordinate location;
        int color;
        string identifier;
    public:
        Piece();
        Piece(int row_, int col_, int lvl_, int color_);

        int getColor();
        Coordinate getLocation();
        void setLocation(int row_, int col_, int lvl_);
        string toString();
};

#endif