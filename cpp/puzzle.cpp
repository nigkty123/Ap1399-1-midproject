
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

void State::BFS(int s)
{
    // Mark all the vertices as not visited
    bool *visited = new bool[V];
    for(int i = 0; i < V; i++)
        visited[i] = false;
 
    // Create a queue for BFS
    std::list<int> queue;
 
    // Mark the current node as visited and enqueue it
    visited[s] = true;
    queue.push_back(s);
 
    // 'i' will be used to get all adjacent
    // vertices of a vertex
    list<int>::iterator i;
 
    while(!queue.empty())
    {
        // Dequeue a vertex from queue and print it
        s = queue.front();
        cout << s << " ";
        queue.pop_front();
 
        // Get all adjacent vertices of the dequeued
        // vertex s. If a adjacent has not been visited, 
        // then mark it visited and enqueue it
        for (i = adj[s].begin(); i != adj[s].end(); ++i)
        {
            if (!visited[*i])
            {
                visited[*i] = true;
                queue.push_back(*i);
            }
        }
    }
}