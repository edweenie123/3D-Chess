# 3D-Chess

This project is a complete interactive game of the Raumschach variant of 3D Chess and was made as our ICS4U summative. Users may choose to play against an AI with 3 different difficulty levels or with another player locally.  The rules of the game may be found [here](https://www.chessvariants.com/3d.dir/3d5.html).

Play our game at: https://edweenie123.github.io/3D-Chess/

## Features
* 4 different game modes (PvP + 3 AI difficulties)
* UI to select pieces for pawn promotions
* Highlights to show legal moves and the opponent’s last move
* Game history 
* Panel showing piece captures of each side
* Game evaluation bar

## Built With
The move logic, checkmate+stalemate detection and AI were all programmed in C++ and was compiled to [WebAssembly](https://webassembly.org/) using [Emscripten](https://emscripten.org/docs/introducing_emscripten/about_emscripten.html) so that it could be run on the browser. The visual interface of the game was made using vanilla JavaScript, HTML and CSS. 

## Chess AI
Our chess AI was made from scratch and consists of the minimax algorithm with alpha-beta pruning for optimization.

## Installation
To run the game locally

1. Clone the repository 
	``` sh
	git clone https://github.com/edweenie123/3D-Chess.git
	```
2. Serve index.html on port 8080 by running the following command in the project root directory:
	``` sh
	sh serve.sh
	```
	NB: This step requires Python 3 to be installed 
3. Play the game on the browser at http://localhost:8080/

## Team Members
* [Zeyu Chen](https://github.com/zecookiez)
* [Edwin Chen](https://github.com/edweenie123)
* [Allen Tao](https://github.com/allenapplehead)
 






