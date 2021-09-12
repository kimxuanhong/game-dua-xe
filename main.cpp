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
#define LONGITUDE 41
#define LATITUDE 30
#define VEHICLE_LENGTH 3

int AVAILABLE_LONGITUDE =  LONGITUDE - 1;
int AVAILABLE_LATITUDE =  LATITUDE;
int HALF_AVAILABLE_LONGITUDE = AVAILABLE_LONGITUDE / 2;
int MIN_POSITION_X = 1;
int MIN_POSITION_Y = 1;
int MAX_POSITION_X = AVAILABLE_LONGITUDE - VEHICLE_LENGTH;
int MAX_POSITION_Y = AVAILABLE_LATITUDE - VEHICLE_LENGTH;

int highScore = 0;
int highMoney = 0;
string userHighScore = "Nobody";


void intMapGame(string mapGame[LONGITUDE][LATITUDE], bool isEven){	
	for(int y=0; y < LATITUDE; y++){
		for(int x=0; x < LONGITUDE; x++){
			if(x == 0 || (x == HALF_AVAILABLE_LONGITUDE && (((y % 2) == 0) && isEven)) || x == AVAILABLE_LONGITUDE){					
				mapGame[x][y] = "|";				
			} else {
				mapGame[x][y] = " ";
			}
		}
	}
}

void drawMapGame(string mapGame[LONGITUDE][LATITUDE]){
	for(int y=0; y < LATITUDE; y++){
		string lineOfMap = "";
		for(int x=0; x < LONGITUDE; x++){
			lineOfMap = lineOfMap + mapGame[x][y];
		}
		cout << lineOfMap << endl;
	}
}

