#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define BOARD_SIZE 30 
#define DBG(X) printf( # X ": %d\n", X)

char board[BOARD_SIZE][BOARD_SIZE] = {
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 1, 0, 0, 1, 0, 0, 0, 0, 0},
	{0, 1, 0, 0, 0, 1, 0, 0, 0, 0},
	{0, 1, 0, 1, 1, 1, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
	{0, 0, 0, 0, 0, 0, 0, 0, 0, 0},
};

/*******************************
	     Stack
*******************************/
struct op{
	int i, j;
	char stat;
};

//TODO: decrease the stack size.
struct op opstack[BOARD_SIZE * BOARD_SIZE];
struct op *stacktop = opstack;

size_t stack_elements(void) {return (size_t)(stacktop - opstack);}
void push(struct op _o){ *stacktop++ = _o; }
struct op pop(void){ return *--stacktop; }

/*******************************/


void print_board(void);
void next_generation(void);
int live_neighbors(int i, int j);
char get_next_stat(int i, int j);
void operate(struct op o) { board[o.i][o.j] = o.stat; }
int main(){
	while(1){
		print_board();
		next_generation();
	//	getchar();
		system("sleep 0.5");
	}
}

void print_board(void){
	system("clear");
	for(int i = 0; i < BOARD_SIZE; i++){
		putchar('|');
		for(int j = 0; j < BOARD_SIZE; j++)
			printf("%c|", board[i][j] ? '*' : ' ');
		putchar('\n');
	}
}

void next_generation(void) {
	for(int i = 0; i < BOARD_SIZE; i++)
		for(int j = 0; j < BOARD_SIZE; j++) {
			char next_stat = get_next_stat(i, j);
			if(next_stat != board[i][j]){
				struct op o = {i, j, next_stat};
				push(o);
			}
		}
	while(stack_elements() > 0)
		operate(pop());
}

char get_next_stat(int i, int j){
	int l = live_neighbors(i, j);
	if(board[i][j]){
		if(l < 2 || l > 3)
			return 0;
	}
	else if(l == 3){
		return 1;
	}
	return board[i][j];
}

#define IS_VALID(i, j) (i > 0 && j > 0 && i < BOARD_SIZE && j < BOARD_SIZE )
int live_neighbors(int i, int j){
	const int neighbor[2][8] = {
		{-1, 0, 1, -1, 1, -1, 0, 1},
		{-1, -1, -1, 0, 0, 1, 1, 1}
	};
	int res = 0;
	for(int k = 0, _i, _j; k < 8; k++) {
		_i = i + neighbor[0][k];
		_j = j + neighbor[1][k];
		if( IS_VALID(_i, _j) )
			res += board[_i][_j];
	}
	return res;
}
