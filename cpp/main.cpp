#include <iostream>
#include "puzzle.h"
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <vector>


int findFreeX(int puzzle[WIDTH][HEIGHT])
{
    int freeX;
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
    int freeY;
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
void initialize_Board(int puzzle[WIDTH][HEIGHT])
{
    std::vector<int>::iterator temp;
    int random_roll = 0;
    std::vector<int> tiles;


    for(int i = 0; i < WIDTH; i++)
    {
        for (int j = 0; j < HEIGHT; j++)
        {
            random_roll = rand() % 9;
            temp = std::find(tiles.begin() , tiles.end() , random_roll);
            if(temp ==  tiles.end())
            {
                puzzle[i][j] = random_roll;
                tiles.push_back(random_roll);
            }           
        }   
    }
}

void get_user_input(int puzzle[WIDTH][HEIGHT])
{
    std::vector<int> input;
    int tile;
    std::cout << "Enter your puzzle: "<<std::endl;
    unsigned int i = 0;
    while( i != 9)
    {
        std::cout<<"tile["<<i<<"]:"<<std::endl;
        std::cin>>tile;
        input.push_back(tile);
        i++;
    }
    unsigned int n = 0;
    while( n != 9)
    {
        for(unsigned int i = 0 ; i<3 ; i++)
        {
            for(unsigned int j = 0 ; j<3 ; j++)
            {
                puzzle[i][j] = input[n];
                n++;
            }
        }
        
    }
}

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
            std::vector<myState> children;
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
    std::vector<int>startingboard;
    int startingBoard[3][3] ;
    
    //std::cout<< "Enter your puzzle:"<<std::endl;
    
    
    initialize_Board(startingBoard);
    //get_user_input(startingBoard);
    
    /*
    

    
    int startingBoard[3][3] = 
    {
    {6, 7, 1} ,   //  initializers for row indexed by 0 
    {0, 3, 2} ,   //  initializers for row indexed by 1 
    {8, 5, 4}   //  initializers for row indexed by 2 
    };
    */    

    //std::cout<<findFreeX(startingBoard)<<std::endl;
    //std::cout<<findFreeY(startingBoard)<<std::endl;

    


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
    std::cout<<solution.getPath()<<std::endl;
    std::cout<<"number of moves:"<<solution.no_OfMoves()<<std::endl;
   
    
    std::cout<<"Starting State(DFS): \n"<<initial.toString()<<"\n"<<"\nGoal State: \n"<<goal.toString()<<std::endl;//Prints the starting to final state
    
    
    DFS(goal,agenda,closed,solution);

    std::cout<<"DFS Solution: "<<std::endl;
    std::cout<<solution.getPath()<<std::endl;
    std::cout<<"number of moves:"<<solution.no_OfMoves()<<std::endl;


    return 0;
}



