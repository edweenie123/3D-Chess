class Menu {
  constructor(board, panel) {
    this.panel = panel;
    this.board = board;
    this.gameMode;
    this.menuDiv = document.getElementById("selec");
    document.getElementById("submitButton").onclick = () => {this.submit()};
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
    
    this.colour = [-1, 1][Math.floor(Math.random() * 2)];
    if(document.getElementById("selWhite").checked){
        this.colour = 1;
    } else if(document.getElementById("selBlack").checked){
        this.colour = -1;
    }

    // flip the board towards black if user selected to be black
    if (this.colour == -1) this.board.flipTowards(-1);
    this.board.animateBoard();

    console.log(this.gameMode);
    console.log(this.colour + " player");


    board.cpuDifficulty = this.gameMode;
    board.opponent = new Module.Solver(Number(board.cpuDifficulty));

    this.menuDiv.style.display = "none";
    document.getElementById("board").style.display = "block";
    this.panel.panelDiv.style.display = "block";
    this.panel.initialize(this.gameMode, this.colour);
    document.getElementById("statusContainer").style.display = "block";
    document.getElementById("movesPanel").style.display = "block";

    if (this.gameMode != -1) {
      if (this.colour==1) {
		  this.board.changeClickability(true, false);
		  this.board.aiColour = -1;
      } else {
		this.board.aiColour = 1;
        this.board.changeClickability(false, false);
        setTimeout(() => this.board.getNextComputerMove(), this.board.compDelay + 3000);
      } 
    } else {
      this.board.changeClickability(true, false);
    }

    console.log(board.turn);
    console.log(board.cpuDifficulty);
    
    var gameStart = new Audio("../sfx/game-start.wav");
    gameStart.play();
  }
}
