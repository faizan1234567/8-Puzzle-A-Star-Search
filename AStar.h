//Author Faizan
#include <set>
#include "node.h" 



#define H2 2 // manhatten cost 
#define H1 1 // hamming cost

#define DEPTH_LIMIT 1000 // maximum allowed depth
#define NODES_LIMIT 200000000 // nodes limit (no more than that)

#define cost_ cost
#define parent_ parent


struct NodeData {
	bool isDead; // further can't explored
	int cost;   // g cost paramets
	int parent;  // parent cost

	bool operator==(const NodeData &node) const {
		return parent == node.parent &&
		       cost == node.cost;
	}

	bool operator!=(const NodeData &node) const {
		return !(node == *this);
	}
};


class aStarSearchAlgorithm {
public:
	map<Node, NodeData> explored;//

	size_t openedTotal;
	int maximum_depth;
	int nInserted;

	int heuristicKind = 2;

	bool isCorrect(int w, int h) { return w >= 0 && h >= 0 && w< Node::boardSqSize && h < Node::boardSqSize; }

	static int h1(const Node &current_state, const Node &goal_state) {
		int dissmilarity = 0;
		for (int m = 0; m < Node::boardSqSize; m++)
			for (int n = 0; n < Node::boardSqSize; n++)
				if (current_state.A[m][n] && current_state.A[m][n] != goal_state.A[m][n]) dissmilarity++;
		return dissmilarity;
	}

	static int h2(const Node &current_state, const Node &goal_state) {
		int cost = 0;
		puzzle_t pR[(Node::boardSqSize * Node::boardSqSize) + 1];
		puzzle_t pC[(Node::boardSqSize * Node::boardSqSize) + 1];
		for (int i = 0; i < Node::boardSqSize; i++) {
			for (int j = 0; j < Node::boardSqSize; j++) {
				pR[current_state.A[i][j]] = static_cast<puzzle_t>(i);
				pC[current_state.A[i][j]] = static_cast<puzzle_t>(j);
			}
		
		}
		for (int i = 0; i < Node::boardSqSize; i++)
			for (int j = 0; j < Node::boardSqSize; j++)
				if (goal_state.A[i][j])
					cost += abs(pR[goal_state.A[i][j]] - i) + abs(pC[goal_state.A[i][j]] - j);
		// cout<<"cost: "<< cost <<endl;
		return cost;

	}

	// int h2(const Node &current_state, const Node &goal_state)
    // {
	// 	int manhatten_dis = 0;
	// 	for(int i = 0; i < Node::boardSqSize; i++)
	// 	{
	// 		for (int j = 0; j < Node::boardSqSize; j++)
	// 		{
	// 			int number = current_state.A[i][j]; // return an element to number variable...
	// 			// cout<<"num: "<<number<<endl;
	// 			for (int m = 0; m < Node::boardSqSize; m++)
	// 			{
	// 			int n = 0;
	// 			while (n < Node::boardSqSize)
	// 				{
	// 				int goal_number = goal_state.A[m][n];
	// 				if (goal_number == number)
	// 				{
	// 					manhatten_dis += abs(m - i) + abs(n - j);
	// 				}

	// 				n+=1;
	// 			}}}}
        
    //     cout<<"h2: "<<manhatten_dis<<endl;
	// 	return manhatten_dis;
    // }

	

	double heuristicSelection(const Node &current_state, const Node &goal_state) {
		if (heuristicKind == H1) return h1(current_state, goal_state);
		if (heuristicKind == H2) return h2(current_state, goal_state);
		return 0;
	}

	int AStarSearch(const Node &intial_state, const Node &goal_state) {
		int nExplored = 0;
		maximum_depth = 0;
		nInserted = 0;

		priority_queue<pair<double, Node>> priorityList;
		priorityList.push({0, intial_state}); // insert initial state into priority queue
		explored[intial_state] = {false, 0, EOF};

		while (!priorityList.empty()) {
			Node current_state = priorityList.top().second;
			priorityList.pop();
			++nExplored;
			NodeData &currentInfo = explored[current_state];
			currentInfo.isDead = true;

			maximum_depth = max(maximum_depth, explored[current_state].cost);

			if (current_state == goal_state) {
				break;
			}

			if (currentInfo.cost > DEPTH_LIMIT) {
				cout << "depth limit reached" << endl << current_state;
				break;
			}


			if (explored.size() > NODES_LIMIT) {
				cout << "Nodes limit reached" << endl << current_state;
				break;
			}

			int blankX = -1, blankY = -1;
			Node::getZeroPos(current_state, blankX, blankY);

			for (direction_t action = 0; action < 4; action++) {
				int blankXUpdated = blankX + dirX[action]; // (1 + 0) = 1
				int blankYUpdated = blankY + dirY[action]; // (1 + 1) = 2 (1, 2) --> right
				if (isCorrect(blankXUpdated, blankYUpdated)) {
					Node current_state_copy = current_state;
					swap(current_state_copy.A[blankX][blankY], current_state_copy.A[blankXUpdated][blankYUpdated]);

					bool isVisited = explored.find(current_state_copy) != explored.end();
					if (isVisited && explored[current_state_copy].isDead) continue;
					double newCost = currentInfo.cost + 1;
					if (!isVisited || newCost < explored[current_state_copy].cost) { 
						++nInserted;
						explored[current_state_copy] = {false, static_cast<int>(newCost), Node::oppositeDirection(action)};
						double priority = newCost + heuristicSelection(current_state_copy, goal_state);
						priorityList.push({-priority, current_state_copy});
					}
				}
			}

		}
		openedTotal = explored.size();
		return nInserted;
	}

	void setHeuristic(int heuristic = H1) {
		heuristicKind = heuristic;
	}

	virtual ~aStarSearchAlgorithm() {
		heuristicKind = 0;
		explored.clear();
	}
};


