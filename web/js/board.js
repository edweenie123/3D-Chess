class Board {
    constructor(panel, moves, bar) {
        this.boardDiv = document.getElementById("board");
        this.size = 5;
        this.squareSize = 6; // size of each square on board in px
        this.cppBoard = new Module.Board();
        this.turn = 1; // 1 for white, -1 for black
        this.aiColor = -1;
        this.gameOver = false;
        this.cpuDifficulty = 2; // -1 for P vs P, [0-2] for CPU difficulty
        this.compDelay = 1000; // amount of milliseconds before genNextComputerMove() is called
        this.panel = panel;
        this.flippedSide = 1; // 1 = flipped towards white, -1 flipped towards black

        this.boardLvlTransformWhite;
        this.boardLvlTransformBlack;

        this.moves = moves;
        this.scoreBar = bar;
    }

    animateBoard() {
        var allBoardLvl = document.getElementsByClassName("boardLvl");
        var allPieces = document.querySelectorAll(".chessImg");
        var boardTime = 0.5;
        var boardInterval = 0.25;
        var pieceTime = 0.7;
        var pieceInterval = 0.03;

        Array.from(allBoardLvl).forEach((elem, ind) => {
            setTimeout(
                () =>
                    (elem.style.animation = `comeFromLeft ${boardTime}s forwards`),
                ind * boardInterval * 1000
            );
        });

        Array.from(allPieces).forEach((elem, ind) => {
            setTimeout(
                () => (elem.style.animation = `fadeIn ${pieceTime}s forwards`),
                (boardInterval * 4 + boardTime + ind * pieceInterval) * 1000 -
                    200
            );
        });

        // remove animation from pieces to avoid repeat animations
        Array.from(allPieces).forEach((elem) => {
            setTimeout(() => {
                elem.style.animation = "";
                elem.style.opacity = 1;
            }, (boardTime + boardInterval * 4 + pieceTime + pieceInterval * 39) * 1000);
        });
    }

    changeClickability(clickWhite, clickBlack) {
        if (this.cpuDifficulty != -1 && this.turn == this.aiColor) {
            if (!this.gameOver)
                document.getElementById("status").innerHTML =
                    "Computer<br>is thinking";
        } else {
            if (!this.gameOver)
                document.getElementById("status").innerHTML =
                    this.turn === 1 ? "White<br>to move" : "Black<br>to move";
        }
        for (var lvl = 0; lvl < this.size; lvl++) {
            for (var row = 0; row < this.size; row++) {
                for (var col = 0; col < this.size; col++) {
                    var piece = this.getPiece(row, col, lvl);
                    if (!piece.getIsAlive()) continue;

                    var pieceColor = piece.getColor();
                    var hitbox = this.getHitbox(row, col, lvl);

                    if (pieceColor == 1)
                        hitbox.style.pointerEvents = clickWhite
                            ? "auto"
                            : "none";
                    if (pieceColor == -1)
                        hitbox.style.pointerEvents = clickBlack
                            ? "auto"
                            : "none";
                }
            }
        }
    }

    changeTurn() {
        this.turn = this.turn === 1 ? -1 : 1;

        // remove the pointer event of all white / black pieces depending on whose turn it is
        if (this.cpuDifficulty == -1) {
            this.changeClickability(this.turn === 1, this.turn === -1);
            this.flipTowards(this.turn);
        } else {
            this.changeClickability(false, false);
        }

        if (this.cpuDifficulty != -1) {
            setTimeout(() => this.getNextComputerMove(), this.compDelay);
        }
    }

    // returns true if a particular coordinate has a chess piece image associated with it
    hasImage(row, col, lvl) {
        var image = Array.from(
            this.getSquareDiv(row, col, lvl).childNodes
        ).find((elem) => elem.classList.contains("chessImg"));
        return image != undefined;
    }

    // returns a the piece object located at a specific coordinate
    getPiece(row, col, lvl) {
        return this.cppBoard.getBoard().get(row).get(col).get(lvl);
    }

    // returns the div located at a specific coordinate
    getSquareDiv(row, col, lvl) {
        return this.boardDiv.childNodes[this.size - 1 - lvl].childNodes[
            (this.size - 1 - row) * this.size + col
        ];
    }

    // returns the chess image located at a specific coordinate
    getSquareImage(row, col, lvl) {
        var square = this.getSquareDiv(row, col, lvl);
        var image = Array.from(square.childNodes).find((elem) =>
            elem.classList.contains("chessImg")
        );
        console.assert(image != undefined, {
            msg: "image not found!",
            cord: [row, col, lvl],
        });

        return image;
    }

    // returns the hitbox located at a specific coordinate
    getHitbox(row, col, lvl) {
        var square = this.getSquareDiv(row, col, lvl);
        var hitbox = Array.from(square.childNodes).find(
            (elem) => elem.className === "pieceHitbox"
        );
        console.assert(hitbox != undefined, {
            msg: "hitbox not found!",
            cord: [row, col, lvl],
        });

        return hitbox;
    }

    // get the image for the king of a certain color (used for the red shadow effect)
    getKingImg(color) {
        var desiredId = "k" + (color === 1 ? "l" : "d");
        for (var lvl = 0; lvl < this.size; lvl++) {
            for (var row = 0; row < this.size; row++) {
                for (var col = 0; col < this.size; col++) {
                    if (!this.hasImage(row, col, lvl)) continue;

                    if (
                        this.getSquareImage(row, col, lvl).dataset.id ===
                        desiredId
                    )
                        return this.getSquareImage(row, col, lvl);
                }
            }
        }

        throw "ERROR: king not found";
    }

    // create a div for each square of the board
    renderBoard() {
        for (var lvl = this.size - 1; lvl >= 0; lvl--) {
            var boardLvl = document.createElement("DIV");
            boardLvl.className = "boardLvl";

            for (var row = 0; row < this.size; row++) {
                for (var col = 0; col < this.size; col++) {
                    var square = document.createElement("DIV");
                    square.className = "square";
                    // set the color of the square to get checkboard pattern
                    square.className +=
                        (lvl + row + col) % 2 ? " lightCol" : " darkCol";
                    square.dataset["coordinate"] = [
                        this.size - 1 - row,
                        col,
                        lvl,
                    ];

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
            square.style.width = this.squareSize + "vh";
            square.style.height = this.squareSize + "vh";
        });

        var allBoardLvl = document.getElementsByClassName("boardLvl");
        Array.from(allBoardLvl).forEach((lvl, index) => {
            let height = this.squareSize * this.size;
            let missing = height * (1 - Math.cos((63 * Math.PI) / 180)) * 0.95;
            lvl.style.width = height + "vh";
            lvl.style.height = height + "vh";
            lvl.style.transform = `translateY(${
                -index * missing
            }vh) rotateX(63deg) skew(336deg)`;
        });
    }

    // flip the board so that it is from the perspective of a certain color
    flipTowards(color) {
        if (this.flippedSide == color) return; // the board is already flipped towards this color

        var allBoardLvl = document.getElementsByClassName("boardLvl");

        Array.from(allBoardLvl).forEach((lvl, index) => {
            let height = this.squareSize * this.size;
            let missing = height * (1 - Math.cos((63 * Math.PI) / 180)) * 0.95;
            lvl.style.width = height + "vh";
            lvl.style.height = height + "vh";
            lvl.style.transform = `translateY(${
                -index * missing
            }vh) rotateX(63deg) skew(336deg)`;
            // turn the board upside-down if flipping towards black
            if (color == -1) lvl.style.transform += " rotateZ(180deg)";

            // change the offset of the drop shadow depending on whose side the board is facing
            if (color == -1)
                lvl.style.boxShadow = "-5px -9px 8px -1px rgb(0 0 0 / 57%)";
            else lvl.style.boxShadow = "5px 9px 8px -1px rgb(0 0 0 / 57%)";
        });

        // add css id of each piece to flip them
        var allPieceImgs = document.querySelectorAll(".chessImg");
        Array.from(allPieceImgs).forEach((pieceImg) => {
            if (color == -1) pieceImg.classList.add("chessImgFlipped");
            else pieceImg.classList.remove("chessImgFlipped");
        });

        this.flippedSide *= -1;
    }

    // create images of each piece to match the state of the board
    renderPieces() {
        for (var lvl = 0; lvl < this.size; lvl++) {
            for (var row = 0; row < this.size; row++) {
                for (var col = 0; col < this.size; col++) {
                    // get the id of the piece located at this coordinate
                    var cppPiece = this.getPiece(row, col, lvl);
                    if (!cppPiece.getIsAlive()) continue;
                    var pieceId = String.fromCharCode(cppPiece.getId());
                    var pieceColor = cppPiece.getColor() == 1 ? "l" : "d";
                    // obtain the image name based off the piece id
                    var pieceName = pieceId + pieceColor;
                    var [piece, pieceHitbox] = this.createChessPiece(pieceName);

                    // add the piece image as a child of the current div
                    var square = this.getSquareDiv(row, col, lvl);
                    square.appendChild(piece);
                    square.appendChild(pieceHitbox);
                }
            }
        }
    }

    // creates a tint on a square of a specific type
    createTint(row, col, lvl, className) {
        var tint = document.createElement("DIV");
        tint.className = className;

        // add event listeners to the tint depending on its class name
        if (className === "legalTint") {
            tint.addEventListener("click", (event) =>
                this.updatePiecePosition(event)
            );
        }

        if (className === "pieceSelectTint") {
            tint.addEventListener("click", (event) =>
                this.unselectPiece(event)
            );
        }

        // add the tint to the appropriate square
        var square = this.getSquareDiv(row, col, lvl);
        this.getSquareDiv(row, col, lvl).insertBefore(tint, square.firstChild);

        return tint;
    }

    // gets called when the user unselects a piece to move
    unselectPiece(event) {
        this.removeTintType("legalTint");

        const [row, col, lvl] = event.target.parentElement.dataset["coordinate"]
            .split(",")
            .map((x) => parseInt(x));

        this.removeTintType("pieceSelectTint");
    }

    createChessImage(id) {
        var img = document.createElement("img");
        img.src = "../img/" + id + ".svg";
        img.dataset["id"] = id;
        return img;
    }

    createChessPiece(id) {
        var piece = this.createChessImage(id);
        var pieceHitBox = document.createElement("DIV");

        // add onclick event listener to each piece's hitbox with IIFE (immediate invoked function expression)
        ((id) => {
            pieceHitBox.addEventListener("click", (event) =>
                this.displayLegalMoves(event, id)
            );
        })(id);

        pieceHitBox.className = "pieceHitbox";
        piece.className = "chessImg";
        return [piece, pieceHitBox];
    }

    movePiece(pRow, pCol, pLvl, nRow, nCol, nLvl) {
        if (this.hasImage(nRow, nCol, nLvl)) {
            var prevImage = this.getSquareImage(nRow, nCol, nLvl);

            // add the captured piece the panel
            this.panel.addCapturedPiece(prevImage.dataset.id);
            // delete the prexisting image at the new coordinate if it exists
            this.getSquareImage(nRow, nCol, nLvl).remove();
            this.getHitbox(nRow, nCol, nLvl).remove();
        }

        var pieceImage = this.getSquareImage(pRow, pCol, pLvl);
        var pieceHitbox = this.getHitbox(pRow, pCol, pLvl);

        var newSquare = this.getSquareDiv(nRow, nCol, nLvl);
        newSquare.appendChild(pieceImage);
        newSquare.appendChild(pieceHitbox);
    }

    removeTintType(className) {
        var allTints = document.getElementsByClassName(className);

        while (allTints[0]) {
            allTints[0].remove();
        }
    }

    // activates when user clicks on a piece
    displayLegalMoves(event, pieceName) {
        this.removeTintType("pieceSelectTint");
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

    // get information about the move that was just made
    getMoveInfo(nRow, nCol, nLvl, pieceName) {
        var oppColor = -this.turn;
        var info = {
            enemyMated: this.cppBoard.isCheckmated(oppColor),
            enemyChecked: this.cppBoard.isChecked(oppColor),
            isStalemate: this.cppBoard.isStalemated(oppColor),
            capturedPiece: this.hasImage(nRow, nCol, nLvl),
            isPromotion: this.canPromote(nRow, nLvl, pieceName),
        };

        // print if checkmate or statemate happens
        if (info.enemyMated || info.isStalemate) {
            document.getElementById("status").innerHTML =
                this.cppBoard.getGameState(oppColor);
            this.gameOver = true;
        }

        return info;
    }

    handleCheckShadow(moveInfo) {
        var friendlyKing = this.getKingImg(this.turn);
        var enemyKing = this.getKingImg(this.turn * -1);

        // remove the check effect from the friendly king
        friendlyKing.id = "";

        // add red shadow if enemy king is checked
        if (moveInfo.enemyChecked) enemyKing.id = "checked";
    }

    handleSfx(moveInfo) {
        var sound;
        // Play correct sound based on movement type performed
        if (moveInfo.enemyMated || moveInfo.isStalemate)
            sound = new Audio("../sfx/game-end.wav");
        else if (moveInfo.enemyChecked)
            sound = new Audio("../sfx/move-check.wav");
        else if (moveInfo.capturedPiece)
            sound = new Audio("../sfx/capture.wav");
        // normal move sound effect
        else sound = new Audio("../sfx/move-self.wav");

        sound.play();
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

        var moveInfo = this.getMoveInfo(nRow, nCol, nLvl, pieceName);
        this.handleCheckShadow(moveInfo);
        this.handleSfx(moveInfo);

        // remove previous tints
        this.removeTintType("legalTint");
        this.removeTintType("lastMoveTint");
        this.removeTintType("pieceSelectTint");

        // add tints to show previous move
        this.createTint(nRow, nCol, nLvl, "lastMoveTint");
        this.createTint(pRow, pCol, pLvl, "lastMoveTint");

        // move the piece to its new square
        this.movePiece(pRow, pCol, pLvl, nRow, nCol, nLvl);

        // record the move
        this.moves.addMove(
            pieceName,
            moveInfo,
            this.turn,
            pRow,
            pCol,
            pLvl,
            nRow,
            nCol,
            nLvl
        );

        // update board's evaluation score
        this.scoreBar.update(this.opponent.evaluate(this.cppBoard));

        if (moveInfo.isPromotion) {
            this.createPromotionPanel(nRow, nCol, nLvl, pieceName[1]);
        } else {
            if (moveInfo.enemyMated) {
                this.moves.appendSpecial(true, false, false, this.turn, "");
            } else if (moveInfo.enemyChecked) {
                this.moves.appendSpecial(false, true, false, this.turn, "");
            }
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

        // Do not continue updating the board if the game has already ended
        if (pRow < 0) {
            return;
        }

        // update the cpp board to match the state of the GUI board
        this.cppBoard.updateLocation(
            new Module.Coordinate(pRow, pCol, pLvl),
            new Module.Move(mRow, mCol, mLvl)
        );
        const [nRow, nCol, nLvl] = [pRow + mRow, pCol + mCol, pLvl + mLvl];

        var cppPiece = this.getPiece(nRow, nCol, nLvl);
        var pieceName =
            String.fromCharCode(cppPiece.getId()) +
            (cppPiece.getColor() == 1 ? "l" : "d");

        var moveInfo = this.getMoveInfo(nRow, nCol, nLvl, pieceName);

        this.handleSfx(moveInfo);
        this.handleCheckShadow(moveInfo);

        this.removeTintType("lastMoveTint");
        // add highlights to show previous move
        this.createTint(nRow, nCol, nLvl, "lastMoveTint");
        this.createTint(pRow, pCol, pLvl, "lastMoveTint");

        this.movePiece(pRow, pCol, pLvl, nRow, nCol, nLvl);

        // record the move
        this.moves.addMove(
            pieceName,
            moveInfo,
            this.turn,
            pRow,
            pCol,
            pLvl,
            nRow,
            nCol,
            nLvl
        );

        // update board's evaluation score
        this.scoreBar.update(this.opponent.evaluate(this.cppBoard));

        if (this.canPromote(nRow, nLvl, pieceName)) {
            // default to the best piece
            this.promote(nRow, nCol, nLvl, "q" + pieceName[1]);
        } else {
            if (moveInfo.enemyMated) {
                this.moves.appendSpecial(true, false, false, this.turn, "");
            } else if (moveInfo.enemyChecked) {
                this.moves.appendSpecial(false, true, false, this.turn, "");
            }
        }
        this.turn = this.turn === 1 ? -1 : 1;
        this.changeClickability(this.turn == 1, this.turn == -1);
    }

    // color = l -> white, color = d -> black
    createPromotionPanel(row, col, lvl, color) {
        var panel = document.getElementById("promotePanel");
        var pieceHolder = document.getElementById("pieceHolder");
        panel.style.display = "block";

        // remove all children of pieceHolder
        while (pieceHolder.firstChild) {
            pieceHolder.removeChild(pieceHolder.firstChild);
        }

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
        var panel = document.getElementById("promotePanel");
        panel.style.display = "none";

        // remove the existing pawn and replace it with the new piece
        this.getSquareImage(row, col, lvl).remove();
        this.getHitbox(row, col, lvl).remove();
        var [promotedPiece, promotedPieceHitbox] =
            this.createChessPiece(promoteId);
        promotedPiece.style.opacity = 1;
        this.getSquareDiv(row, col, lvl).appendChild(promotedPiece);
        this.getSquareDiv(row, col, lvl).appendChild(promotedPieceHitbox);
        if (this.flippedSide == -1)
            promotedPiece.classList.add("chessImgFlipped"); // make sure the promoted piece is not updown

        // get the cpp pawn and promote it
        var cppPawn = this.getPiece(row, col, lvl);
        var color = promoteId[1] === "l" ? 1 : -1;
        var cppPromotedPiece;

        // create new cppPiece depending on the id of promoted piece
        switch (promoteId[0]) {
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
                throw "ERROR: promoteId is invalid";
        }
        cppPawn.promote(this.cppBoard, cppPromotedPiece, true);
        var promote = new Audio("../sfx/promote.wav");
        promote.play();

        var moveInfo = this.getMoveInfo(row, col, lvl, promoteId[0]);
        this.handleCheckShadow(moveInfo);
        this.handleSfx(moveInfo);

        // update moves list
        if (moveInfo.enemyMated) {
            this.moves.appendSpecial(
                true,
                false,
                true,
                this.turn,
                promoteId[0]
            );
        } else if (moveInfo.enemyChecked) {
            this.moves.appendSpecial(
                false,
                true,
                true,
                this.turn,
                promoteId[0]
            );
        } else {
            this.moves.appendSpecial(
                false,
                false,
                true,
                this.turn,
                promoteId[0]
            );
        }

        // update board's evaluation score
        this.scoreBar.update(this.opponent.evaluate(this.cppBoard));

        if (this.cpuDifficulty != -1 && this.turn == this.aiColor) {
            return;
        } else this.changeTurn();
    }
}
