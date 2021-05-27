#ifndef piece_h
#define piece_h

#include<coordinate.h>
#include<string>

using namespace std;

class Piece {
    private:
        bool isAlive;
        Coordinate location;
        int color;
    public:
        Piece();
        Piece(int row, int col, int lvl, int color);

        int getColor();
        int getLocation();
        void getIdentifier();
        void setIdentifier();
        void setLocation();
        string toString();
};

#endif