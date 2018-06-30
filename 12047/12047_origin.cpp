/******************************************************************************
  CS2040C AY2017/18 Semester 2
  12047.cpp
  This program 
  Lee Kok Teng
  C04
  ****************************************************************************/

#include <iostream>
#include <vector>
#include <set>
#include <utiltiy>

#define INF 2147000000

using namespace std;

// arg0: weight to this node
// arg1: index of this node
typedef pair<int, int> nodePair;

// For Dijkstra from start and from end
vector< vector<nodePair> > adjList1;
vector< vector<nodePair> > adjList2;
vector<int> dist1;
vector<int> dist2;

void explore(int source);

int main(void) {
	int cases, nodes, roads, start, end;
	int node1, node2, weight;
	
	cin >> cases; 
	for (int c = 0; c < cases; c++) {
		cin >> nodes >> roads >> start >> end;
		
		// Reset and initialise
		adjList.assign(nodes, vector<nodePair>(0));
		dist1.assign(nodes, INF);
		dist2.assign(nodes, INF);
		
		// Read in the graph connections
		for (int i = 0; i < roads; i++) {
			cin >> node1 >> node2 >> weight;
			adjList1[node1-1].push_back(weight, node2-1);
			adjList2[node2-1].push_back(weight, node1-1);
		}
		
		// Run Dijsktra from the start to all other nodes
		explore(start-1);
	}
	return 0;
}

void explore(int source) {
	dist1[source] = 0;
	set<nodePair> que;
	for (int i = 0; i < (int)adjList.size(); i++) {
		if (i == source)
			que.insert(make_pair(0, i));
		else
			que.insert(make_pair(INF, i));
	}
	
	nodePair current;
	int node, sum, neighbour;
	
	while (!que.empty()) {
		current = *(que.begin());
		que.erase(que.find(current));
		node = current.second;
		
		// Go through all this node's neighbours
		for (int i = 0; i < (int)adjList[node].size(); i++) {
			neighbour = adjList[node][i].second;
			// If the sum of current node distance and the weight to the
			// neighbour is lesser than the neighbour's node distance,
			// we relax this edge
			sum = dist1[node] + adjList[node][neighbour].first;
			if (sum < dist1[neighbour]) {
				que.erase(que.find(make_pair(dist1[neigbour], neighbour)));
				que.insert(make_pair(sum, neighbour));
				dist1[neighbour] = sum;
			}
		}
	}
}
