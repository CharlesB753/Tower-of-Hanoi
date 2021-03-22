//Charles-Olivier Belisle
//Comp 206 Game script
//#include

//startgame();
alert("Welcome to Tower of Hanoi! Our game has a twist! be sure to complete the game in the exact minimum number of moves, or the Kraken will slowly eat you pieces!");
var poleA;
var poleB;
var poleC;
var bottomPiece;
var heightOfStackOne = 105;
var heightOfStackTwo = 185;
var heightOfStackThree = 185;
var moves = ["1", "2", "1", "3", "1", "2", "1", "4", "1", "2", "1", "3", "1", "2", "1"];
var counter = 0;

function startGame() {
	//the game piece
	bottomPiece = new component(650, 25, "#2F4F4F", 25, 185);
	//the three poles
	poleA = new component(10, 125, "#B8860B", 140, 60);
	poleB = new component(10, 125, "#B8860B", 365, 60);
	poleC = new component(10, 125, "#BB860B", 590, 60);
	//the bars
	bar1 = new bar(30, 20, "#00FF00", 130, 105);
	bar2 = new bar(50, 20, "#32CD32", 120, 125);
	bar3 = new bar(70, 20, "#FFFF00", 110, 145);
	bar4 = new bar(90, 20, "#FFA500", 100, 165);
	myGameArea.start();	
}

var myGameArea = {

	canvas : document.getElementById("TowerOfHanoi"),
	start : function() {
		this.canvas.width = 700; 
		this.canvas.height = 300;
		this.context = this.canvas.getContext("2d");
		this.interval = setInterval(updateGameArea, 100);
	},

	clear : function(){
		this.context.clearRect(0,0, this.canvas.width, this.canvas.height);
	}
}

function updateGameArea() {
//	alert("hey!");
	myGameArea.clear();
	bar1.newPos();
	bar2.newPos();
	bar3.newPos();
	bar4.newPos();
	bottomPiece.create();
	poleA.create();
	poleB.create();
	poleC.create();
	bar1.update();
	bar2.update();
	bar3.update();
	bar4.update();
	if(counter == 15){
		alert("You have won! We will now redirect you to the room. You can enter your winnings there");
		window.location.href ="room.html";
	}
}

function bar(width, height, color, xCD, yCD){
	this.width = width;
	this.height = height;
	this.xCD = xCD;
	this.yCD = yCD;
	this.newPositionX = 0;
	this.newPositionY = 0;
	this.update = function() {
		this.newPositionX = 0;
		this.newPositionY = 0;
		ctx = myGameArea.context;
		ctx.fillStyle = color;
		ctx.fillRect(this.xCD, this.yCD, this.width, this.height);
	};
	this.newPos = function() {
		this.xCD += this.newPositionX;
		this.yCD += this.newPositionY;	
	};
}


function component(width, height, color, xCD, yCD){
	this.width = width;
	this.height = height;
	this.xCD = xCD;
	this.yCD = yCD;
	this.create = function() {
		ctx = myGameArea.context;
		ctx.fillStyle = color;
		ctx.fillRect(this.xCD, this.yCD, this.width, this.height);
	};
}

function buttonOne(){
	var x = moves[counter];
	counter += 1;
	var z = (345 - heightOfStackTwo) / 20; //this number is the number of bars on the stack
	var s = (345 - heightOfStackOne) / 20;
	var r = 20 * (-z + s - 1);
	
	if(x == 1){
		bar1.newPositionX = 225;
		bar1.newPositionY = r;
		heightOfStackOne += 20;
		heightOfStackTwo -= 20;
	}
	
	if(x == 2){
		bar2.newPositionX = 225;
		bar2.newPositionY = r;
		heightOfStackOne += 20;
		heightOfStackTwo -= 20;
	}
	
	if(x == 3){
		bar3.newPositionX = 225;
		bar3.newPositionY = r;
		heightOfStackOne += 20;
		heightOfStackTwo -= 20;
	}
	
	if(x == 4){
		bar4.newPositionX = 225;
		bar4.newPositionY = r;
		heightOfStackOne += 20;
		heightOfStackTwo -= 20;
	}
}

