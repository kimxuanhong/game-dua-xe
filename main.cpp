#include <iostream> 
#include "stdio.h"
#include "conio.h"
#include "stdlib.h"
#include "windows.h"
#include "time.h"
#include <string> 
 
using namespace std; 

// Graphic Lib	
void resizeConsole(int width, int height);
void textcolor(int x);
void gotoxy(int x, int y);
void Clearscreen();

//Global and Static variables
int highScore = 0;
int highMoney = 0;
string userHighScore = "Nobody";


void intMapGame(string mapGame[41][31], bool isEven){	
	for(int y=0; y <= 30; y++){
		for(int x=0; x <= 40; x++){
			if(x == 0 || (x == 20 && (((y % 2) == 0) && isEven)) || x == 40){					
				mapGame[x][y] = "|";				
			} else {
				mapGame[x][y] = " ";
			}
		}
	}
}

void drawMapGame(string mapGame[41][31]){
	for(int y=0; y <= 30; y++){
		string lineOfMap = "";
		for(int x=0; x <= 40; x++){
			lineOfMap = lineOfMap + mapGame[x][y];
		}
		cout << lineOfMap << endl;
	}
}

void setProtagonistToMapGame(int positionX, int positionY, string mapGame[41][31]){
	mapGame[positionX][positionY] = 		"O";
	mapGame[positionX + 1][positionY] = 	"A";
	mapGame[positionX + 2][positionY] = 	"O";
	
	mapGame[positionX][positionY + 1] = 	"H";
	mapGame[positionX + 1][positionY + 1] = "-";
	mapGame[positionX + 2][positionY + 1] = "H";
	
	mapGame[positionX][positionY + 2] = 	"O";
	mapGame[positionX + 1][positionY + 2] = "-";
	mapGame[positionX + 2][positionY + 2] = "O";
}

void setVillainToMapGame(int positionX, int positionY, string mapGame[41][31]){
	mapGame[positionX][positionY] = 		"O";
	mapGame[positionX + 1][positionY] = 	"-";
	mapGame[positionX + 2][positionY] = 	"O";
	
	mapGame[positionX][positionY + 1] = 	"H";
	mapGame[positionX + 1][positionY + 1] = "-";
	mapGame[positionX + 2][positionY + 1] = "H";
	
	mapGame[positionX][positionY + 2] = 	"O";
	mapGame[positionX + 1][positionY + 2] = "V";
	mapGame[positionX + 2][positionY + 2] = "O";
}

void setMoneyToMapGame(int positionX, int positionY, string mapGame[41][31]){
	mapGame[positionX][positionY] = 		"$";
}

void showGameOver(string mapGame[41][31]){
	mapGame[15][15] = "G";
	mapGame[16][15] = "A";
	mapGame[17][15] = "M";
	mapGame[18][15] = "E";
	mapGame[19][15] = " ";
	mapGame[20][15] = "O";
	mapGame[21][15] = "V";
	mapGame[22][15] = "E";
	mapGame[23][15] = "R";
}

void remoteProtagonist(int &positionX, int &positionY){
	if(GetAsyncKeyState(VK_LEFT)){
	    if(positionX > 1){
	        positionX--;
	    }
	}
	if(GetAsyncKeyState(VK_RIGHT)){
	    if(positionX < 37) {
	        positionX++;
	    }
	}
	if(GetAsyncKeyState(VK_UP)){
	    if(positionY > 0){
	        positionY--;
	    }
	}
	if(GetAsyncKeyState(VK_DOWN)){
	    if(positionY < 28){
	        positionY++;
	    }
	}
}

bool validCollision(int positionX, int positionY, int positionXOfVillain, int positionYOfVillain){
	int collisionX = abs(positionX - positionXOfVillain);
    int collisionY = abs(positionY - positionYOfVillain);
    return collisionX < 3 && collisionY < 3;
}

void showScore(int score, int money, int level){
	cout << endl;
	cout << "#########################################" << endl;
	cout << endl;
	cout << "Score: " << score << endl;
	cout << "Level: " << level << endl;
	cout << "Money: " << money << endl;
}

void sumScoreAndMoveVillain(int &positionX, int &positionY, int &score){
    if(positionY > 29) {
    	++score;
    	positionY = rand() % 5; // rand from 0 to 5
     	positionX = 1 + rand() % 37; // rand from 1 to 37	
	} else {
		++positionY;
	}
}

