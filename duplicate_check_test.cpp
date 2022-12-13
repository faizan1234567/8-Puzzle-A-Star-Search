#include <iostream>
#include <string.h>
using namespace std;
bool duplicate_check(int state[3][3])
{
    int nums[3*3];

    // Copy into 1D array
    memcpy(nums,state,9*sizeof(int));
    

    int i, j;
    bool duplicate = false;
    int size = sizeof(nums)/sizeof(nums[0]);
    for(i = 0; i < size; i++)
    for(j = i+1; j < size; j++)
      if(nums[i] == nums[j]){
        duplicate = true; break;}

    return duplicate;   
}
int main() {
    int a[3][3] = {{1, 2 ,3},
                    {4, 5, 6},
                    {7, 8, 0}};
    bool duplicate;
    duplicate = duplicate_check(a);
    cout<<duplicate<<endl;
    return 0;
}


