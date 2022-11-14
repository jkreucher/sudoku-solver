#include <stdio.h>

// sudoku to solve
// zeros are blanks
int sudoku[9][9] = {
	0,3,7,1,0,6,4,9,8,
	1,2,0,8,9,0,3,7,0,
	8,0,9,3,4,7,0,2,5,
	0,8,3,0,5,4,2,0,9,
	2,4,0,6,3,0,0,8,7,
	9,0,5,2,1,8,6,4,3,
	0,1,8,0,6,3,9,0,2,
	3,0,2,9,0,1,7,6,4,
	4,9,0,5,7,2,0,3,1
};


// function prototypes
void sudoku_input();
void sudoku_print();
int is_valid(int x, int y);
int solve();


// main function
int main() {

	//sudoku_input();
	//printf("Solving Sudoku...");
	//solve();
	//printf("\nDone\n");

	sudoku_print();
	printf("\n");
	solve();

	return 0;
}


// this function lets the user type in
// a sudoku to solve
void sudoku_input() {
	printf("Note: zeros are blanks. Separate numbers by spaces or returns\n");
	printf("Sudoku to solve:\n");
	for(int y=0; y<9; y++)
		for(int x=0; x<9; x++)
			scanf("%d", &sudoku[y][x]);
}


void sudoku_print() {
	for(int y=0; y<9; y++) {
		// draw horizontal separator
		if((y%3 == 0) && (y != 0))
			printf("-----+-----+-----\n");
		
		// go through horizontal numbers
		for(int x=0; x<9; x++) {
			// draw vertical separator
			if((x%3 == 0) && (x != 0))
				printf("|");
			else if(x != 0)
				printf(" ");
			
			// print number or blank if the number is zero
			if(sudoku[9*y+x])
				printf("%d", sudoku[y][x]);
			else
				printf(" ");
		}

		// newline after every horizontal line
		printf("\n");
	}
}


// this function sets a number at position x,y
// and checks if the change is valid
int is_valid(int x, int y) {
	// check horizontal line
	int mask = 0;
	for(int cell=0; cell<9; cell++) {
		// ignore blank cells
		if(sudoku[y][cell] > 0) {
			//check if number already used
			if((1 << sudoku[y][cell]) & mask) {
				return 1;
			} else {
				mask |= 1 << sudoku[y][cell];
			}
		}
	}

	// check vertical line
	mask = 0;
	for(int cell=0; cell<9; cell++) {
		// ignore blank cells
		if(sudoku[cell][x] > 0) {
			// check if number already used
			if((1 << sudoku[cell][x]) & mask) {
				return 1;
			} else {
				mask |= 1 << sudoku[cell][x];
			}
		}
	}

	// check 3x3 square
	mask = 0;
	for(int cell=0; cell<9; cell++) {
		// calculate coordinates
		int cx = ((x / 3) * 3) + (cell % 3);
		int cy = ((y / 3) * 3) + (cell / 3);
		// ignore blank cells
		if(sudoku[cy][cx] > 0) {
			// check if number already used
			if((1 << sudoku[cy][cx]) & mask) {
				return 1;
			} else {
				mask |= 1 << sudoku[cy][cx];
			}
		}
	}

	return 0;
}


// recursive solver using backtracking
int solve() {
	for(int y=0; y<9; y++) {
		for(int x=0; x<9; x++) {
			// check if we are at the next blank cell
			if(sudoku[y][x] == 0) {
				// try every number
				for(int num=1; num<=9; num++) {
					// write number in blank cell and check if number is valid
					sudoku[y][x] = num;
					if(is_valid(x, y) == 0) {
						solve();
					}
					sudoku[y][x] = 0;
				}
				return 1;
			}
		}
	}
	// found a solution
	printf("Solution: \n");
	sudoku_print();
	printf("\n");
	return 0;
}