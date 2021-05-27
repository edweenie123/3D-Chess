#ifndef coordinate_h
#define coordinate_h

class Coordinate {
    private:
        int row;
        int col;
        int lvl;
    public:
        Coordinate();
        Coordinate(int row, int col, int lvl);
};

#endif