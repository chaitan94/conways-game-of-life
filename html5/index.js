var gridsize = 128;
var screensize = 512;
var cellsize = screensize/gridsize;
var gol = document.getElementById('gol');
var color1 = "#FFF";
var color2 = "#444";

var frag = document.createDocumentFragment();
for (var i = 0; i < gridsize; i++) {
	var row = document.createElement('div');
	row.classList.add('row');
	for (var j = 0; j < gridsize; j++) {
		var cell = document.createElement('div');
		cell.classList.add('cell');
		row.appendChild(cell);
	};
	frag.appendChild(row);
};
gol.appendChild(frag);

var Board = function(n){
	this.n = n;
	this.board = [];
	for (var i = 0; i < this.n; i++) {
		var t = [];
		for (var j = 0; j < this.n; j++)
			t.push(0.3 > Math.random());
		this.board.push(t);
	};
	this.getCell = function(i, j){
		if (i < 0 || i >= this.n) return false;
		if (j < 0 || j >= this.n) return false;
		return this.board[i][j];
	};
};
var front = new Board(gridsize);
var back = new Board(gridsize);

var gameOfLife = function(i, j){
	var s = 0;
	s += front.getCell(i-1, j-1);
	s += front.getCell(i, j-1);
	s += front.getCell(i+1, j-1);
	s += front.getCell(i-1, j+1);
	s += front.getCell(i, j+1);
	s += front.getCell(i+1, j+1);
	s += front.getCell(i-1, j);
	s += front.getCell(i+1, j);
	if (s > 3) return false;
	else if (s == 3) return true;
	else if (s < 2) return false;
	return front.getCell(i, j); 
};
var update = function(){
	for (var i = 0; i < front.n; i++) {
		for (var j = 0; j < front.n; j++){
			back.board[i][j] = gameOfLife(i, j);
		};
	};
};
var render = function(){
	for (var i = 0; i < front.n; i++) {
		for (var j = 0; j < front.n; j++){
			var t = front.board[i][j];
			if (t != back.board[i][j]){
				front.board[i][j] = back.board[i][j];
				if(t) gol.children[i].children[j].style.background = color1;
				else gol.children[i].children[j].style.background = color2;
			};
		};
	};
};

var game = function(){
	update();
	render();
	requestAnimationFrame(game);
}
game();