void moveMoney(int &positionX, int &positionY){
    if(positionY >= 30) {
    	positionY = rand() % 5; // rand from 0 to 5
     	positionX = 1 + rand() % 40; // rand from 1 to 37	
	} else {
		++positionY;
	}
}

void sumMoney(int positionX, int positionY, int positionXOfMoney, int positionYOfMoney, int &money){
	if(	(positionX == positionXOfMoney && positionY == positionYOfMoney) ||
		(positionX+1 == positionXOfMoney && positionY == positionYOfMoney) ||
		(positionX+2 == positionXOfMoney && positionY == positionYOfMoney)){
			
		money++;
	}
}

void checkLevel(int score, int &level){
	level = score / 10;
}

void checkDelayTime(int &delayTime, int level, int &previousLevel){
	if(level != previousLevel && delayTime > 3){
		delayTime -= 3;
		previousLevel = level;
	}
}

void startGame(){
	string mapGame[41][31];
	int positionX = 19; 			// x min = 1, x max = 37
	int positionY = 28; 			// y min = 0, y max = 28
	
	int positionXOfVillain01 = 1;	// x min = 1, x max = 37
	int positionYOfVillain01 = 0; 	// y min = 0, y max = 28
	int positionXOfVillain02 = 19; 	// x min = 1, x max = 37
	int positionYOfVillain02 = 0; 	// y min = 0, y max = 28
	int positionXOfVillain03 = 37; 	// x min = 1, x max = 37
	int positionYOfVillain03 = 0; 	// y min = 0, y max = 28
	
	int positionXOfMoney01 = 1;		// x min = 1, x max = 40
	int positionYOfMoney01 = 1; 	// y min = 0, y max = 30
	int positionXOfMoney02 = 1; 	// x min = 1, x max = 40
	int positionYOfMoney02 = 5; 	// y min = 0, y max = 30
	int positionXOfMoney03 = 1; 	// x min = 1, x max = 40
	int positionYOfMoney03 = 15; 	// y min = 0, y max = 30
	int positionXOfMoney04 = 1; 	// x min = 1, x max = 40
	int positionYOfMoney04 = 20; 	// y min = 0, y max = 30
	int positionXOfMoney05 = 1; 	// x min = 1, x max = 40
	int positionYOfMoney05 = 27; 	// y min = 0, y max = 30
	
	bool isCollision = false;
	bool isEven = true;
	int score = 0;
	int money = 0;
	int level = 1;
	int previousLevel = 1;
	int delayTime = 50;
	
	
	while(true){
		
		Clearscreen();
		intMapGame(mapGame, isEven);
		isEven = !isEven;
		
		setVillainToMapGame(positionXOfVillain01, positionYOfVillain01, mapGame); 
		setVillainToMapGame(positionXOfVillain02, positionYOfVillain02, mapGame);
		setVillainToMapGame(positionXOfVillain03, positionYOfVillain03, mapGame);
		
		setMoneyToMapGame(positionXOfMoney01, positionYOfMoney01, mapGame);
		setMoneyToMapGame(positionXOfMoney02, positionYOfMoney02, mapGame);
		setMoneyToMapGame(positionXOfMoney03, positionYOfMoney03, mapGame);
		setMoneyToMapGame(positionXOfMoney04, positionYOfMoney04, mapGame);
		setMoneyToMapGame(positionXOfMoney05, positionYOfMoney05, mapGame);
		
		sumScoreAndMoveVillain(positionXOfVillain01, positionYOfVillain01, score);
		sumScoreAndMoveVillain(positionXOfVillain02, positionYOfVillain02, score);
		sumScoreAndMoveVillain(positionXOfVillain03, positionYOfVillain03, score);
				
		moveMoney(positionXOfMoney01, positionYOfMoney01);
		moveMoney( positionXOfMoney02, positionYOfMoney02);
		moveMoney(positionXOfMoney03, positionYOfMoney03);
		moveMoney(positionXOfMoney04, positionYOfMoney04);
		moveMoney(positionXOfMoney05, positionYOfMoney05);
		
		sumMoney(positionX, positionY, positionXOfMoney01, positionYOfMoney01, money);
		sumMoney(positionX, positionY, positionXOfMoney02, positionYOfMoney02, money);
		sumMoney(positionX, positionY, positionXOfMoney03, positionYOfMoney03, money);
		sumMoney(positionX, positionY, positionXOfMoney04, positionYOfMoney04, money);
		sumMoney(positionX, positionY, positionXOfMoney05, positionYOfMoney05, money);
		
		setProtagonistToMapGame(positionX, positionY, mapGame); 
		
		bool isCollisionWithVillain01 = validCollision(positionX, positionY, positionXOfVillain01, positionYOfVillain01);
		bool isCollisionWithVillain02 = validCollision(positionX, positionY, positionXOfVillain02, positionYOfVillain02);
		bool isCollisionWithVillain03 = validCollision(positionX, positionY, positionXOfVillain03, positionYOfVillain03);
		
		if(isCollisionWithVillain01 || isCollisionWithVillain02 || isCollisionWithVillain03){
     		showGameOver(mapGame);
        	isCollision = true;
		}

		drawMapGame(mapGame);
		showScore(score, money, level);
		
		if(isCollision){
			if(score > highScore){
				fflush(stdin);
				cin.clear(); 
				highScore = score;
				highMoney = money;
				cout << "Nhap ten cua ban: "; 
				cin >> userHighScore; 
				cout << "Ten ban la: " << userHighScore << endl; 
			}
			
			bool exit = false;
			do{
				if(GetAsyncKeyState(VK_RETURN)){
					exit = true;
				}
			} while(!exit);
			
			Sleep(1000);
			
			break;
		}
				
		remoteProtagonist(positionX, positionY);
		
		checkLevel(score, level);
		
		checkDelayTime(delayTime, level, previousLevel);
		
		Sleep(delayTime);
	}
}