void setProtagonistToMapGame(int positionX, int positionY, string mapGame[LONGITUDE][LATITUDE]){
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

void setVillainToMapGame(int positionX, int positionY, string mapGame[LONGITUDE][LATITUDE]){
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

void setMoneyToMapGame(int positionX, int positionY, string mapGame[LONGITUDE][LATITUDE]){
	mapGame[positionX][positionY] = 		"$";
}

void showGameOver(string mapGame[LONGITUDE][LATITUDE]){
	mapGame[HALF_AVAILABLE_LONGITUDE - 4][15] = "G";
	mapGame[HALF_AVAILABLE_LONGITUDE - 3][15] = "A";
	mapGame[HALF_AVAILABLE_LONGITUDE - 2][15] = "M";
	mapGame[HALF_AVAILABLE_LONGITUDE - 1][15] = "E";
	mapGame[HALF_AVAILABLE_LONGITUDE][15] 	  = " ";
	mapGame[HALF_AVAILABLE_LONGITUDE + 1][15] = "O";
	mapGame[HALF_AVAILABLE_LONGITUDE + 2][15] = "V";
	mapGame[HALF_AVAILABLE_LONGITUDE + 3][15] = "E";
	mapGame[HALF_AVAILABLE_LONGITUDE + 4][15] = "R";
}

void remoteProtagonist(int &positionX, int &positionY){
	if(GetAsyncKeyState(VK_LEFT)){
	    if(positionX > MIN_POSITION_X){
	        positionX--;
	    }
	}
	if(GetAsyncKeyState(VK_RIGHT)){
	    if(positionX < MAX_POSITION_X) {
	        positionX++;
	    }
	}
	if(GetAsyncKeyState(VK_UP)){
	    if(positionY > MIN_POSITION_Y){
	        positionY--;
	    }
	}
	if(GetAsyncKeyState(VK_DOWN)){
	    if(positionY < MAX_POSITION_Y){
	        positionY++;
	    }
	}
}

bool validCollision(int positionX, int positionY, int positionXOfVillain, int positionYOfVillain){
	int collisionX = abs(positionX - positionXOfVillain);
    int collisionY = abs(positionY - positionYOfVillain);
    return collisionX < VEHICLE_LENGTH && collisionY < VEHICLE_LENGTH;
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
    if(positionY >= AVAILABLE_LATITUDE) {
    	++score;
    	positionY = rand() % 5; // rand from 0 to 5
     	positionX = MIN_POSITION_X + rand() % (MAX_POSITION_X - 1); // rand from 1 to 37	
	} else {
		++positionY;
	}
}

void moveMoney(int &positionX, int &positionY){
    if(positionY >= AVAILABLE_LATITUDE) {
    	positionY = rand() % 5; // rand from 0 to 5
     	positionX = MIN_POSITION_X + rand() % (AVAILABLE_LATITUDE - 2); // rand from 1 to 37	
	} else {
		++positionY;
	}
}

void sumMoney(int positionX, int positionY, int &positionXOfMoney, int &positionYOfMoney, int &money){
	if(	(positionX == positionXOfMoney && positionY == positionYOfMoney) ||
		(positionX + 1 == positionXOfMoney && positionY == positionYOfMoney) ||
		(positionX + 2 == positionXOfMoney && positionY == positionYOfMoney)){
		
		positionYOfMoney = AVAILABLE_LATITUDE + 1;
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

void insertPlayerName(){
	fflush(stdin);
	cin.clear(); 
	cout << "Nhap ten cua ban: "; 
	cin >> userHighScore; 
	cout << "Ten ban la: " << userHighScore << endl;
	cin.clear(); 							
	Sleep(1000);
}

void startGame(){
	
	string mapGame[LONGITUDE][LATITUDE];
	
	int positionX = HALF_AVAILABLE_LONGITUDE - 1;
	int positionY = MAX_POSITION_Y;
	
	int positionXOfVillain01 = MIN_POSITION_X;
	int positionYOfVillain01 = MIN_POSITION_Y;
	
	int positionXOfVillain02 = HALF_AVAILABLE_LONGITUDE - 1; 
	int positionYOfVillain02 = MIN_POSITION_Y; 
	
	int positionXOfVillain03 = MAX_POSITION_X; 	
	int positionYOfVillain03 = MIN_POSITION_Y;
	
	
	int positionXOfMoney01 = MIN_POSITION_X + 1;		
	int positionYOfMoney01 = MIN_POSITION_Y ;
	
	int positionXOfMoney02 = MIN_POSITION_X  + 10;
	int positionYOfMoney02 = MIN_POSITION_Y; 
	
	int positionXOfMoney03 = MIN_POSITION_X + 20;
	int positionYOfMoney03 = MIN_POSITION_Y;
	
	int positionXOfMoney04 = MIN_POSITION_X  + 30;
	int positionYOfMoney04 = MIN_POSITION_Y;
	
	int positionXOfMoney05 = MAX_POSITION_X;
	int positionYOfMoney05 = MIN_POSITION_Y ;
	
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
		
		setMoneyToMapGame(positionXOfMoney01, positionYOfMoney01, mapGame);
		setMoneyToMapGame(positionXOfMoney02, positionYOfMoney02, mapGame);
		setMoneyToMapGame(positionXOfMoney03, positionYOfMoney03, mapGame);
		setMoneyToMapGame(positionXOfMoney04, positionYOfMoney04, mapGame);
		setMoneyToMapGame(positionXOfMoney05, positionYOfMoney05, mapGame);
		
		setVillainToMapGame(positionXOfVillain01, positionYOfVillain01, mapGame); 
		setVillainToMapGame(positionXOfVillain02, positionYOfVillain02, mapGame);
		setVillainToMapGame(positionXOfVillain03, positionYOfVillain03, mapGame);
		

		
		sumScoreAndMoveVillain(positionXOfVillain01, positionYOfVillain01, score);
		sumScoreAndMoveVillain(positionXOfVillain02, positionYOfVillain02, score);
		sumScoreAndMoveVillain(positionXOfVillain03, positionYOfVillain03, score);
				
		moveMoney(positionXOfMoney01, positionYOfMoney01);
		moveMoney(positionXOfMoney02, positionYOfMoney02);
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
				highScore = score;
				highMoney = money;
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
	cout << "Press spacebar to select!" << endl << endl;
	string menu[] = {"New Game", "High Score", "Inset Name", "Exit Game"};
	for(int index = 0; index < 4; index ++){
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
				slectedItem = 4;
			}
			slectedItem--;
			showMenu(slectedItem);
			Sleep(200);	
		}
		
		if(GetAsyncKeyState(VK_DOWN)){
			if(slectedItem == 3) {
				slectedItem = -1;
			}
			slectedItem++;
			showMenu(slectedItem);
			Sleep(200);	
		}
		
		if(GetAsyncKeyState(VK_SPACE)){
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
		} else if(slectedItem == 1){
			showHighscore();
		} else if(slectedItem == 2){
			insertPlayerName();
		}
		
	} while(slectedItem != 3);
	
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

