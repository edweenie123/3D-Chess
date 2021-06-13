/*
To-do:
    make board size dynamic (based of screen size)?
    rerender on window resize
*/
    
class Board {
  constructor(col, diff) {
    this.boardDiv = document.getElementById("board");
    this.size = 5;
    this.squareSize = 67; // size of each square on board in px
    this.cppBoard = new Module.Board();
    this.turn = -1; // 1 for white, -1 for black
    this.cpuDifficulty = 2; // -1 for P vs P, [0-2] for CPU difficulty
    this.compActive = false;
    // this.opponent = new Module.Solver(this.cpuDifficulty);
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
            (pieceColor === this.turn) ? "auto" : "none";
        }
      }
    }
    if(this.cpuDifficulty != -1 && this.compActive) this.getNextComputerMove();
    if (this.cppBoard != -1) this.compActive = true;
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

          boardLvl.appendChild(square);

          // add event listener to remove legal tint
          var removeLegal = document.createElement("DIV");
          removeLegal.className = "removeLegal";
          removeLegal.addEventListener("click", (event) => {
            this.unselectPiece(event);
          });

          square.appendChild(removeLegal);
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
          var cppPiece = this.getPiece(row, col, lvl);
          if (!cppPiece.isAlive) continue;
          var pieceId = String.fromCharCode(cppPiece.getId());
          var pieceColor = cppPiece.getColor() == 1 ? "l" : "d";
          // obtain the image name based off the piece id
          var pieceName = pieceId + pieceColor;
          var piece = this.createChessPiece(pieceName);

          // add the piece image as a child of the current div
          var square = this.getSquareDiv(row, col, lvl);
          square.appendChild(piece);
        }
      }
    }
  }

  createTint(row, col, lvl, className) {
    var tint = document.createElement("DIV");
    tint.className = className;

    if (className === "legalTint") {
      tint.addEventListener("click", (event) =>
        this.updatePiecePosition(event)
      );
    }

    if (className === "pieceSelectTint") {
      tint.addEventListener("click", (event) => this.unselectPiece(event))
    }

    // add the tint to the appropriate square
    var square = this.getSquareDiv(row, col, lvl);
    this.getSquareDiv(row, col, lvl).insertBefore(tint, square.firstChild);

    return tint;
  }

  unselectPiece(event) {
    console.log("undo")
    this.removeTintType("legalTint");

    const [row, col, lvl] = event.target.parentElement.dataset["coordinate"]
      .split(",")
      .map((x) => parseInt(x));

    // this.getSquareImage(row, col, lvl).style.pointerEvents = "auto";

    this.removeTintType("pieceSelectTint");
    // event.target.remove();
  }

  createChessImage(id) {
    var img = document.createElement("img");
    img.src = "../img/" + id + ".svg";
    img.dataset["id"] = id;
    return img;
  }

  createChessPiece(id) {
    var piece = this.createChessImage(id);

    // add onclick event listener to each piece with IIFE (immediate invoked function expression)
    ((id) => {
      piece.addEventListener("click", (event) =>
        this.displayLegalMoves(event, id)
      );
    })(id);

    piece.className = "chessImg";
    return piece;
  }

  removeTintType(className) {
    var allTints = document.getElementsByClassName(className);

    while (allTints[0]) {
      allTints[0].remove();
    }
  }

  // activates when user clicks on a piece
  displayLegalMoves(event, pieceName) {
    this.removeTintType("pieceSelectTint")
    this.removeTintType("legalTint");
    
    // obtain the coordinate of the image from the parent div and convert to int
    const [row, col, lvl] = event.target.parentElement.dataset["coordinate"]
      .split(",")
      .map((x) => parseInt(x));

    var selectedTint = this.createTint(row, col, lvl, "pieceSelectTint");
    selectedTint.dataset["coordinate"] = [row, col, lvl];
    // event.target.style.pointerEvents = "none";

    
    var piece = this.getPiece(row, col, lvl);
    var moves = piece.getMoves(this.cppBoard, true);

    for (var i = 0; i < moves.size(); i++) {
      var m = moves.get(i);
      var nRow = row + m.row;
      var nCol = col + m.col;
      var nLvl = lvl + m.lvl;

      // add the coordinate of the peace and the move delta to each legalTint div
      var legalTint = this.createTint(nRow, nCol, nLvl, "legalTint");
      //   console.log("created at ", nRow, nCol, nLvl);
      legalTint.dataset["pieceLoc"] = [row, col, lvl];
      legalTint.dataset["move"] = [m.row, m.col, m.lvl];
      legalTint.dataset["pieceName"] = pieceName;
    }
  }

  // determines if a piece can promote given its name and row
  canPromote(row, lvl, pieceName) {
    if (pieceName == "pl") return row === 4 && lvl === 4;
    if (pieceName == "pd") return row === 0 && lvl === 0;
    return false;
  }

  // activates when user clicks on highlighted square
  updatePiecePosition(event) {
    var legalTint = event.target;
    var pieceName = legalTint.dataset["pieceName"];
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
    var pieceImage = this.getSquareImage(pRow, pCol, pLvl);

    // delete the prexisting image at the new coordinate if it exists
    var curChecked = false;
    var curCaptured = false;
    if (this.hasImage(nRow, nCol, nLvl)) {
	  curCaptured = true;
      this.getSquareImage(nRow, nCol, nLvl).remove();
    }
    
    // check if this move puts the other player in check
    if (this.cppBoard.isChecked(this.turn * -1)) {
	  curChecked = true;
	}
	
	// Play correct sound based on movement type performed
	if (curChecked) {
		var moveCheck = new Audio("../sfx/move-check.wav");
		moveCheck.play();
	} else if (curCaptured) {
		var capture = new Audio("../sfx/capture.wav");
		capture.play();
	} else {
		var moveSelf = new Audio("../sfx/move-self.wav");
		moveSelf.play();
	}
	
    // remove previous tints
    this.removeTintType("legalTint");
    this.removeTintType("lastMoveTint");
    this.removeTintType("pieceSelectTint");

    // add tints to show previous move
    this.createTint(nRow, nCol, nLvl, "lastMoveTint");
    this.createTint(pRow, pCol, pLvl, "lastMoveTint");

    newSquare.appendChild(pieceImage);

    console.log(nRow, nLvl, pieceName);
    if (this.canPromote(nRow, nLvl, pieceName)) {
      this.createPromotionPanel(nRow, nCol, nLvl, pieceName[1]);
    } else {
      this.changeTurn();
    }
  }
  
  getNextComputerMove() {
    // compute and parse next move to play
    var nxTurn = this.opponent.nextMove(this.cppBoard, this.turn);
    // current location
    const pRow = nxTurn.currentLocation.row;
    const pCol = nxTurn.currentLocation.col;
    const pLvl = nxTurn.currentLocation.lvl;
    // change in movement
    const mRow = nxTurn.change.row;
    const mCol = nxTurn.change.col;
    const mLvl = nxTurn.change.lvl;
    
    if(pRow < 0){
      console.log(pRow == -1 ? "Stalemate." : "Checkmate.");
      console.log(`Solver return code: ${pRow}`);
      // Play sound to signal game end
      var gameEnd = new Audio("../sfx/game-end.wav");
      gameEnd.play();
      return;
    }
    // update the cpp board to match the state of the GUI board
    this.cppBoard.updateLocation(
      new Module.Coordinate(pRow, pCol, pLvl),
      new Module.Move(mRow, mCol, mLvl)
    );
    const [nRow, nCol, nLvl] = [pRow + mRow, pCol + mCol, pLvl + mLvl];
    var newSquare = this.getSquareDiv(nRow, nCol, nLvl);
    // var oldSquare = this.getSquareDiv(pRow, pCol, pLvl);
    var pieceImage = this.getSquareImage(pRow, pCol, pLvl);

    // delete the prexisting image at the new coordinate if it exists
    var curChecked = false;
    var curCaptured = false;
    
    if (this.hasImage(nRow, nCol, nLvl)) {
	  curCaptured = true;
      this.getSquareImage(nRow, nCol, nLvl).remove();
	}
	
	// check if this move puts the other player in check
	if (this.cppBoard.isChecked(this.turn)) {
	  curChecked = true;
	}
	
	// Play correct sound based on movement type performed
	if (curChecked) {
		var moveCheck = new Audio("../sfx/move-check.wav");
		moveCheck.play();
	} else if (curCaptured) {
		var capture = new Audio("../sfx/capture.wav");
		capture.play();
	} else {
		var moveOpponent = new Audio("../sfx/move-opponent.wav");
		moveOpponent.play();
	}

    this.removeTintType("lastMoveTint");
    // add highlights to show previous move
    this.createTint(nRow, nCol, nLvl, "lastMoveTint");
    this.createTint(pRow, pCol, pLvl, "lastMoveTint");

    newSquare.appendChild(pieceImage);
    this.turn = this.turn === 1 ? -1 : 1;
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

  // color = l -> white, color = d -> black
  createPromotionPanel(row, col, lvl, color) {
    console.log("yes");

    var panel = document.getElementById("promotePanel");
    var pieceHolder = document.getElementById("pieceHolder");
    panel.style.display = "block";

    // remove all children of pieceHolder
    while (pieceHolder.firstChild) {
      pieceHolder.removeChild(pieceHolder.firstChild);
    }

    //
    var pieces = [
      this.createChessImage("q" + color),
      this.createChessImage("n" + color),
      this.createChessImage("r" + color),
      this.createChessImage("u" + color),
      this.createChessImage("b" + color),
    ];

    pieces.forEach((elem) => {
      pieceHolder.appendChild(elem);
      elem.className = "promoteImg";

      // add event listener to each piece to promote
      elem.addEventListener("click", (event) => {
        this.promote(row, col, lvl, elem.dataset["id"]);
      });
    });
  }

  // replaces a pawn with promoted piece
  promote(row, col, lvl, promoteId) {
    console.log("promote", promoteId);
    var panel = document.getElementById("promotePanel");
    panel.style.display = "none";

    // remove the existing pawn and replace it with the new piece
    this.getSquareImage(row, col, lvl).remove();
    var promotedPiece = this.createChessPiece(promoteId);
    this.getSquareDiv(row, col, lvl).appendChild(promotedPiece);

    // get the cpp pawn and promote it
    var cppPawn = this.getPiece(row, col, lvl);
    var color = promoteId[1] === "l" ? 1 : -1;
    var cppPromotedPiece;

    // create new cppPiece depending on the id of promoted piece
    switch(promoteId[0]) {
      case "q":
        cppPromotedPiece = new Module.Queen(row, col, lvl, color);
        break;
      case "n":
        cppPromotedPiece = new Module.Knight(row, col, lvl, color);
        break;
      case "r":
        cppPromotedPiece = new Module.Rook(row, col, lvl, color);
        break;
      case "u":
        cppPromotedPiece = new Module.Unicorn(row, col, lvl, color);
        break;
      case "b":
        cppPromotedPiece = new Module.Bishop(row, col, lvl, color);
        break;
      default:
        throw "ERROR: promoteId is invalid"
    }

    cppPawn.promote(this.cppBoard, cppPromotedPiece);
    var promote = new Audio("../sfx/promote.wav");
    promote.play();
    this.changeTurn();
  }
}
