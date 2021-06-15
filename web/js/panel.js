class Panel {
  constructor() {
    this.panelDiv = document.getElementById("panel");
    this.whitePlayer = document.getElementById("whitePlayer");
    this.blackPlayer = document.getElementById("blackPlayer");
    this.pieceOrder = ["p", "n", "r", "u", "b", "q"];
  }

  initialize(gameMode, playerColor) {
    var name1 = "Player";
    var name2 = "";
    switch (gameMode) {
      case "0":
        name2 += "Computer (Easy)";
        break;
      case "1":
        name2 += "Computer (Normal)";
        break;
      case "2":
        name2 += "Computer (Hard)";
        break;
      default:
        name2 += "Player";
        break;
    }

    this.whitePlayer.getElementsByTagName("p")[0].innerHTML =
      playerColor == 1 ? name1 : name2;
    this.blackPlayer.getElementsByTagName("p")[0].innerHTML =
      playerColor != 1 ? name1 : name2;
  }

  makePiece(pieceName) {
    var img = document.createElement("img");
    img.src = "../img/" + pieceName + ".svg";
    img.className = "capturedPiece";
    img.dataset.type = pieceName[0];
    return img;
  }

  // sorts the pieces in capture box based off this.pieceOrder
  sortCaptureBox(captureBox) {
    var pieces = captureBox.children;
    pieces = Array.prototype.slice.call(pieces, 0);

    pieces.sort((a, b) => {
      for (var i = 0; i < this.pieceOrder.length; i++) {
        if (a.dataset.type == this.pieceOrder[i]) return -1;
        if (b.dataset.type == this.pieceOrder[i]) return 1;
      }
	  throw("ERROR: sorting failed")
    });

	captureBox.innerHTML = "";
	var lastType = "";
	for (var i=0;i<pieces.length;i++) {
		// put pieces of the same type closer together (decrease margin)
		if (pieces[i].dataset.type == lastType) 
			pieces[i].style.marginLeft = "-20px";
		else pieces[i].style.margin = "0";

		lastType = pieces[i].dataset.type;	
		captureBox.appendChild(pieces[i]);
	} 
  }

  addCapturedPiece(pieceName) {
    console.log("panel adding ", pieceName);
    // var boxIndex = pieceName[1] == "l" ? 0 : 1;
    var captureBox = (
      pieceName[1] == "l" ? this.blackPlayer : this.whitePlayer
    ).getElementsByClassName("captureBox")[0];
    captureBox.appendChild(this.makePiece(pieceName));
	this.sortCaptureBox(captureBox)
  }
}
