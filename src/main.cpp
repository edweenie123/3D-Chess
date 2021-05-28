#include <iostream>
#include <cassert>
#include "../include/coordinate.h"
#include "../include/move.h"

using namespace std;

int main() {
    Coordinate coordTest(1, 2, 3);
    Move movementTest(0, -1, 5);
    
    assert(coordTest.toString() == "(1, 2, 3)");
    assert(movementTest.toString() == "Move by (0, -1, 5) cells");
    cout << "Working tests" << endl;
}