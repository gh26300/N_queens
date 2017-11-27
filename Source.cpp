#include <cstdio>
#include <iostream>
#include <random>
#include <time.h>
#include <iomanip>
using namespace std;
#define n  20
int **board;
int *check;
void initboard();
void random_set_position();
void draw_board();
int calc_collision();
void change_board_col(int present_collision);
void load_queens_position();
//動態配置二維陣列
//交換以 board [x] [  ]為主   上下列交換
// Q1 (x,y) Q2 (u,v)   if   |x-u|  = |y-v|  時為處斜線上  

struct position
{
	int x;
	int y;
} queens_pos[n];

void main() {
	srand(time(NULL));
	int present_collision=0;
	int step;
	while (1){
		//init
		initboard();
		//set position & get queen's pos
		random_set_position();
		load_queens_position();
	    //calc collision
		present_collision=calc_collision();
		//random change cols and test collision's value
		step = 0;
		while (present_collision !=0 && step<n*n ){
			step++;
			if (present_collision != 0){
				change_board_col(present_collision);
				load_queens_position();
			}
			present_collision = calc_collision();

		    if (present_collision==0){ //完成
				cout << endl;
				draw_board();
				for (int i = 0; i < n; i++){
					cout << endl <<" x: "<< setw(2)<<queens_pos[i].x+1 << "  y: " << setw(2)<<queens_pos[i].y+1;
				}
				system("pause");
			}
		}
   		if (step > n*n) 
			cout << "reload"<<endl;
		//release memory
		for (int i = 0; i < n; i++)
			delete[] board[i];
		delete[] board;
		//cout << endl;
		//system("pause");
	}
}
void initboard(){
	//set board[n][n]
	board = new int*[n];
	for (int i = 0; i < n; i++){
		board[i] = new int[n];
	}
	//init board to zero
	for (int row = 0; row < n; row++){       //row
		for (int col = 0; col < n; col++){   //col
			board[row][col] = 0;
		}  
	}
}
void random_set_position(){
	//random set queen's postion
	//*board[i] = i+1;       ==> //first col = i+1
	check = new int[n]; //record col used
	for (int i = 0; i < n; i++){
		int rand_col = rand();
		rand_col = rand_col%n;
		if (check[rand_col] != 1){
			board[i][rand_col] = i + 1;
			check[rand_col] = 1;
		}
		else{
			while (true){
				rand_col = rand();
				rand_col = rand_col%n;
				if (check[rand_col] != 1){
					board[i][rand_col] = i + 1;
					check[rand_col] = 1;
					break;
				}
			}
		}
	}
}
void draw_board(){
	//draw out the board
	for (int row = 0; row < n; row++){    //row
		for (int col = 0; col < n; col++){   //col
			if (board[row][col]!=0)
			cout << " " << setw(2) << board[row][col] << " ";
			else
				cout << " " << "--" << " ";
		}
		cout << endl;
	}
}
int calc_collision(){ //done
	int collision = 0;
	for (int i = 0; i < n; i++){
		for (int j = i+1; j < n; j++){
			int x = abs(queens_pos[i].x - queens_pos[j].x);
			int y = abs(queens_pos[i].y - queens_pos[j].y);
			if (x == y){
				collision++;
			}
		}
	}
	return collision;
}
void change_board_col(int present_collision){
	//set random change
	int  rand_1, rand_2;
	rand_1 = rand()%n;
	rand_2 = rand()% n;
	if (rand_1 != rand_2){
		swap(board[rand_1], board[rand_2]);
		load_queens_position();
	}
	if (calc_collision() > present_collision){
		swap(board[rand_1], board[rand_2]);
		load_queens_position();
	}
}
void load_queens_position(){
	for (int j = 0; j < n; j++){//row
	    for (int  i = 0; i < n; i++){//col
			if (board[j][i] != 0){
				queens_pos[j].x = i; 
				queens_pos[j].y = j;
			}
		}
	}
}