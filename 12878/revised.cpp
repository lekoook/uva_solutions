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

#define INF 2000000000

using namespace std;

// arg0: weight to the neighbour
// arg1: number of neighbour node
typedef pair<int, int> nodePair;

vector< vector<nodePair> > adjList;
vector<int> distVect1;
vector<int> distVect2;

void explore(int source, vector<int> *distVect);

int main(void) {
	int points, trails;
	int node1, node2, weight;
	
	while (cin >> points >> trails, !cin.eof()) {
		// Reset and initialise
		adjList.assign(points, vector<nodePair>(0));
		distVect1.assign(points, INF);
		distVect2.assign(points, INF);
		
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

		// Run Dijkstra from the highest peak to all other nodes
		explore(0, &distVect1);
		explore(points-1, &distVect2);
	
		// Check for each edge, if it belongs to the shortest path
		int shortestDist = distVect1[points-1];
		int totalDistance = 0;
		for (int i = 0; i < points; i++) {
			int x = i;
			for (int j = 0; j < (int)adjList[i].size(); j++) {
				int y = adjList[i][j].second;
				int weight = adjList[i][j].first;
				if (distVect1[x] + weight + distVect2[y] == shortestDist) {
					totalDistance += weight;
				}
			}
		}
	
		// Output
		totalDistance *= 2;
		cout << totalDistance << endl;
	}
	
	return 0;
}

void explore(int source, vector<int> *distVect) {
	// Set up the priority queue
	set<nodePair> pq;
	(*distVect)[source] = 0;
	for (int i = 0; i < (int)distVect->size(); i++) {
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
			sum = (*distVect)[node] + adjList[node][i].first;
//			cout << "current node = " << node << " neighbour = " << neighbour << " sum = " << sum << " neighsum = " << distVect[neighbour] << endl;
			if (sum <= (*distVect)[neighbour]) {				
				pq.erase(pq.find(make_pair((*distVect)[neighbour], neighbour)));
				pq.insert(make_pair(sum, neighbour));
				(*distVect)[neighbour] = sum;
			}
		}
	}
}
