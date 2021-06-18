#include "../include/empty.h"

char Empty::getId() {
    return ' ';
}

vector<Move> Empty::getMoves(Board board, bool prune) {
    vector<Move> emptyVector;
    return emptyVector;
}