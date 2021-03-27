#include<iostream>
#include<limits.h>
#include <stdlib.h>
#include<ctime>
using namespace std;
int generate[8];
int chess_board[8][8];
int best_chess_board[8][8];
int h, h_compare;

void display(int a[8][8]){
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			cout << a[i][j] << " ";
		}
		cout << endl;
	}
}

void generate_puzzles(){
	int x;
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			chess_board[i][j] = 0;
		}
	}
	srand(time(0));
	for(int i = 0; i < 8; i++){
		int x = rand() % 8; // generate random numbers between 0 to 7
		chess_board[x][i] = 1;
	}
	//display(chess_board);
	return;
}

void allocate(){
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			best_chess_board[i][j] = chess_board[i][j];
		}
	}
}

int right(int row , int col){
	int threatsFromRight = 0;
	for(int i = col + 1; i < 8; i++){
		if(chess_board[row][i] == 1){
			threatsFromRight++;
		}
	}
	//cerr << "threatsFromRight: " << threatsFromRight << endl;
	return threatsFromRight;
}

int right_up_diagonal(int row , int col){
	int threatsFromRightUpDiagonal = 0;
	int i = row - 1, j = col + 1;
	while(0 <= i && i < 8 && 0 <= j && j < 8){
		if(chess_board[i][j] == 1)
			threatsFromRightUpDiagonal++;
		i--; j++;
	}
	//cerr << "threatsFromRightUpDiagonal: " << threatsFromRightUpDiagonal << endl;
	return threatsFromRightUpDiagonal;
}

int right_down_diagonal(int row , int col){
	int threatsFromRightDownDiagonal = 0;
	int i = row + 1, j = col + 1;
	while(0 <= i && i < 8 && 0 <= j && j < 8){
		if(chess_board[i][j] == 1)
			threatsFromRightDownDiagonal++;
		i++; j++;
	}
	//cerr << "threatsFromRightDownDiagonal: " << threatsFromRightDownDiagonal << endl;
	return threatsFromRightDownDiagonal;
}

int count_threats(){
	int threats = 0;
	for(int i = 0; i < 8; i++){
		for(int j = 0; j < 8; j++){
			if(chess_board[i][j] == 1){
				//cerr << "threat happens at: (" << i << " , " << j << ")" << endl;
				threats += right(i , j) + right_up_diagonal(i , j) + right_down_diagonal(i , j);
			}
		}
	}
	//cerr << "threats = " << threats << endl;
	return threats;
}

int make_successor(){
	int queen;
	for(int i = 0; i < 8; i++){ //colomn
		for(int j = 0; j < 8; j++){ //row    //In this loop, we will find the row of each colomn where a queen is located.
			if(chess_board[j][i] == 1){
				queen = j;
				//cerr << "queen = " << queen << endl;
				break;
			}
		}
		for(int j = 0; j < 8; j++){ // row
			if(j != queen){
				chess_board[j][i] = 1;
				chess_board[queen][i] = 0;
				int c = count_threats();
				if(c < h){
					h = c;
					allocate();
				}
				chess_board[j][i] = 0;
				chess_board[queen][i] = 1;
			}
		}
	}
	return h;
}

int main(){
	h = 10;
	int counter = 0;
	while(h != 0){
		counter++;
		//generate different puzzles.
		//cout << "generate #" << counter++ << endl;
		generate_puzzles();
		//display(chess_board);
		h = count_threats();
		h_compare = h;
		while(h_compare > make_successor()){
			//cout << h << endl;
			h_compare = h;
			for(int i = 0; i < 8; i++){
				for(int j = 0; j < 8; j++){
					chess_board[i][j] = best_chess_board[i][j];
				}
			}
		}
	}
	cout << "Number of generating a new chess board: " << counter << endl;
	display(chess_board);
	return 0;
}
