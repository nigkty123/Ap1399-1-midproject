#include <iostream>
#include "puzzle.h"
#include <algorithm>
#include <fstream>


int findFreeX(int puzzle[WIDTH][HEIGHT]);
int findFreeY(int puzzle[WIDTH][HEIGHT]);


template <typename myState>
bool BFS(const myState &goal,std::queue<myState> &agenda, std::set<myState> &closed,myState &solution)
{
    myState s;
    while (!(agenda.empty()))
    {
        s=agenda.front();
        agenda.pop();

        if (s==goal)
        {
            solution = s;
            return true;
        }

        if (closed.size()==0 || (closed.find(s)==closed.end()))// if closed set is empty or set does NOT contain s,

        {
            std::vector<myState> children;
            children=s.expand();
            closed.insert(s);
            for (unsigned int i=0;i<children.size();i++)
                agenda.push(children.at(i));
        }
    }

    return false;
}

template <typename myState>
bool DFS(const myState &goal,std::stack<myState> &agenda, std::set<myState> &closed,myState &solution)
{
    myState s;
    while (!(agenda.empty()))
    {
        s=agenda.top();
        agenda.pop();

        if (s==goal)
        {
            solution = s;
            return true;
        }

        if (closed.size()==0 || (closed.find(s)==closed.end()))

        {
            vector<myState> children;
            children=s.expand();
            closed.insert(s);
            for (unsigned int i=0;i<children.size();i++)
                agenda.push(children.at(i));
        }
    }

    return false;
}


int main()
{
    int startingBoard[3][3] ;
    std::cout<< "Enter your puzzle:"<<std::endl;
    std::cin>> startingBoard;

    

    //int startingBoard[3][3] = 
   // {
   //{6, 7, 1} ,   /*  initializers for row indexed by 0 */
  // {0, 3, 2} ,   /*  initializers for row indexed by 1 */
   //{8, 5, 4}   /*  initializers for row indexed by 2 */
    //};




    int goalBoard[3][3] = 
    {
   {1, 2, 3} ,   /*  initializers for row indexed by 0 */
   {4, 5, 6} ,   /*  initializers for row indexed by 1 */
   {7, 8, 0}   /*  initializers for row indexed by 2 */
    };

    State initial(findFreeX(startingBoard),findFreeY(startingBoard),startingBoard);//Creates the starting state
    State goal(2,2,goalBoard);//Sets a goal
    
    std::queue <State> Qagenda;
    std::stack <State> agenda;;
    std::set <State> Qclosed;
    std::set <State> closed;

    agenda.push(initial);
    Qagenda.push(initial);
    

    std::cout<<"Starting State(BFS): \n"<<initial.toString()<<"\n"<<"\nGoal State: \n"<<goal.toString()<<std::endl;//Prints the starting to final state

    State solution;

    BFS(goal,Qagenda,Qclosed,solution);

    std::cout<<"BFS Solution: "<<std::endl;
    std::cout<<solution.getPath()<<std::endl;;
    
   
    
    std::cout<<"Starting State(DFS): \n"<<initial.toString()<<"\n"<<"\nGoal State: \n"<<goal.toString()<<std::endl;//Prints the starting to final state
    
    
    DFS(goal,agenda,closed,solution);

    std::cout<<"DFS Solution: "<<std::endl;
    std::cout<<solution.getPath()<<std::endl;;


    return 0;
}

int findFreeX(int puzzle[WIDTH][HEIGHT])
{
    int freeX = 2 ;
    for(int i = 0 ; i < WIDTH ; i++)
    {
        for(int j = 0 ; j<HEIGHT ; j++)
        {
            if (puzzle[i][j] == 0)
            {
                freeX = i;
            }
        }
    }
    return freeX ;
}

int findFreeY(int puzzle[WIDTH][HEIGHT])
{
    int freeY = 2 ;
    for(int i = 0 ; i < WIDTH ; i++)
    {
        for(int j = 0 ; j<HEIGHT ; j++)
        {
            if (puzzle[i][j] == 0)
            {
                freeY = j;
            }
        }
    }
    return  freeY;
}