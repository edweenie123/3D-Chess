/*
To-do:
    make board size dynamic (based of screen size)?
    rerender on window resize
*/

class Board {
  constructor() {
    this.boardDiv = document.getElementById("board");
    this.size = 5;
    this.squareSize = 60;
    this.cppBoard = new Module.Board();
    this.turn = -1; // 1 for white, -1 for black
  }

  changeTurn() {
    this.turn = (this.turn===1) ? -1 : 1;

    for (var lvl = 0; lvl < this.size; lvl++) {
      for (var row = 0; row < this.size; row++) {
        for (var col = 0; col < this.size; col++) {
          var piece = this.getPiece(row, col, lvl);
          if (!piece.isAlive) continue;
          
          console.log("here", [row, col, lvl])
          var pieceColor = piece.getColor();
          var image = this.getSquareImage(row, col, lvl);
          image.style.pointerEvents = (pieceColor === this.turn) ? "auto" : "none";
        }
      }
    }
  }

  hasImage(row, col, lvl) {
    var image = Array.from(this.getSquareDiv(row, col, lvl).childNodes).find((elem) => elem.className == "chessImg");
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
    console.assert(image != undefined, {msg: "image not found!", cord: [row, col, lvl]});

    return image;
  }

  getHighlightDiv(row, col, lvl) {
    var square = this.getSquareDiv(row, col, lvl);
    var highLight = Array.from(square.childNodes).find(
      (elem) => elem.className === "tint"
    );
    console.assert(highLight != undefined, "highLight div not found!");

    return highLight;
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
          // add tint div to the square
          var tint = document.createElement("DIV");
          tint.className = "tint";
          tint.addEventListener("click", (event) =>
            this.updatePiecePosition(event)
          );

          square.appendChild(tint);
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

  highLightSquare(row, col, lvl) {
    var highLight = this.getHighlightDiv(row, col, lvl);
    // console.log("hightlight ", highLight)
    highLight.style.display = "block";
  }

  removeAllHighLight() {
    var allTints = document.getElementsByClassName("tint");

    Array.prototype.forEach.call(allTints, (elem) => {
      elem.style.display = "none";
    });
  }

  // activates when user clicks on a piece
  displayLegalMoves(event) {
    this.removeAllHighLight();
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

      this.highLightSquare(nRow, nCol, nLvl);

      var highLight = this.getHighlightDiv(nRow, nCol, nLvl);
      highLight.dataset["pieceLoc"] = [row, col, lvl];
      highLight.dataset["move"] = [m.row, m.col, m.lvl];
      // this.getSquareDiv(nRow, nCol, nLvl).childNodes()
      // console.log(this.getSquareDiv(nRow, nCol, nLvl))
      // console.log(moves.get(i));
    }
  }

  // activates when user clicks on highlighted square
  updatePiecePosition(event) {
    this.removeAllHighLight();
    var highLight = event.target;

    const [pRow, pCol, pLvl] = highLight.dataset["pieceLoc"]
      .split(",")
      .map((x) => parseInt(x));

    const [mRow, mCol, mLvl] = highLight.dataset["move"]
      .split(",")
      .map((x) => parseInt(x));

    this.cppBoard.updateLocation(
      new Module.Coordinate(pRow, pCol, pLvl),
      new Module.Move(mRow, mCol, mLvl)
    );

    const [nRow, nCol, nLvl] = [pRow + mRow, pCol + mCol, pLvl + mLvl];
    var newSquare = this.getSquareDiv(nRow, nCol, nLvl);
    var pieceImage = this.getSquareImage(pRow, pCol, pLvl);
    
    // delete the prexisting image at the new coordinate if it exists
    if (this.hasImage(nRow, nCol, nLvl))
      this.getSquareImage(nRow, nCol, nLvl).remove();

    newSquare.appendChild(pieceImage);
    this.changeTurn();
  }
}
