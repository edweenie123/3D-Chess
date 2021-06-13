# compiles c++ code to get WASM binary => a.out.wasm
# bind WASM with js glue code => a.out.js

rm build/ -rf
mkdir build 
cd build
em++ -O3 --bind ../cpp/src/main.cpp ../cpp/src/globals.cpp ../cpp/src/coordinate.cpp ../cpp/src/move.cpp ../cpp/src/piece.cpp ../cpp/src/board.cpp ../cpp/src/king.cpp ../cpp/src/knight.cpp ../cpp/src/pawn.cpp ../cpp/src/queen.cpp ../cpp/src/rook.cpp ../cpp/src/unicorn.cpp ../cpp/src/bishop.cpp ../cpp/src/turn.cpp ../cpp/src/solver.cpp -s TOTAL_MEMORY=64MB
mv a.out.js ../web/gen/
mv a.out.wasm ../web/gen/


# globals.cpp
# coordinate.cpp
# move.cpp
# piece.cpp
# board.cpp
# king.cpp
# knight.cpp
# pawn.cpp
# queen.cpp
# rook.cpp
# unicorn.cpp
# bishop.cpp
# turn.cpp
# solver.cpp
# main.cpp

