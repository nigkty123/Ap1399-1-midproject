#include <iostream>
#include "puzzle.h"
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <iomanip>
#include <string>
#include <vector>
#include <unordered_set>
#include <stdlib.h>     /* srand, rand */
#include <time.h>
#include <thread>
#include <chrono>
#include <sstream>

enum class ansi_color_code: int{
    black = 30,
    red=31,
    green=32,
    yellow=33,
    blue=34,
    magenta=35,
    cyan=36,
    white=37,
    bright_black = 90,
    bright_red=91,
    bright_green=92,
    bright_yellow=93,
    bright_blue=94,
    bright_magenta=95,
    bright_cyan=96,
    bright_white=97,
};

template<typename printable>
std::string print_as_color(printable const& value, ansi_color_code color){
    std::stringstream sstr;
    sstr<<"\033[1;"<<static_cast<int>(color)<<"m"<<value<<"\033[0m";
    return sstr.str();
}
template<ansi_color_code color,typename printable>
std::string print_as_color(printable const& value){
    std::stringstream sstr;
    sstr<<"\033[1;"<<static_cast<int>(color)<<"m"<<value<<"\033[0m";
    return sstr.str();
}

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
    int command;
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


    //std::cout<<findFreeX(startingBoard)<<std::endl;
    //std::cout<<findFreeY(startingBoard)<<std::endl;

        /*
            int startingBoard[3][3]= 
        {
        {6, 7, 1} ,   //  initializers for row indexed by 0 
        {0, 3, 2} ,   //  initializers for row indexed by 1 
        {8, 5, 4}   //  initializers for row indexed by 2 
        };
        */
    


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
    

    std::cout<<print_as_color<ansi_color_code::bright_green>("Starting State(BFS): \n")<<print_as_color<ansi_color_code::cyan>(initial.toString())<<"\n"<<print_as_color<ansi_color_code::bright_green>("\nGoal State: \n")<<print_as_color<ansi_color_code::cyan>(goal.toString())<<std::endl;//Prints the starting to final state

    State solution;

    BFS(goal,Qagenda,Qclosed,solution);

    std::cout<<print_as_color<ansi_color_code::magenta>("BFS Solution: ")<<std::endl;
    std::cout<<print_as_color<ansi_color_code::blue>(solution.getPath())<<std::endl;
    std::cout<<print_as_color<ansi_color_code::yellow>("number of moves:")<<print_as_color<ansi_color_code::blue>(solution.no_OfMoves())<<std::endl;
    
    
    DFS(goal,agenda,closed,solution);

    std::cout<<print_as_color<ansi_color_code::magenta>("DFS Solution: ")<<std::endl;
    std::cout<<print_as_color<ansi_color_code::blue>(solution.getPath())<<std::endl;
    std::cout<<print_as_color<ansi_color_code::yellow>("number of moves:")<<print_as_color<ansi_color_code::blue>(solution.no_OfMoves())<<std::endl;


    return 0;
}



