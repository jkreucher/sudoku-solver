TARGET=sudoku_solver

all:
	gcc main.c -o $(TARGET)

clean:
	rm -f $(TARGET)
