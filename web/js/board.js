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
    for (var lvl = 0; lvl < this.size; lvl++) {
      var boardLvl = document.createElement("DIV");
      boardLvl.className = "boardLvl";

      for (var row = 0; row < this.size; row++) {
        for (var col = 0; col < this.size; col++) {
          var square = document.createElement("DIV");
          square.className = "square";
          // set the color of the square to get checkboard pattern
          square.className += (lvl + row + col) % 2 ? " lightCol" : " darkCol";
          square.dataset["coordinate"] = [this.size - 1 - row, col, lvl];

          var tint = document.createElement("DIV");
          tint.className = "tint"
          square.appendChild(tint)
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
          // get the id of the piece located at this coordinate
          var piece = this.getPiece(row, col, lvl);
          var pieceId = String.fromCharCode(piece.getId());
          if (pieceId === " ") continue;

          // obtain the image name based off the piece id
          var imageName =
            "../img/" + pieceId + (piece.getColor() == 1 ? "l" : "d") + ".svg";
          var image = document.createElement("img");

          image.src = imageName;
          image.className = "chessImg";

          // add onclick event listener to each piece
          image.addEventListener("click", (event) =>
            this.displayLegalMoves(event, this)
          );
          // add the piece image as a child of the current div
          var square = this.getSquareDiv(row, col, lvl);
          square.appendChild(image);
        }
      }
    }
  }

  highLightSquare(square) {
    square.childNodes.forEach((elem) => {
      if (elem.className === "tint") {
        elem.style.display = "block";
      }
    })
  }

  removeAllHighLight() {
    var allTints = document.getElementsByClassName("tint");

    Array.prototype.forEach.call(allTints, (elem) => {
      elem.style.display = "none";
    })
  }

  // var self = this;
  displayLegalMoves(event, board) {
    this.removeAllHighLight();
    // obtain the coordinate of the image from the parent div and convert to int
    const [row, col, lvl] = event.target.parentElement.dataset["coordinate"]
      .split(",")
      .map((x) => parseInt(x));

    console.log("bruh", row, col, lvl);
    var piece = board.getPiece(row, col, lvl);
    var moves = piece.getMoves(this.cppBoard);

    for (var i = 0; i < moves.size(); i++) {
      var m = moves.get(i);
      var nRow = row + m.row;
      var nCol = col + m.col;
      var nLvl = lvl + m.lvl;
      
      // this.getSquareDiv(nRow, nCol, nLvl).childNodes()
      this.highLightSquare(this.getSquareDiv(nRow, nCol, nLvl));
      console.log(this.getSquareDiv(nRow, nCol, nLvl))
      // console.log(moves.get(i));
    }
  }

  // updatePiecePosition(event) {
  //   console.log(event.target)
  // }
}
