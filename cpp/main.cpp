#include <iostream>
#include "puzzle.h"
#include <algorithm>


int findFreeX(int puzzle[WIDTH][HEIGHT]);
int findFreeY(int puzzle[WIDTH][HEIGHT]);

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

    State initial(findFreeX(startingBoard),findFreeY(startingBoard),startingBoard);//Creates the starting state
    State goal(2,2,goalBoard);//Sets a goal
    


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