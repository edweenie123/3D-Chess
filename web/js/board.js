/*
To-do:
    make board size dynamic (based of screen size)?
    rerender on window resize
*/


class Board {
  constructor() {
    this.boardDiv = document.getElementById("board");
    this.size = 5;
    this.cppBoard = new Module.Board();
  }

  // returns a the piece object located at a specific coordinate
  getPiece(row, col, lvl) {
    return this.cppBoard.board.get(row).get(col).get(lvl);
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
  }

  // create images of each piece on to match the state of the board
  renderPieces() {
    for (var i = 0; i < this.size; i++) {
      for (var j = 0; j < this.size; j++) {
        for (var k = 0; k < this.size; k++) {
          var piece = this.getPiece(k, j, i);
          var pieceId = String.fromCharCode(piece.getId());

          if (pieceId === " ") continue;

          var square =
            this.boardDiv.childNodes[i].childNodes[j * this.size + k];

          var imageName =
            "../img/" + pieceId + (piece.getColor() == 1 ? "l" : "d") + ".svg";

          var image = document.createElement("img");
          image.className = "chessImg";
          image.src = imageName;

          square.appendChild(image);
        }
      }
    }
  }

  // const updatePiecePosition = () => {

  // }
}
