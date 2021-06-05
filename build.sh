# compiles c++ code to get WASM binary => main.wasm
# bind WASM with js glue code => main.js

rm build/ -rf
mkdir build 
cd build
em++ --bind -c ../cpp/src/globals.cpp ../cpp/src/coordinate.cpp ../cpp/src/move.cpp ../cpp/src/piece.cpp ../cpp/src/board.cpp ../cpp/src/king.cpp ../cpp/src/knight.cpp ../cpp/src/pawn.cpp ../cpp/src/queen.cpp ../cpp/src/rook.cpp ../cpp/src/unicorn.cpp ../cpp/src/bishop.cpp ../cpp/src/turn.cpp ../cpp/src/solver.cpp ../cpp/src/main.cpp
em++ --bind globals.o coordinate.o move.o piece.o board.o king.o knight.o pawn.o queen.o rook.o unicorn.o bishop.o turn.o solver.o main.o -o main.js
mv main.js ../web/gen/
mv main.wasm ../web/gen/



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

