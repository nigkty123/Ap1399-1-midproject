
#include "puzzle.h"
#include <iostream>
#include <color.h>


State::State()
{

}

State::State(size_t row, size_t col, size_t puzzle[][WIDTH])
{
    this->freeX = row;
    this->freeY = col;

    for (size_t i=0;i<WIDTH;i++)
        for (size_t j=0;j<HEIGHT;j++)
            this->puzzle[i][j]=puzzle[i][j];
}

size_t State::noOfMoves() const
{
    return path.size();
}

State State::operator= (State o)
{
    freeX = o.freeX;
    freeY = o.freeY;

    path = o.path;

    for (size_t i=0;i<WIDTH;i++)
        for (size_t j=0;j<HEIGHT;j++)
            puzzle[i][j]=o.puzzle[i][j];

    return *this;
}

bool State::operator==(const State& s) const 
{
    for (size_t i=0;i<WIDTH;i++)
        for (size_t j=0;j<HEIGHT;j++)
                {
                    if (puzzle[i][j] != s.puzzle[i][j])
                        return false;
                }

    return true;
}


void State::setFree(size_t x, size_t y)
{
    freeX = x;
    freeY = y;
}

size_t State::getFreeY()
{
    return freeY;
}

size_t State::getFreeX()
{
    return freeX;
}


void State::swapTileValues(size_t row, size_t col, State &n)
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

    for (size_t i = 0; i < WIDTH; i++)
    {
        ot << "\n";
        for (size_t j = 0; j < HEIGHT; j++)
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

void State::Show(size_t x, size_t y, size_t puzzle[][WIDTH])
{
    std::string s;
    State child(x,y,puzzle);
    for( size_t i=0 ; i< path.size(); i++)
    {
        
        
        if( path.at(i) == "R" )
        {
            child.moveFreeRight(child);
            std::cout<<print_as_color<ansi_color_code::bright_cyan>(i+1)<<print_as_color<ansi_color_code::bright_cyan>("-Move to Right:")<<std::endl<<print_as_color<ansi_color_code::blue>(child.toString())<<std::endl;
        }

        if( path.at(i) == "L" )
        {
            child.moveFreeLeft(child);
            std::cout<<print_as_color<ansi_color_code::bright_cyan>(i+1)<<print_as_color<ansi_color_code::bright_cyan>("-Move to Left:")<<std::endl<<print_as_color<ansi_color_code::blue>(child.toString())<<std::endl;
        }

        if( path.at(i) == "U" )
        {
            child.moveFreeUp(child);
            std::cout<<print_as_color<ansi_color_code::bright_cyan>(i+1)<<print_as_color<ansi_color_code::bright_cyan>("-Move to Up:")<<std::endl<<print_as_color<ansi_color_code::blue>(child.toString())<<std::endl;
        }

        if( path.at(i) == "D" )
        {
            child.moveFreeDown(child);
            std::cout<<print_as_color<ansi_color_code::bright_cyan>(i+1)<<print_as_color<ansi_color_code::bright_cyan>("-Move to Down:")<<std::endl<<print_as_color<ansi_color_code::blue>(child.toString())<<std::endl;
        }
        
    }
}