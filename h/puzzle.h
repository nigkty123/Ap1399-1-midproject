
#ifndef PUZZLE_H
#define PUZZLE_H
#include <string>
#include <vector>
#include <stack>
#include <queue>
#include <set>
#include <sstream>
#include <cstdlib> //For abs()
#define WIDTH 3
#define HEIGHT 3

using namespace std;

class State
{
    int freeX, freeY;//free cell position
    int puzzle[WIDTH][HEIGHT];// The numbers of each cell
    vector <string> path; // path taken

    public:
          /*Constructors*/
    State();
    State(int x, int y, int puzzle[][WIDTH]);
    void setFree(int i, int j);//Sets free the specified tile
    int getFreeY();//Returns the current Y position of the free tile
    int getFreeX();//Returns the current x position of the free tile

    private:

    void swapTileValues(int row, int col, State &n);//Changes the value of the previous free tile
    bool moveFreeUp(State &n);//Goes up if the tile above the current is free
    bool moveFreeDown(State &n);//Goes up if the tile below the current is free
    bool moveFreeLeft(State &n);//Goes left if the tile left to the current is free
    bool moveFreeRight(State &n);//Goes right if the tile right to the current is free
};

#endif // PUZZLE_H



