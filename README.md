
# A* Search Algorithm for solving 8-Puzzle problem

A* search implementation for 8-puzzle problem in C++. A* search algorithm is
a type of informed search strategy. Informed search algorithm are those that know 
where to look for the solution. A* search uses multiple heuristic to know how far 
the goal is. In this repository, Hamming and Manhatten heuristic are implemented.
A heuristic is a estimated straight line distance to the goal G from a node N. A* 
search uses heuristic value h and cost value g from intial state to estimate the cost
value any level at node t. Mathematically it's given by:

f = g + h
; where h is a heuristic value and g is the cost value to the node.

![A_star_working](https://user-images.githubusercontent.com/61932757/206433479-57d67b6a-5e0f-4fe4-b473-582ccd47cd13.jpg)

## Installation

Installation is pretty staright forward. Follow the instructions below:

```bash
  git clone https://github.com/faizan1234567/8-Puzzle-A-Star-Search.git
  cd 8-Puzzle-A-Star-Star
```
It will work with any C++ IDE/compiler. However, I would recommend running
it in [VS code](https://code.visualstudio.com/). Install the compiler if you have not by following the instructions [here](https://youtu.be/j8nAHeVKL08).

After installing [compiler](https://www.ics.uci.edu/~pattis/common/handouts/mingweclipse/mingw.html) and [VS code](https://code.visualstudio.com/)
run the following command to run the algorithm.
```bash
g++ main.cpp -o main
./main.exe
```
The result will be written to an output .txt file.

## Note
Some intiale state don't converge to the goal state. It is important to check it before
running the algorithm. In this repository, it is implemented in the node class.
In order to understand why some states converge and other don't. Please read [this](https://www.geeksforgeeks.org/check-instance-15-puzzle-solvable/) nice explanation.

Please star the repository, if you use it in your projects or for learning purposes.

## References
[1]. https://blog.goodaudience.com/solving-8-puzzle-using-a-algorithm-7b509c331288

[2]. https://zoo.cs.yale.edu/classes/cs470/materials/aima2010.pdf

[3]. https://www.geeksforgeeks.org/check-instance-8-puzzle-solvable/

[4]. https://github.com/Subangkar/N-Puzzle-Problem-CPP-Implementation-using-A-Star-Search

[5]. https://faramira.com/solving-8-puzzle-problem-using-a-star-search-in-c/
