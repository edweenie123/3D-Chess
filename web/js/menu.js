class Menu {
  constructor(board) {
    this.board = board;
    this.colour = (document.getElementById("sel5").checked) ? -1 : 1; // Assume player wants to play as white
    this.gameMode;
    this.menuDiv = document.getElementById("selec");
    document.getElementById("playerToggle").onclick = () => {this.toggle()};
    document.getElementById("submitButton").onclick = () => {this.submit()};
    this.init();
  }

  submit() {
    if (document.getElementById("sel1").checked == true) {
      this.gameMode = document.getElementById("sel1").value;
    } else if (document.getElementById("sel2").checked == true) {
      this.gameMode = document.getElementById("sel2").value;
    } else if (document.getElementById("sel3").checked == true) {
      this.gameMode = document.getElementById("sel3").value;
    } else if (document.getElementById("sel4").checked == true) {
      this.gameMode = document.getElementById("sel4").value;
    }

    console.log(this.gameMode);
    console.log(this.colour);


    board.cpuDifficulty = this.gameMode;
    board.opponent = new Module.Solver(Number(board.cpuDifficulty));

    this.menuDiv.style.display = "none";
    document.getElementById("board").style.display = "block";

    if (this.gameMode != -1) {
      if (this.colour==1) this.board.changeClickability(true, false);
      else {
        this.board.changeClickability(false, false);
        setTimeout(() => this.board.getNextComputerMove(), this.board.compDelay);
      } 
    } else {
      this.board.changeClickability(true, false);
    }

    console.log(board.turn);
    console.log(board.cpuDifficulty);
    
    var gameStart = new Audio("../sfx/game-start.wav");
    gameStart.play();
  }

  toggle() {
    this.colour = this.colour === 1 ? -1 : 1;
    this.init();
  }

  init() {
    document.getElementById("chosenColour").innerHTML = `Play as <b>${((this.colour === 1) ? "WHITE" : "BLACK")}</b>`;
  }
}

// var gameMode = "NULL";
// var colour = 1;

// if (document.getElementById("sel5").checked == true) {
//   colour = -1;
// }

// var chosenColour = "WHITE&nbsp;&nbsp;&nbsp;&nbsp;";
// if (colour == -1) {
//   chosenColour = "BLACK&nbsp;&nbsp;&nbsp;&nbsp;";
// }
