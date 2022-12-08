//
// Created by subangkar on 11/25/18.
//

#ifndef NPUZZLE_NODE_H
#define NPUZZLE_NODE_H
#define BOARD_SQ_SIZE 3
#define PRINT_W 3

//#include<bits/stdc++.h>
#include <iostream>
#include <iomanip>
#include <string>
#include <vector>
#include <map>
#include <queue>
#include <algorithm>
#include <cmath>
#include <cstdlib>
#include <cstring>

#define RIGHT 0
#define LEFT 1
#define DOWN 2
#define UP 3

typedef int direction_t;
typedef int8_t puzzle_t;

using namespace std;

int dirX[4] = {0, 0, 1, -1}; // RIGHT-LEFT-DOWN-UP
int dirY[4] = {1, -1, 0, 0}; // RIGHT-LEFT-DOWN-UP



class Node {
public:
	puzzle_t **A = nullptr;
	bool emptyNode = true;
	static int boardSqSize;

	friend ostream &operator<<(ostream &os, const Node &node);

	Node() {
		emptyNode = true;
		A = new puzzle_t *[boardSqSize];
		for (int i = 0; i < boardSqSize; ++i) {
			A[i] = new puzzle_t[boardSqSize];
			memset(A[i], 0, boardSqSize * sizeof(A[0][0]));
		}
	}


	Node(const Node &node) {
		this->~Node();
//		emptyNode = false;
		this->emptyNode = node.emptyNode;
		A = new puzzle_t *[boardSqSize];
		for (int i = 0; i < boardSqSize; ++i) {
			A[i] = new puzzle_t[boardSqSize];
		}
		for (int i = 0; i < boardSqSize; i++) {
			for (int j = 0; j < boardSqSize; j++) {
				A[i][j] = node.A[i][j];
			}
		}
	}

	Node &operator=(const Node &node) {
		this->~Node();
		this->emptyNode = node.emptyNode;
		A = new puzzle_t *[boardSqSize];
		for (int i = 0; i < boardSqSize; ++i) {
			A[i] = new puzzle_t[boardSqSize];
		}
		for (int i = 0; i < boardSqSize; i++) {
			for (int j = 0; j < boardSqSize; j++) {
				A[i][j] = node.A[i][j];
			}
		}
		return *this;
	}

	~Node() {
		if (A == nullptr) return;
		for (int i = 0; i < boardSqSize; ++i) {
			delete A[i];
		}
		delete[] A;
		A = nullptr;
	}

	bool operator==(const Node &right) const {
		for (int i = 0; i < boardSqSize; i++)
			for (int j = 0; j < boardSqSize; j++)
				if (A[i][j] != right.A[i][j]) return false;
		return true;
	}

	bool operator!=(const Node &right) const {
		return !(*this == right);
	}

	bool operator<(const Node &right) const {
		for (int i = 0; i < boardSqSize; i++) {
			for (int j = 0; j < boardSqSize; j++) {
				if (A[i][j] < right.A[i][j]) return true;
				else if (A[i][j] == right.A[i][j]) continue;
				else return false;
			}
		}
		return false;
	}

	bool isSolveAble() {

		int blank_row_no = -1;
		vector<int> arr;
		for (int i = 0; i < boardSqSize; i++)
			for (int j = 0; j < boardSqSize; j++) {
				if (A[i][j])
					arr.push_back(A[i][j]);
				else
					blank_row_no = i;
			}
		int invCount = getInvCount(arr);
		bool boardSizeOdd = static_cast<bool>(boardSqSize & 1);
//		cout << boardSizeOdd << " " << blank_row_no << " " << invCount << endl;
		if (boardSizeOdd && !(invCount & 1)) // odd-board & even-inversions
			return true;
		else if (!boardSizeOdd && ((blank_row_no + getInvCount(arr)) & 1)) // even-board & odd-sum
			return true;
		return false;
	}


	static int getInvCount(const vector<int> &arr) {
		int inv_count = 0;
		for (int i = 0; i < arr.size() - 1; i++)
			for (int j = i + 1; j < arr.size(); j++)
				if (arr[i] > arr[j])
					inv_count++;

		return inv_count;
	}

	// not works donno why not
	Node getNode(int direction, int zX = -1, int zY = -1) {
		if (A == nullptr || direction > 3)
			return *this;

		if (zX == -1 || zY == -1) {
			if (!getZeroPos(*this, zX, zY))
				return Node();
		}

		int zXnew = zX + dirX[direction];
		int zYnew = zY + dirY[direction];

		if (zXnew < 0 || zYnew < 0 || zXnew >= Node::boardSqSize || zYnew >= Node::boardSqSize)
			return Node();

		Node v = *this;
//		cout << v;
		swap(v.A[zX][zY], v.A[zXnew][zYnew]);
		return v;
	}

	static bool getZeroPos(const Node &node, int &zX, int &zY) {
		zX = zY = -1;
		for (int i = 0; i < Node::boardSqSize; i++) {
			for (int j = 0; j < Node::boardSqSize; j++)
				if (!node.A[i][j]) {
					zX = i, zY = j;
					return true;
				}
		}
		return false;
	}

	static int oppositeDirection(int direction) {
		switch (direction) {
			case LEFT:
				return RIGHT;
			case RIGHT:
				return LEFT;
			case UP:
				return DOWN;
			case DOWN:
				return UP;
			default:
				return EOF;
		}
	}

	bool isEmptyNode() const {
		return emptyNode;
	}
};

int Node::boardSqSize = 0;

ostream &operator<<(ostream &os, const Node &node) {
	if (!node.A) return os;
	for (int i = 0; i < Node::boardSqSize; i++) {
		for (int j = 0; j < Node::boardSqSize; j++)
			if (node.A[i][j])
				os << setw(PRINT_W) << (static_cast<int>(node.A[i][j])) << " ";
			else
				os << setw(PRINT_W) << "  " << " ";
		os << endl;
	}
	os << " ----------- " << std::endl;
	return os;
}

#endif //NPUZZLE_NODE_H
