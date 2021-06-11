/*
To-do:
    make board size dynamic (based of screen size)?
    rerender on window resize
*/

class Board {
  constructor() {
    this.boardDiv = document.getElementById("board");
    this.size = 5;
    this.squareSize = 67; // size of each square on board in px
    this.cppBoard = new Module.Board();
    this.turn = -1; // 1 for white, -1 for black
  }

  changeTurn() {
    this.turn = this.turn === 1 ? -1 : 1;

    // remove the pointer event of all white / black pieces depending on whose turn it is
    for (var lvl = 0; lvl < this.size; lvl++) {
      for (var row = 0; row < this.size; row++) {
        for (var col = 0; col < this.size; col++) {
          var piece = this.getPiece(row, col, lvl);
          if (!piece.isAlive) continue;

          var pieceColor = piece.getColor();
          var image = this.getSquareImage(row, col, lvl);
          image.style.pointerEvents =
            pieceColor === this.turn ? "auto" : "none";
        }
      }
    }
  }

  // returns true if a particular coordinate has a chess piece image associated with it
  hasImage(row, col, lvl) {
    var image = Array.from(this.getSquareDiv(row, col, lvl).childNodes).find(
      (elem) => elem.className == "chessImg"
    );
    return image != undefined;
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

  getSquareImage(row, col, lvl) {
    var square = this.getSquareDiv(row, col, lvl);
    var image = Array.from(square.childNodes).find(
      (elem) => elem.className === "chessImg"
    );
    console.assert(image != undefined, {
      msg: "image not found!",
      cord: [row, col, lvl],
    });

    return image;
  }

  getTintDiv(row, col, lvl, className) {
    var square = this.getSquareDiv(row, col, lvl);
    var tint = Array.from(square.childNodes).find(
      (elem) => elem.className === className
    );
    console.assert(tint != undefined, "tint div not found!");

    return tint;
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
          
          // add legal tint div to the square
          var legalTint = document.createElement("DIV");
          legalTint.className = "legalTint";
          legalTint.addEventListener("click", (event) =>
            this.updatePiecePosition(event)
          );
          square.appendChild(legalTint);

          // add last move tint div to the square
          var lastMoveTint = document.createElement("DIV");
          lastMoveTint.className = "lastMoveTint";
          square.appendChild(lastMoveTint);

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
          if (!piece.isAlive) continue;
          var pieceId = String.fromCharCode(piece.getId());

          // obtain the image name based off the piece id
          var imageName =
            "../img/" + pieceId + (piece.getColor() == 1 ? "l" : "d") + ".svg";
          var image = document.createElement("img");

          image.src = imageName;
          image.className = "chessImg";

          // add onclick event listener to each piece
          image.addEventListener("click", (event) =>
            this.displayLegalMoves(event)
          );
          // add the piece image as a child of the current div
          var square = this.getSquareDiv(row, col, lvl);
          square.appendChild(image);
        }
      }
    }
  }

  highLightSquare(row, col, lvl, className) {
    var tint = this.getTintDiv(row, col, lvl, className);
    tint.style.display = "block";
  }

  removeHighLights(className) {
    var allTints = document.getElementsByClassName(className);

    Array.prototype.forEach.call(allTints, (elem) => {
      elem.style.display = "none";
    });
  }

  // activates when user clicks on a piece
  displayLegalMoves(event) {
    this.removeHighLights("legalTint");
    // obtain the coordinate of the image from the parent div and convert to int
    const [row, col, lvl] = event.target.parentElement.dataset["coordinate"]
      .split(",")
      .map((x) => parseInt(x));

    var piece = this.getPiece(row, col, lvl);
    var moves = piece.getMoves(this.cppBoard, true);

    for (var i = 0; i < moves.size(); i++) {
      var m = moves.get(i);
      var nRow = row + m.row;
      var nCol = col + m.col;
      var nLvl = lvl + m.lvl;

      this.highLightSquare(nRow, nCol, nLvl, "legalTint");
      // add the coordinate of the peace and the move delta to each legalTint div
      var legalTint = this.getTintDiv(nRow, nCol, nLvl, "legalTint");
      legalTint.dataset["pieceLoc"] = [row, col, lvl];
      legalTint.dataset["move"] = [m.row, m.col, m.lvl];
    }
  }

  // activates when user clicks on highlighted square
  updatePiecePosition(event) {
    this.removeHighLights("legalTint");
    this.removeHighLights("lastMoveTint");
    var legalTint = event.target;

    // get the piece and move delta information from the legalTint div
    const [pRow, pCol, pLvl] = legalTint.dataset["pieceLoc"]
      .split(",")
      .map((x) => parseInt(x));

    const [mRow, mCol, mLvl] = legalTint.dataset["move"]
      .split(",")
      .map((x) => parseInt(x));

    // update the cpp board to match the state of the GUI board
    this.cppBoard.updateLocation(
      new Module.Coordinate(pRow, pCol, pLvl),
      new Module.Move(mRow, mCol, mLvl)
    );

    const [nRow, nCol, nLvl] = [pRow + mRow, pCol + mCol, pLvl + mLvl];
    var newSquare = this.getSquareDiv(nRow, nCol, nLvl);
    var oldSquare = this.getSquareDiv(pRow, pCol, pLvl);
    var pieceImage = this.getSquareImage(pRow, pCol, pLvl);

    // delete the prexisting image at the new coordinate if it exists
    if (this.hasImage(nRow, nCol, nLvl))
      this.getSquareImage(nRow, nCol, nLvl).remove();

    // add highlights to show previous move
    this.highLightSquare(nRow, nCol, nLvl, "lastMoveTint");
    this.highLightSquare(pRow, pCol, pLvl, "lastMoveTint");

    newSquare.appendChild(pieceImage);
    this.changeTurn();
  }
}
