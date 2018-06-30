/******************************************************************************
  CS2040C AY2017/18 Semester 2
  12878.cpp
  This program 
  Lee Kok Teng
  C04
  ****************************************************************************/

#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <map>

#define INF 2000000000

using namespace std;

// arg0: weight to the neighbour
// arg1: number of neighbour node
typedef pair<int, int> nodePair;

vector< vector<nodePair> > adjList;
vector<int> distVect;
map< int, set<nodePair> > shortestGraph;
vector<int> backArray;
vector< vector<int> > paths;
int totalDistance = 0;

void explore(int source);
void exploreDist(int source, int end);

void printB() {
	int count = 0;
	cout << "backArray:" << endl;
	for (auto &it : backArray) {
		cout << count << ":" << it << endl;
		count++;
	}
}

void printL() {
	//int count = 0;
	/*
	cout << "distVect: ";
	for (auto &it : distVect) {
			cout << it << " ";
	}
	cout << endl;
	*/
	cout << "shortestGraph:" << endl;
	for (auto &it : shortestGraph) {
		cout << it.first << ":";
		for (auto &it2 : it.second) {
			cout << " " << it2.first << "," << it2.second;
		}
		cout << endl;
	}
}

int main(void) {
	int points, trails;
	int node1, node2, weight;
	
	while (cin >> points >> trails, !cin.eof()) {
		// Reset and initialise
		adjList.assign(points, vector<nodePair>(0));
		distVect.assign(points, INF);
		shortestGraph.clear();
		totalDistance = 0;
		
		// Read in the graph connections
		for (int i = 0; i < trails; i++) {
			cin >> node1 >> node2 >> weight;
			if (node1 != node2) {
				adjList[node1].push_back(make_pair(weight, node2));
				adjList[node2].push_back(make_pair(weight, node1));
			}
			else {
				adjList[node1].push_back(make_pair(weight, node2));
			}
		}
		for (auto &it : adjList) {
			sort(it.begin(), it.end());
		}
		// Run Dijkstra from the highest peak to all other nodes
		explore(0);
	
		// Explore the shortestGraph to get the total distance of all
		// the routes
		backArray.clear();
		paths.clear();
		exploreDist(points-1, 0);
		
		// Output
		totalDistance *= 2;
		cout << totalDistance << endl;
		
		cout << "All shortest routes" << endl;
		for (auto &it : paths) {
			for (auto &it2 : it) {
				cout << it2 << " -> ";
			}
			cout << endl;
		}
		cout << endl << endl;
	}
	
	return 0;
}

void explore(int source) {
	// Set up the priority queue
	set<nodePair> pq;
	distVect[source] = 0;
	for (int i = 0; i < (int)distVect.size(); i++) {
		if (i == source)
			pq.insert(make_pair(0, i));
		else
			pq.insert(make_pair(INF, i));
	}
	
	nodePair current;
	int sum, node;
	
	while (!pq.empty()) {
		current = *(pq.begin());
		pq.erase(pq.begin());
		node = current.second;
		
		// Explore all neighbours
		for (int i = 0; i < (int)adjList[node].size(); i++) {
			int neighbour = adjList[node][i].second;
			// If the distance to the neighbour is lesser and equal than
			// the neighbour's current value, update pq and distVect.
			sum = distVect[node] + adjList[node][i].first;
//			cout << "current node = " << node << " neighbour = " << neighbour << " sum = " << sum << " neighsum = " << distVect[neighbour] << endl;
			if (sum <= distVect[neighbour]) {				
				// This will form a graph of only the routes required
				if (sum < distVect[neighbour]) {
					shortestGraph[neighbour].clear();
				}
					
				shortestGraph[neighbour].insert(make_pair(adjList[node][i].first, node));

				pq.erase(pq.find(make_pair(distVect[neighbour], neighbour)));
				pq.insert(make_pair(sum, neighbour));
				distVect[neighbour] = sum;
			}
		}
	}
}

// Run DFS from the source and add the backtracking distance
void exploreDist(int source, int end) {
	backArray.push_back(source);
	
	// If the source is equal to end, we have reached the target point
	if (source == end) {
		paths.push_back(vector<int>(backArray.rbegin(), backArray.rend()));
	}
	
	// Go through all neighbours
	for (auto &it : shortestGraph[source]) {
		exploreDist(it.second, end);
	}
	
	backArray.pop_back();
}
