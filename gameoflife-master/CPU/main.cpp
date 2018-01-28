#include <iostream>
#include <ncurses.h>
#include <string>
#include <stdlib.h>

using namespace std;

class Grid {
  private:
    int** grid;
    int sizeOf;
  public:
    Grid(int size) {
      grid = new int*[size];
      for(int i = 0; i < size; i++)
        grid[i] = new int[size];
      sizeOf = size;
    }

    void printGrid() {
      for(int i = 0; i < sizeOf; i++) {
        move(i+1, 0);
        for(int j = 0; j < sizeOf; j++) {
          if(grid[i][j] == 0)
            printw(" ");
          else
            printw("@");
        }
      }
    }

    void refreshGrid() {

      for(int i = 0; i < sizeOf; i++) {
        for(int j = 0; j < sizeOf; j++) {
            int neighbours = calculateNextStep(i, j);
            if(grid[i][j] == 0 && neighbours == 3) {
              grid[i][j] = 1;
            } else if(grid[i][j] == 1 && neighbours < 2) {
              grid[i][j] = 0;
            } else if(grid[i][j] == 1 && neighbours > 3) {
              grid[i][j] = 0;
            } else {
              grid[i][j] = grid[i][j];
            }
        }
      }
    }

    int calculateNextStep(int x, int y) {
      int sum = 0;
      for(int i = -1; i < 2; i++) {
        for(int j = -1; j < 2; j++) {
          int col = (x + i + sizeOf) % sizeOf;
          int row = (y + j + sizeOf) % sizeOf;
          sum += grid[col][row];
        }
      }
      sum -= grid[x][y];
      return sum;
    }

    void fillGrid() {
      srand(time(NULL));
      for(int i = 0; i < sizeOf; i++)
        for(int j = 0; j < sizeOf; j++)
          grid[i][j] = rand() % 2;
    }
};

int main() {
  initscr();
  WINDOW * win = newwin(30, 10, 0, 0);
  Grid myGrid = Grid(15);
  myGrid.fillGrid();
  myGrid.printGrid();
  refresh();
  wrefresh(win);
  while(true){
    delay_output(5);
    myGrid.refreshGrid();
    myGrid.printGrid();
    refresh();
    wrefresh(win);
  }
  getch();
  endwin();
  return 0;
}
