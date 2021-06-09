/*
To-do:
    make board size dynamic (based of screen size)?
    rerender on window resize
*/

class Board {
  constructor() {
    this.boardDiv = document.getElementById("board");
    this.size = 5;
    this.squareSize = 40;
    this.cppBoard = new Module.Board();
  }

  // returns a the piece object located at a specific coordinate
  getPiece(row, col, lvl) {
    return this.cppBoard.board.get(row).get(col).get(lvl);
  }

  // returns the div located at a specific coordiante
  getSquareDiv(row, col, lvl) {
    return this.boardDiv.childNodes[lvl].childNodes[
      (this.size - 1 - row) * this.size + col
    ];
  }

  // create a div for each square of the board
  renderBoard() {
    for (var i = 0; i < this.size; i++) {
      var boardLvl = document.createElement("DIV");
      boardLvl.className = "boardLvl";

      for (var j = 0; j < this.size; j++) {
        for (var k = 0; k < this.size; k++) {
          var square = document.createElement("DIV");
          square.id = (i + j + k) % 2 ? "lightCol" : "darkCol";
          square.className = "square";
          boardLvl.appendChild(square);
        }
      }

      this.boardDiv.appendChild(boardLvl);
    }
    this.resizeBoard();
  }

  // resize each square and board level to match the size specfied by the "squareSize" attribute
  resizeBoard() {
    var allSquares = document.getElementsByClassName("square");
    Array.from(allSquares).forEach((square) => {
      square.style.width = this.squareSize + "px";
      square.style.height = this.squareSize + "px";
    });

    var allBoardLvl = document.getElementsByClassName("boardLvl");
    Array.from(allBoardLvl).forEach((lvl) => {
      lvl.style.width = this.squareSize * this.size + "px";
      lvl.style.height = this.squareSize * this.size + "px";
    });
  }

  // create images of each piece to match the state of the board
  renderPieces() {
    for (var lvl = 0; lvl < this.size; lvl++) {
      for (var row = 0; row < this.size; row++) {
        for (var col = 0; col < this.size; col++) {
          var piece = this.getPiece(row, col, lvl);
          var pieceId = String.fromCharCode(piece.getId());

          if (pieceId === " ") continue;

          // obtain the image name based off the piece id
          var imageName =
            "../img/" + pieceId + (piece.getColor() == 1 ? "l" : "d") + ".svg";
          var image = document.createElement("img");

          image.src = imageName;
          image.className = "chessImg";

          var square = this.getSquareDiv(row, col, lvl);
          square.appendChild(image);
        }
      }
    }
  }

  updatePiecePosition() {

  }
}
