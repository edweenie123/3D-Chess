#include "../include/turn.h"

Turn::Turn(int score_, Coordinate currentLocation_, Move change_){
    score = score_;
    currentLocation = currentLocation_;
    change = change_;
}

Turn& Turn::operator= (const Turn& turn){
    score = turn.score;
    currentLocation = turn.currentLocation;
    change = turn.change;
    return *this;
}
