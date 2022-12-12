/* A* search algorithm for solving 8 puzzling problem using Hammming and Manhatten cost

Author: Muhammad Faizan
Registration: 
Subject: Artifical intelligence
*/

// add some necceassry packages to run this file ..
#include "node.h"
#include "AStar.h" 
#include <chrono>
#define MAX 105


void showProgress(aStarSearchAlgorithm &eightPuzzleSolver, const Node &Initial, const Node &Target) {
	auto now = Target;

	//show the progress for search algorithm.
	vector<Node> solPath;
	while (eightPuzzleSolver.explored[now].parent_ != EOF) {
		solPath.push_back(now);
		now = now.getNode(eightPuzzleSolver.explored[now].parent_);
	}
	solPath.push_back(Initial);
	reverse(solPath.begin(), solPath.end());
	for (auto &i : solPath) cout << i;
}

void runSearchAlgorithm(const Node &Initial, const Node &Target, int h, bool showProg = true) {
    /*run A* search algorithm on initial and goal states given the heuristic
	if showProg is true then print the solution.*/
	auto *eightPuzzleSearch = new aStarSearchAlgorithm();
	eightPuzzleSearch->setHeuristic(h);
	auto tic = chrono::steady_clock::now();
	int nExpanded = eightPuzzleSearch->AStarSearch(Initial, Target);
	auto toc = chrono::steady_clock::now();

	auto duration = toc - tic;
	cout << "Number of depth Levels (steps): " << (int) eightPuzzleSearch->explored[Target].cost_ << endl;
	cout << "Number of Nodes Explored: " << nExpanded << endl;
	cout << "Number of Nodes Expanded: " << eightPuzzleSearch->openedTotal << endl;
	cout << "Number of Nodes Inserted: " << eightPuzzleSearch->nInserted << endl;
	cout << "Maximum possible depth for the soultion: " << eightPuzzleSearch->maximum_depth << endl;
	cout << "Duration of the search: " << chrono::duration<double, milli>(duration).count() << "ms" << endl;
	cout << endl;
	fflush(stdout);

	if (showProg) showProgress(*eightPuzzleSearch, Initial, Target);
	delete eightPuzzleSearch;
}




int** get_state(unsigned height, unsigned width)
    { 
      int** initial_state = 0;
      initial_state = new int*[height];
      cout<<"\nInital State Input:\n";
	  for(int i=0; i<height; i++)
	  { 
        initial_state[i] = new int[width];
	  	for(int j=0; j<width; j++)
	  	{
	  		cout<<"\ns["<<i<<"]["<<j<<"]=  ";
	  		cin>>initial_state[i][j];
		}
	  } 
      
      return initial_state;
    }

int main() {
	/*All the code goes here, it will execute our A* search algoirthm for 8 puzzle problem
	goal state and initial state of the problem will be set here. Then running
	the search algoritm will expand the tree to search for the solution. In this case,
	I use two types of heuristics, the first one is Hamming heuristic (h1) and the second
	one is Manhatten heuristic (h2), both of them are used to measure the estimated cost for
	reaching to the goal state
	
	the cost is given by:
	f = g + h
	where g is the cost from the initial state to the current node where h is the estimated
	cost such as hamming or manhatten cost. */

    //--------------------------------------------------------------------------------------
	// read from the filed, and write our output to the file 
	// freopen("input_8puzzle.txt", "r", stdin);
	// freopen("output_8puzzle.txt", "w", stdout);
	// choose grid size, in this case it's 3 (3x3 board)
	int gridSize = 3; // for 8 puzzle problem we have 3x3 grid, for other you can specify NXN grid
	Node::boardSqSize = gridSize;
    
	// declare Target node as the object of class Node and initialize the goal state, we can 
	// modify the goal state as per the requirement.
	Node Target;
	// any gaol state could be assigned. 
	int goal_state[3][3] =  {{1, 2 ,3},
                             {4, 5, 6},
                             {7, 8, 0}};

    for (int m = 0; m < gridSize; m++)
	{
		for (int n = 0; n < gridSize; n++)
		{
			Target.A[m][n] = goal_state[m][n];
		}
	}
	
    // setting up the initial node and assigning it the initial state of the problem
	Node Initial;
	// any state can be assigned as initial state
	// int initial_state[3][3] = {{1, 8 ,2},   // solution exists check ..
    //                            {0, 4, 3},
    //                            {7, 6, 5}};

	//get initial state from the user...
	int height = 3; // height of grid
    int width = 3; // width of the grid
    int** initial_state = get_state(height, width);
	// print the inital state 
    for (int h = 0; h < height; h++)
      {
            for (int w = 0; w < width; w++)
            {
                //   printf("%i,", my2DArray[h][w]);
                cout<<initial_state[h][w]<<" ";
				Initial.A[h][w] = initial_state[h][w];
            }
            cout<<"\n";
      }
	//-----------------------------------------------------------------------						   
    //  int initial_state[3][3] = {{8, 1, 3},
    //                             {0, 4, 5}, // when no solutin exists check ...
    //                             {7, 6, 2}};
	//  for (int i = 0; i < gridSize; i++)
	// {
	// 	for (int j = 0; j < gridSize; j++)
	// 	{
	// 		Initial.A[i][j] = initial_state[i][j];
	// 	}
	// }
	//--------------------------------------------------------------------------

	cout << "Initial State: \n" << Initial;
	cout << "Goal State: \n" << Target;
    
	// pick the heursitic type for h estimation by default I sat it to Manhatten cost
	string choose_heuristic = "h2";

    // check whether the solution exists or not, if it does then run the search algorithm 
	// to find the goal state.
	if (!Initial.isSolveAble()) {
		cout << "Solution doesn't exists!!!!" << endl;

	} 
	// run the algorithm 
	else {
		{
			if (choose_heuristic == "h1")
			{
				cout << "Running Hamming heuristic for h estimation: " << endl;
				runSearchAlgorithm(Initial, Target, H1, true);}
			else{
				cout << "Running Manhatten cost for h estimation: "<<endl;
				runSearchAlgorithm(Initial, Target, H2, true);
			}
		}
	}
}
//the end..
