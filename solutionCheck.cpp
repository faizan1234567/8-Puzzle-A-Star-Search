// C++ program to check if a given instance of 8 puzzle is solvable or not
#include <iostream>
using namespace std;

// A utility function to count inversions in given array 'arr[]'
int getInvCount(int arr[]) {
  int inv_count = 0;
  for (int i = 0; i < 9 - 1; i++) {
    for (int j = i + 1; j < 9; j++) {
      // cout<<"i: "<<arr[i]<<endl;
      // cout<<"j: "<<arr[j]<<endl;
      if (arr[j] && arr[i] && arr[i] > arr[j]) {
        // cout << arr[j] << endl;
        inv_count++;
      }
    }
  }
  cout << "inverse count:" << inv_count << endl;
  return inv_count;
}

// This function returns true if given 8 puzzle is solvable.
bool isSolvable(int puzzle[3][3]) {
  // Count inversions in given 8 puzzle
  int invCount = getInvCount((int *)puzzle);

  // return true if inversion count is even.
  return (invCount % 2 == 0);
}

/* Driver program to test above functions */
int main() {
  int puzzle[3][3] = {{8, 1, 3},
                      {0, 4, 5}, // Value 0 is used for empty space
                      {7, 6, 2}};
  isSolvable(puzzle) ? cout << "Solvable" : cout << "Not Solvable"<<endl;
  return 0;
}