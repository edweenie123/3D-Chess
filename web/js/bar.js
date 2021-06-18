class Bar {
  constructor() {
    this.barBorder = document.getElementById("barBorder");
    this.evalBar = document.getElementById("progressBar");
    this.indicator = document.getElementById("scoreIndicator");
  }

  update(score) {
      let sign = score < 0 ? -1 : 1;
      score = Math.abs(score);
	  this.evalBar.style.width = `${50 + sign * this.normalize(score)}%`;
      this.indicator.innerHTML = `<b>EVAL</b> ${(sign * score / 10.0).toFixed(2)}`;
  }
  
  normalize(score){
    // return a decimal in the range [0, 50]
    return Math.min(50, Math.cbrt(score) * 5);
  }
}
