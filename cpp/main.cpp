#include <iostream>
#include "puzzle.h"
#include <algorithm>
#include <ctime>
#include <set>
#include <stack>
#include <queue>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <vector>
#include <unordered_set>
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include "color.h"

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

void Random_Board(int puzzle[WIDTH][HEIGHT])
{
    std::vector<int>::iterator temp;
    unsigned int random_roll = 0;
    std::unordered_set<int> tiles;
    std::vector<int> randoms;
    std::vector<int> finish;
    srand(time(0)) ;

    while(tiles.size() != 9)
    {
        random_roll = rand() % 9;
        randoms.push_back(random_roll);
        tiles.insert(randoms.begin(), randoms.end());
    }


    for (const int& x: tiles)
    {
        finish.push_back(x);
    }
    int n = 0;
    while(n != 9)
    {
        for(int i = 0; i < WIDTH; i++)
        {
            for (int j = 0; j < HEIGHT; j++)
            {
                tiles.insert(random_roll);
                puzzle[i][j] = finish[n];    
                n++;    
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
        std::cout<<print_as_color<ansi_color_code::blue>("tile[")<<print_as_color<ansi_color_code::bright_white>(i)<<print_as_color<ansi_color_code::bright_blue>("]:")<<std::endl;
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

int getInvCount(int arr[]) 
{ 
    int inv_count = 0; 
    for (int i = 0; i < 9 - 1; i++) 
        for (int j = i+1; j < 9; j++) 
             // Value 0 is used for empty space 
             if (arr[j] && arr[i] &&  arr[i] > arr[j]) 
                  inv_count++; 
    return inv_count; 
}

bool isSolvable(int puzzle[3][3]) 
{ 
    // Count inversions in given 8 puzzle 
    int invCount = getInvCount((int *)puzzle); 
  
    // return true if inversion count is even. 
    return (invCount%2 == 0); 
} 

template <typename myState>
bool BFS(const myState &goal,std::queue<myState> &agenda, std::set<myState> &closed,myState &solution)
{
    myState s;
    while (!(agenda.empty()) )
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
bool DFS(const myState &goal,std::stack<myState> &agenda, std::set<myState> &closed,myState &solution , size_t depth)
{
    myState s;
    while (!(agenda.empty()) && (agenda.size()<depth))
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
    int command;
    //int goalX;
    //int goalY;
    int freeX;
    int freeY;

    std::cout<< print_as_color<ansi_color_code::bright_blue>("Choose one of the following:")<<std::endl;
    std::cout<< print_as_color<ansi_color_code::bright_blue>("to solve a random puzzle enter: '1'")<<std::endl;
    std::cout<< print_as_color<ansi_color_code::bright_blue>("to solve your own puzzle enter: '2'")<<std::endl;
    std::cin>>command;
    
    if(command==1)
    {
        Random_Board(startingBoard);
        isSolvable(startingBoard)? std::cout << print_as_color<ansi_color_code::green>("Solvable")<<std::endl: 
                      std::cout << print_as_color<ansi_color_code::red>("Not Solvable")<<std::endl;  

    }
    else
    {
        get_user_input(startingBoard);
        isSolvable(startingBoard)? std::cout << print_as_color<ansi_color_code::green>("Solvable")<<std::endl: 
                      std::cout << print_as_color<ansi_color_code::red>("Not Solvable")<<std::endl; 
    }

    
    
    int goalBoard[3][3] = 
    {
    {1, 2, 3} ,   /*  initializers for row indexed by 0 */
    {4, 5, 6} ,   /*  initializers for row indexed by 1 */
    {7, 8, 0}   /*  initializers for row indexed by 2 */
    };
    
    freeX =findFreeX(startingBoard);
    freeY = findFreeY(startingBoard);
    

    State initial(freeX,freeY,startingBoard);//Creates the starting state

    //std::cout<< print_as_color<ansi_color_code::bright_blue>("to choose your own goal enter: '1'")<<std::endl;
    //std::cout<< print_as_color<ansi_color_code::bright_blue>("to solve the puzzle completely enter: '2'")<<std::endl;
    //std::cin>>command2;

    //State goal ;


    State goal(2,2,goalBoard);//Sets a goal
 
    
    std::queue <State> Qagenda;
    std::stack <State> agenda;;
    std::set <State> Qclosed;
    std::set <State> closed;

    agenda.push(initial);
    Qagenda.push(initial);
    

    std::cout<<print_as_color<ansi_color_code::bright_green>("Starting State: \n")<<print_as_color<ansi_color_code::cyan>(initial.toString())<<"\n"<<print_as_color<ansi_color_code::bright_green>("\nGoal State: \n")<<print_as_color<ansi_color_code::cyan>(goal.toString())<<std::endl;//Prints the starting to final state
    
    if(isSolvable(startingBoard)==true)
    {
        std::cout<<print_as_color<ansi_color_code::bright_blue>("which alghorithm should i solve this puzzle with?(BFS = 1 , DFS = 2 , Both = 3)")<<std::endl;
        std::cin>> command;

        if(command == 1 || command == 3)
        {
            State solution;
        
            BFS(goal,Qagenda,Qclosed,solution);

            std::cout<<print_as_color<ansi_color_code::magenta>("BFS Solution: ")<<std::endl;
            std::cout<<print_as_color<ansi_color_code::blue>(solution.getPath())<<std::endl;

            //dfs number of moves
            std::cout<<print_as_color<ansi_color_code::yellow>("number of moves:")<<print_as_color<ansi_color_code::blue>(solution.noOfMoves())<<std::endl;
            
            //bfs step by step solution
            solution.Show(freeX , freeY ,startingBoard);
        

        }

        if(command == 2 || command == 3)
        {
            size_t depth = 7000;
            std::cout<<print_as_color<ansi_color_code::bright_blue>("would you like to enter a depth?if so please enter 1")<<std::endl;
            std::cin>>command;
            if(command == 1)
            {
                std::cout<<print_as_color<ansi_color_code::bright_blue>("please enter a number less than 7000")<<std::endl;
                std::cin>>depth;
            }
            

            State solutionD;

            DFS(goal,agenda,closed,solutionD,depth);

            std::cout<<print_as_color<ansi_color_code::magenta>("DFS Solution: ")<<std::endl;
            std::cout<<print_as_color<ansi_color_code::blue>(solutionD.getPath())<<std::endl;


            //dfs number of moves
            std::cout<<print_as_color<ansi_color_code::yellow>("number of moves:")<<print_as_color<ansi_color_code::blue>(solutionD.noOfMoves())<<std::endl;
            if(solutionD.noOfMoves()==0)
            {
                std::cout<<print_as_color<ansi_color_code::red>("DFS can't solve this puzzle")<<std::endl;
            }

            /// dfs step by step solution
            if(solutionD.noOfMoves()!=0)
            {
                std::cout<< print_as_color<ansi_color_code::bright_blue>("to see the step by step solution for DFS enter: '1'")<<std::endl;
                std::cin>> command ;
                if(command == 1)
                    solutionD.Show(freeX , freeY ,startingBoard);
            }
        }
    }

        
    else
    {
        std::cout<<print_as_color<ansi_color_code::red>("Sorry i can't solve this :(")<<std::endl;
    }
    
    return 0;
}



