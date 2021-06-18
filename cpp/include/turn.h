/* Turn class, used by solver class to evaluate board positions */

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
        
        // Constructor
        Turn(int, Coordinate, Move);

        // Assignment operator overload
        Turn& operator= (const Turn&);
};

#endif
