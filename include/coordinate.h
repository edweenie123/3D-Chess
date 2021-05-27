#ifndef coordinate_h
#define coordinate_h

struct Coordinate {
    private:
        int row;
        int col;
        int lvl;
    public:
        Coordinate();
        Coordinate(int row, int col, int lvl);
        // might add toChessNotation method
};

#endif