void showMenu(int row) {
	system("cls");
	string menu[] = {"New Game", "High Score", "Exit Game"};
	for(int index = 0; index < 3; index ++){
		if(index == row){
			cout << "> " << menu[index] << endl;
		} else {
			cout << menu[index] << endl;
		}
	}
}


void selectMenuHandler(int &slectedItem){
	
	showMenu(slectedItem);
	
	while(true){
		if(GetAsyncKeyState(VK_UP)){
			if(slectedItem == 0) {
				slectedItem = 3;
			}
			slectedItem--;
			showMenu(slectedItem);
			Sleep(200);	
		}
		
		if(GetAsyncKeyState(VK_DOWN)){
			if(slectedItem == 2) {
				slectedItem = -1;
			}
			slectedItem++;
			showMenu(slectedItem);
			Sleep(200);	
		}
		
		if(GetAsyncKeyState(VK_RETURN)){
			Sleep(200);
			return;
		}
	}
}

void showHighscore(){
	system("cls");
	cin.clear();
	cout << "Score: " << highScore << endl;
	cout << "Money: " << highMoney << endl;
	cout << "User: " << userHighScore << endl;
	bool exit = false;
	do{
		if(GetAsyncKeyState(VK_RETURN)){
			exit = true;
		}
	} while(!exit);		
	cin.clear();		
	Sleep(1000);
}

int main(){
	
	resizeConsole(370, 650);
	int slectedItem = 0; // selected start game as default
	
	do {
		selectMenuHandler(slectedItem);
		
		if(slectedItem == 0) {
			startGame();
		} else {
			showHighscore();
		}
	} while(slectedItem != 2);
	
    getch();
    return 0;
}

/** 
	Graphic library
*/

void resizeConsole(int width, int height){
	HWND console = GetConsoleWindow();
	RECT r;
	GetWindowRect(console, &r);
	MoveWindow(console, r.left, r.top, width, height, TRUE); 	
}

void textcolor(int x){
	HANDLE mau;
	mau = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleTextAttribute(mau, x);
}

void gotoxy(int x, int y){
	HANDLE hConsoleOutput;
	COORD Cursor_an_Pos = {x-1,y-1};
	hConsoleOutput = GetStdHandle(STD_OUTPUT_HANDLE);
	SetConsoleCursorPosition(hConsoleOutput, Cursor_an_Pos);
}

void Clearscreen(){
	HANDLE hOut;
	COORD Position;
	hOut = GetStdHandle(STD_OUTPUT_HANDLE);
	Position.X=0;
	Position.Y=0;
	SetConsoleCursorPosition(hOut, Position);
}

