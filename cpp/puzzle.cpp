
#include "puzzle.h"
#include<iostream>


State::State()
{

}

State::State(int row, int col, int puzzle[][WIDTH])
{
    this->freeX = row;
    this->freeY = col;

    for (int i=0;i<WIDTH;i++)
        for (int j=0;j<HEIGHT;j++)
            this->puzzle[i][j]=puzzle[i][j];
}

State State::operator= (State o)
{
    freeX = o.freeX;
    freeY = o.freeY;

    path = o.path;

    for (int i=0;i<WIDTH;i++)
        for (int j=0;j<HEIGHT;j++)
            puzzle[i][j]=o.puzzle[i][j];

    return *this;
}

bool State::operator==(const State& s) const 
{
    for (int i=0;i<WIDTH;i++)
        for (int j=0;j<HEIGHT;j++)
                {
                    if (puzzle[i][j] != s.puzzle[i][j])
                        return false;
                }

    return true;
}


void State::setFree(int x, int y)
{
    freeX = x;
    freeY = y;
}

int State::getFreeY()
{
    return freeY;
}

int State::getFreeX()
{
    return freeX;
}


void State::swapTileValues(int row, int col, State &n)
{
    n.puzzle[n.getFreeX()][n.getFreeY()] = n.puzzle[row][col];
    n.puzzle[row][col] = 0;
}

bool State::moveFreeUp(State &n)
{
    if (getFreeX()>0)
    {
        n=*this;
        swapTileValues(n.getFreeX()-1, n.getFreeY(), n);
        n.setFree(n.getFreeX()-1, n.getFreeY());
        n.path.push_back("U"); // U for up
        return true;
    }
    return false;
}

bool State::moveFreeDown(State &n)
{
    if (getFreeX()<2)
    {
        n=*this;
        swapTileValues(n.getFreeX()+1, n.getFreeY(), n);
        n.setFree(n.getFreeX()+1, n.getFreeY());
        n.path.push_back("D"); //D for down
        return true;
    }
    return false;
}
bool State::moveFreeLeft(State &n)
{
    if (getFreeY()>0)
    {
        n=*this;
        swapTileValues(n.getFreeX(), n.getFreeY()-1, n);
        n.setFree(n.getFreeX(), n.getFreeY()-1);
        n.path.push_back("L");  // L for Left
        return true;
    }
    return false;
}
bool State::moveFreeRight(State &n)
{
    if (getFreeY()<2)
    {
        n=*this;
        swapTileValues(n.getFreeX(), n.getFreeY()+1, n);
        n.setFree(n.getFreeX(), n.getFreeY()+1);
        n.path.push_back("R"); //R for right
        return true;
    }
    return false;
}

std::string State::toString () const
{
    std::stringstream ot;

    for (int i = 0; i < WIDTH; i++)
    {
        ot << "\n";
        for (int j = 0; j < HEIGHT; j++)
            if (puzzle[i][j] != 0)
                ot<<puzzle[i][j]<< "  ";
            else
                ot<<" "<< "  ";

    }

    return ot.str();
}

std::string State::getPath()
{
    unsigned i;
    std::string s;
    if (path.size()>0)
    {
        for (i=0;i<path.size()-1;i++)
            s+=path.at(i)+", ";
        s+=path.at(i)+ "\n";
    }
    return s;
}

std::vector <State> State::expand()
{
    std::vector <State> children;
    State child;

    if (moveFreeUp(child))
        children.push_back(child);
    if (moveFreeLeft(child))
        children.push_back(child);
    if (moveFreeDown(child))
        children.push_back(child);
    if (moveFreeRight(child))
        children.push_back(child);

    return children;
}

bool operator< (const State& a, const State& o)
{
    return (a.toString() < o.toString());
}