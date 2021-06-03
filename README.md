# 3D-Chess

This repository was created for the ICS4U summative project, featuring an interactive game of the [Raumschach variant of 3D Chess](https://www.chessvariants.com/3d.dir/3d5.html).

This project is coded using C++ using object-oriented programming.

## Compile:
```
g++ -c globals.cpp coordinate.cpp move.cpp piece.cpp board.cpp king.cpp knight.cpp pawn.cpp queen.cpp rook.cpp unicorn.cpp bishop.cpp turn.cpp solver.cpp main.cpp
```
## Link:
```
g++ -o main globals.o coordinate.o move.o piece.o board.o king.o knight.o pawn.o queen.o rook.o unicorn.o bishop.o turn.o solver.o main.o
```

## Run:
```
./main
```

## Structure
The UML diagram of our project can be viewed here: https://lucid.app/lucidchart/invitations/accept/inv_529971e3-e538-4ff5-8454-612c1587092a
### [`/include`](include)

```
.
├── ...
├── include
│   ├── ...
│   ├── board.h				
│   ├── coordinate.h	
│   ├── move.h			
│   └── piece.h				
└── ...
```

### [`/src`](src)

```
.
├── ...
├── src
│   ├── main.cpp			
│   ├── board.cpp			
│   ├── coordinate.cpp			
│   ├── move.cpp				
│   └── piece.cpp			
└── ...
```
