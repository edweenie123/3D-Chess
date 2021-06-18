class Moves {
    constructor() {
        this.movesDiv = document.getElementById("movesPanel");
        this.table = document.getElementById("movesBox");
    }

    addMove(pieceId, info, color, curRow, curCol, curLvl, newRow, newCol, newLvl) {
        var imgFileName = String(pieceId.toLowerCase()) + ".svg";
        var movement =
            '<img src="img/' +
            imgFileName +
            '" width="20px">' +
            String.fromCharCode("A".charCodeAt(0) + curLvl) +
            String.fromCharCode("a".charCodeAt(0) + curCol) +
            (1 + curRow) +
            (info.capturedPiece ? "x" : " ") +
            String.fromCharCode("A".charCodeAt(0) + newLvl) +
            String.fromCharCode("a".charCodeAt(0) + newCol) +
            (1 + newRow);
        // Add this move to the table
        if (color == 1) {
            var row = this.table.insertRow();
            var cellLeft = row.insertCell();
            cellLeft.innerHTML = movement;
        } else {
            var lastRow = this.table.rows[this.table.rows.length - 1];
            var cellRight = lastRow.insertCell();
            cellRight.innerHTML = movement;
        }
    }

    appendSpecial(checkmate, check, promote, color, promoteId) {
        // Get the most recently filled out move
        if (color == 1) {
            promoteId = promoteId.toUpperCase();
        } else {
            promoteId = promoteId.toLowerCase();
        }
        var lastRow = this.table.rows[this.table.rows.length - 1];
        var lastCell = lastRow.cells[lastRow.cells.length - 1];
        if (promote == true) {
            lastCell.innerHTML += "=" + promoteId;
        }
        if (checkmate == true) {
            lastCell.innerHTML += "#";
        } else if (check == true) {
            lastCell.innerHTML += "+";
        }
    }
}
