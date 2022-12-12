#include <iostream>
using namespace std;


int** get_state(unsigned height, unsigned width)
    { 
      int** initial_state = 0;
      initial_state = new int*[height];
      cout<<"\n2D Array Input:\n";
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
int main(){
   int state[3][3] = {{2, 4, 1},
                      {3, 0, 5},
                      {7, 6, 8}};
    bool duplicate = false;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j<3; j++)
        {
           int value = state[i][j];
           
        }
    }
    return 0;
}