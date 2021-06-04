#ifndef turn_h
#define turn_h

#include "coordinate.h"
#include "move.h"
using namespace std;

class Turn {
    private:
    public:
        double score;
        Coordinate currentLocation;
        Move change;
        Turn(double, Coordinate, Move);
        Turn& operator= (const Turn&);
};

#endif
