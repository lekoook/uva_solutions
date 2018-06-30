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
#include <utility>

#define INF 1000000000

using namespace std;

// arg0: weight to this node
// arg1: index of this node
typedef pair<int, int> nodePair;

// For Dijkstra from start and from end
vector< vector<nodePair> > adjList1;
vector< vector<nodePair> > adjList2;
vector<int> dist1;
vector<int> dist2;

void explore(int source, vector< vector<nodePair> > *adjList, vector<int> *dist);

void printL() {
	int count = 0;
	cout << "adjList1:" << endl;
	for (auto &it : adjList1) {
		cout << count+1 << ":";
		count++;
		for (auto &it2 : it) {
			cout << " " << it2.first << "," << it2.second+1;
		}
		cout << endl;
	}
	count = 0;
	cout << "adjList2:" << endl;
	for (auto &it : adjList2) {
		cout << count+1 << ":";
		count++;
		for (auto &it2 : it) {
			cout << " " << it2.first << "," << it2.second+1;
		}
		cout << endl;
	}
	count = 0;
	cout << "dist1: " << endl;
	for (auto &it : dist1) {
		cout << count+1 << ": " << it << endl;
		count++;
	}
	count = 0;
	cout << "dist2: " << endl;
	for (auto &it : dist2) {
		cout << count+1 << ": " << it << endl;
		count++;
	}
}

int main(void) {
	int cases, nodes, roads, start, end, limit;
	int node1, node2, weight;
	
	cin >> cases; 
	for (int c = 0; c < cases; c++) {
		cin >> nodes >> roads >> start >> end >> limit;
		
		// Reset and initialise
		adjList1.assign(nodes, vector<nodePair>(0));
		adjList2.assign(nodes, vector<nodePair>(0));
		dist1.assign(nodes, INF);
		dist2.assign(nodes, INF);
		
		// Read in the graph connections
		for (int i = 0; i < roads; i++) {
			cin >> node1 >> node2 >> weight;
			adjList1[node1-1].push_back(make_pair(weight, node2-1));
			adjList2[node2-1].push_back(make_pair(weight, node1-1));
		}
		
		// Run Dijsktra from the start to all other nodes
		explore(start-1, &adjList1, &dist1);
		// Run Dijkstra from the end to all other nodes
		explore(end-1, &adjList2, &dist2);
		
		// We go through all the edges, if the weight of that edge
		// summed with the shortest distance from one vertex of that edge
		// to the start point and the shortest distance from the other vertex
		// of that edge to the end point is equals to the shortest distance,
		// ie. dist1[u] + edge_weight + dist2[v] == sp_dist where u->v,
		// we know the edge belongs to one of the possibly many shortest
		// path from the start to the end point. We check for the
		// largest edge weight.
		int x, y, sum;
		int spd = dist1[end-1];	//shortest distance computed
		int largestWeight = -1;
		
		if (spd > limit) {
			cout << "-1" << endl;
			continue;
		}
		
		for (int i = 0; i < nodes; i++) {
			x = i;
			// Check for its outgoing edges
			for (int j = 0; j < (int)adjList1[i].size(); j++) {
				y = adjList1[i][j].second;
				if (dist1[x] + adjList1[i][j].first + dist2[y] < limit) {
					if (adjList1[i][j].first > largestWeight) {
						largestWeight = adjList1[i][j].first;
					}
				}
			}
		}
		//cout << "spd = " << spd << " ";
		cout << largestWeight << endl;
	}
	return 0;
}

void explore(int source, vector< vector<nodePair> > *adjList, vector<int> *dist) {
	(*dist)[source] = 0;
	set<nodePair> que;
	for (int i = 0; i < (int)(*adjList).size(); i++) {
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
		for (int i = 0; i < (int)(*adjList)[node].size(); i++) {
			neighbour = (*adjList)[node][i].second;
			// If the sum of current node distance and the weight to the
			// neighbour is lesser than the neighbour's node distance,
			// we relax this edge
			sum = (*dist)[node] + (*adjList)[node][i].first;
			if (sum < (*dist)[neighbour]) {
				que.erase(que.find(make_pair((*dist)[neighbour], neighbour)));
				que.insert(make_pair(sum, neighbour));
				(*dist)[neighbour] = sum;
			}
		}
	}
}
