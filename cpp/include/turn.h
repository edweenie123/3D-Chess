#ifndef turn_h
#define turn_h

#include "coordinate.h"
#include "move.h"
#include "globals.h"

class Turn {
    private:
    public:
        int score;
        Coordinate currentLocation;
        Move change;
        Turn(int, Coordinate, Move);
        Turn& operator= (const Turn&);
};

#endif
