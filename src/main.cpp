#include <iostream>
#include <cassert>
#include "../include/coordinate.h"
#include "../include/move.h"
#include "../include/piece.h"
#include "../include/rook.h"

using namespace std;

int main() {
    Coordinate coordTest(1, 2, 3);
    Move movementTest(0, -1, 5), delta(5, 0, -2);
    Rook testRook = Rook(0, 0, 0, 0);


    // toString asserts
    assert(coordTest.toString() == "(1, 2, 3)");
    assert(movementTest.toString() == "Move by (0, -1, 5) cells");

    // Addition overload asserts
    coordTest += movementTest;
    movementTest += delta;
    assert((movementTest + delta).toString() == "Move by (10, -1, 1) cells");
    assert((coordTest + delta).toString() == "(6, 1, 6)");




    cout << "Tests passed succesfully" << endl;
}