function buttonTwo(){
	var x = moves[counter]; //take from Mat's program
	counter+=1;
	var z = (345 - heightOfStackThree) / 20;//this number is the number of bars on the stack
	var s = (345 - heightOfStackOne) / 20;
	var r = 20 * (-z + s - 1);
	
	if(x == 1){
		bar1.newPositionX = 450;
		bar1.newPositionY = r;
		heightOfStackOne += 20;
		heightOfStackThree -= 20;
	}
	
	if(x == 2){
		bar2.newPositionX = 450;
		bar2.newPositionY = r;
		heightOfStackOne += 20;
		heightOfStackThree -= 20;
	}
	
	if(x == 3){
		bar3.newPositionX = 450;
		bar3.newPositionY = r;
		heightOfStackOne += 20;
		heightOfStackThree -= 20;
	}
	
	if(x == 4){
		bar4.newPositionX = 450;
		bar4.newPositionY = r;
		heightOfStackOne += 20;
		heightOfStackThree -= 20;
	}
}

function buttonThree(){
	var x = moves[counter];
	counter+=1;
	var z = (345 - heightOfStackOne) / 20;//this number is the number of bars on the stack
	var s = (345 - heightOfStackTwo) / 20;
	var r = 20 * (-z + s - 1);
	if(x == 1){
		bar1.newPositionX = -225;
		bar1.newPositionY = r;
		heightOfStackTwo += 20;
		heightOfStackOne -= 20;
	}
	
	if(x == 2){
		bar2.newPositionX = -225;
		bar2.newPositionY = r;
		heightOfStackTwo += 20;
		heightOfStackOne -= 20;
	}
	
	if(x == 3){
		bar3.newPositionX = -225;
		bar3.newPositionY = r;
		heightOfStackTwo += 20;
		heightOfStackOne -= 20;
	}
	
	if(x == 4){
		bar4.newPositionX = -225;
		bar4.newPositionY = r;
		heightOfStackTwo += 20;
		heightOfStackOne -= 20;
	}

}


function buttonFour(){
	var x = moves[counter]; //take from Mat's program
	counter+=1;
	var z = (345 - heightOfStackThree) / 20;//this number is the number of bars on the stack
	var s = (345 - heightOfStackTwo) / 20;
	var r = 20 * (-z + s - 1);
	
	if(x == 1){
		bar1.newPositionX = 225;
		bar1.newPositionY = r;
		heightOfStackTwo += 20;
		heightOfStackThree -= 20;
	}
	
	if(x == 2){
		bar2.newPositionX = 225;
		bar2.newPositionY = r;
		heightOfStackTwo += 20;
		heightOfStackThree -= 20;
	}
	
	if(x == 3){
		bar3.newPositionX = 225;
		bar3.newPositionY = r;
		heightOfStackTwo += 20;
		heightOfStackThree -= 20;
	}
	
	if(x == 4){
		bar4.newPositionX = 225;
		bar4.newPositionY = r;
		heightOfStackTwo += 20;
		heightOfStackThree -= 20;
	}

}

function buttonFive(){
	var x = moves[counter]; //take from Mat's program
	counter+= 1;
	var z = (345 - heightOfStackOne) / 20; //this number is the number of bars on the stack
	var s = (345 - heightOfStackThree) / 20;
	var r = 20 * (-z + s - 1);
	
	if(x == 1){
		bar1.newPositionX = -450;
		bar1.newPositionY = r;
		heightOfStackThree += 20;
		heightOfStackOne -= 20;
	}
	
	if(x == 2){
		bar2.newPositionX = -450;
		bar2.newPositionY = r;
		heightOfStackThree += 20;
		heightOfStackOne -= 20;
	}
	
	if(x == 3){
		bar3.newPositionX = -450;
		bar3.newPositionY = r;
		heightOfStackThree += 20;
		heightOfStackOne -= 20;
	}
	
	if(x == 4){
		bar4.newPositionX = -450;
		bar4.newPositionY = r;
		heightOfStackThree += 20;
		heightOfStackOne -= 20;
	}
}

function buttonSix(){
	var x = moves[counter]; //take from Mat's program
	counter+=1;
	var z = (345 - heightOfStackTwo) / 20; //this number is the number of bars on the stack
	var s = (345 - heightOfStackThree) / 20;
	var r = 20 * (-z + s - 1);
	if(x == 1){
		bar1.newPositionX = -225;
		bar1.newPositionY = r;
		heightOfStackThree += 20;
		heightOfStackTwo -= 20;
	}
	
	if(x == 2){
		bar2.newPositionX = -225;
		bar2.newPositionY = r;
		heightOfStackThree += 20;
		heightOfStackTwo -= 20;
	}
	
	if(x == 3){
		bar3.newPositionX = -225;
		bar3.newPositionY = r;
		heightOfStackThree += 20;
		heightOfStackTwo -= 20;
	}
	
	if(x == 4){
		bar4.newPositionX = -225;
		bar4.newPositionY = r;
		heightOfStackThree += 20;
		heightOfStackTwo -= 20;
	}
}	


startGame();
