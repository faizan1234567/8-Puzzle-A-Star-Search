/*implementation of h1 and h2 heuristics 
h1 = hamming heuristic 
h2 = manhatten heuristic

Author: Muhammad Faizan
*/



// implementation of 8 puzzle using A* search algorithm
/* A* graph search algorithm, which is based on informed search strategy, which uses heuristic function as a component to explore the 
goal in the graph. It starts from the initial state and goes to a goal state with information where to look for the solution*/

/*Author: Muhammad Faizan
MS student at Robotics and intelligent machines at NUST
subject: Aritificial intelligence
course code: CSE-842
Assignement: find the goal state in 8-puzzle using two heuristic function i.e. h1 = tiles misplacment and h2 = manhatten distance*/

#include <iostream>
#include <string>
#include "node.h"
using namespace std;


int misplaced_tiles(int state[3][3], int goal[3][3])
{
    int misplaced_count = 0;
    int same_count = 0;
    for(int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int number = state[i][j];
            int goal_number = goal[i][j];
            if (number == goal_number)
            {
                same_count+=1;
            }
            else
            {
                misplaced_count+=1;
            }
            
            }}

    return misplaced_count;}

int matching_check(int state[3][3], int explored[3][3])
{
    int state_sum = 0;
    for(int i = 0; i < 3; i++)
    {

        for (int j = 0; j < 3; j++)
        {
            int current_state = state[i][j];
            int explored_state = explored[i][j];
            if (current_state != explored_state)
            {
                state_sum +=1;
            }

        }
    }
    return state_sum;
}


int manhatten_cost(int state[3][3], int goal[3][3])
{
    int manhatten_dis = 0;
    for(int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            int number = state[i][j];
            
            for (int m = 0; m < 3; m++)
            {
            int n = 0;
            while (n < 3)
                {
                int goal_number = goal[m][n];
                if (goal_number == number)
                {
                    manhatten_dis += abs(m - i) + abs(n - j);
                }

                n+=1;
            }}}}

    return manhatten_dis;
    }

int main()
{
Node state;
int gridSize = 3;
int initial_state[3][3] = {{2, 8 ,3},
                           {1, 6, 4},
                           {7, 0, 5}};


int goal_state[3][3] =    {{1, 2 ,3},
                           {8, 0, 4},
                           {7, 6, 5}};    //h1 = 6 , and h2 = 12
for (int m = 0; m < gridSize; m++)
	{
		for (int n = 0; n < gridSize; n++)
		{
			state.A[m][n] = initial_state[m][n];
            cout<<"comp: "<<state.A[m][n]<<endl;
		}
	}
	



int h2, h1, match;
h2 = manhatten_cost(initial_state, goal_state);
h1 = misplaced_tiles(initial_state, goal_state);
match = matching_check(initial_state, goal_state);
bool explored ;
if (match > 0)
{
    explored = false;
}
else{
    explored = true;
}
// cout<<"match: "<<match<<endl;
// cout<<"explored: "<<explored<<endl;
cout<<"h2: "<<h2<<endl;
cout<<"h1: "<<h1<<endl;


// printing the multi dimensional array                                                  
 for(int a = 0; a < 3; a++)
  {
    for(int b = 0; b < 3; b++)
    {
    //   cout << state.A[a][b] << " ";
    }
    cout << endl;
  } 
    return 0;
}