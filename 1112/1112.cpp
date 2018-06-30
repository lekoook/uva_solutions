/******************************************************************************
  CS2040C AY2017/18 Semester 2
  1112.cpp
  This program 
  Lee Kok Teng
  C04
  ****************************************************************************/

#include <iostream>
#include <vector>
#include <set>

#define INF 1000000000

using namespace std;

// arg0: neighbour node number
// arg1: edge weight to the neighbour
typedef pair<int, int> nodePair;
// arg0: current time to get to this node from source
// arg1: node number
typedef pair<int, int> timePair;

vector< vector<nodePair> > adjList;
vector<int> timeVect;

set<timePair> pq;

void explore(int source);

void printL() {
	int count = 0;
	cout << "adjList: " << endl;
	for (auto &it : adjList) {
		cout << count << ":";
		count++;
		for (auto &it2 : it) {
			cout << " " << it2.first << "," << it2.second;
		}
		cout << endl;
	}
}

int main(void) {
	int cases, cells, exitCell, timeLimit, connections;
	int node1, node2, weight;
	
	cin >> cases; cin.ignore(10000, '\n');
	for (int i = 0; i < cases; i++) {
		cin >> cells >> exitCell >> timeLimit >> connections;
		
		// Reset and initialise
		adjList.assign(cells, vector<nodePair>(0));
		timeVect.assign(cells, INF);
		
		// Read in the graph connections
		for (int j = 0; j < connections; j++) {
			cin >> node1 >> node2 >> weight;
			adjList[node2-1].push_back(make_pair(node1-1, weight));
		}
		//printL();
		// Run Dijkstra from the the end cell to all other cells
		explore(exitCell-1);
		
		// Find all the cells that have lower or equal time limit than 
		// the given timeLimit. This means all those cells are valid.
		int count = 0;
		for (auto &it : timeVect) {
			if (it <= timeLimit) count++;
		}
		if (i == cases-1) 
			cout << count << endl;
		else
			cout << count << endl << endl;
	}
	
	return 0;
}

void explore(int source) {
	timeVect[source] = 0;
	// Push all nodes to pq
	pq.clear();
	for (int i = 0; i < (int)timeVect.size(); i++) {
		if (i == source)
			pq.insert(make_pair(0, i));
		else
			pq.insert(make_pair(INF, i));
	}
	timePair current;
	int node, sum;
	
	while (!pq.empty()) {
		current = *(pq.begin());
		pq.erase(pq.begin());
		node = current.second;
		
		// Go through all its neighbours and relax them
		for (int i = 0; i < (int)adjList[node].size(); i++) {
			sum = timeVect[node] + adjList[node][i].second;
			// If the computed time is lesser than neighbour's
			// assigned value, update the pq and timeVect.
			if (sum < timeVect[adjList[node][i].first]) {
				pq.erase(pq.find(make_pair(timeVect[adjList[node][i].first],  adjList[node][i].first)));
				timeVect[adjList[node][i].first] = sum;
				pq.insert(make_pair(sum, adjList[node][i].first));
			}
		}
	}
}
