
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


class State
{
    
    size_t freeX, freeY;//free cell position
    size_t puzzle[WIDTH][HEIGHT];// The numbers of each cell
    std::vector <std::string> path; // path taken
    public:
          /*Constructors*/
    State();
    State(size_t x, size_t y, size_t puzzle[][WIDTH]);
    void setFree(size_t i, size_t j);//Sets free the specified tile
    size_t getFreeY();//Returns the current Y position of the free tile
    size_t getFreeX();//Returns the current x position of the free tile
    State operator= (State o);//to copy the State object
    bool operator==(const State& o) const ;// to check if the two objects are equal
    std::string toString () const;// to return as a String the current State
    std::vector <State> expand();//Expanding the States and returns it's children
    std::string getPath();//Returns path that the free tile has moved so far
    friend bool operator< (const State& a,const State& o);//return true if State a is smaller
    size_t noOfMoves() const ;
    void Show( size_t x, size_t y, size_t puzzle[][WIDTH]);
    
    private:
    
    void swapTileValues(size_t row, size_t col, State &n);//Changes the value of the previous free tile
    bool moveFreeUp(State &n);//Goes up if the tile above the current is free
    bool moveFreeDown(State &n);//Goes up if the tile below the current is free
    bool moveFreeLeft(State &n);//Goes left if the tile left to the current is free
    bool moveFreeRight(State &n);//Goes right if the tile right to the current is free
    
};

#endif // PUZZLE_H



