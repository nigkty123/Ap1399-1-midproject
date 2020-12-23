#include <iostream>
#include "puzzle.h"
#include <algorithm>


int main()
{

    int startingBoard[3][3] = 
    {
   {6, 7, 1} ,   /*  initializers for row indexed by 0 */
   {0, 3, 2} ,   /*  initializers for row indexed by 1 */
   {8, 5, 4}   /*  initializers for row indexed by 2 */
    };
    int goalBoard[3][3] = 
    {
   {1, 2, 3} ,   /*  initializers for row indexed by 0 */
   {4, 5, 6} ,   /*  initializers for row indexed by 1 */
   {7, 8, 0}   /*  initializers for row indexed by 2 */
    };

    int Freei , Freey;
    for(int i = 0 ; i < 9 ; i++)
    {
        for(int j = 0 ; j<9 ; j++)
        {
            if (startingBoard[i][j] == 0)
            {
                Freei = i;
                Freey = j;
                return Freei , Freey;
            }
            else
            {
                std::cout<<"The puzzle is wrong ! there was no free space given as 0"<<std::endl;
            }
        }
    }

    State initial(Freei,Freey,startingBoard);//Creates the starting state
    State goal(2,2,goalBoard);//Sets a goal



    return 0;
}