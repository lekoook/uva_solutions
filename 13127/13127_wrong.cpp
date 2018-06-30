/******************************************************************************
  CS2040C AY2017/18 Semester 2
  13127.cpp
  This program 
  Lee Kok Teng
  C04
  ****************************************************************************/

#include <iostream>
#include <vector>
#include <set>
#include <utility>
#include <algorithm>
#include <unordered_set>
#include <unordered_map>

#define INF 2000000000

using namespace std;

// arg0: weight to this node
// arg1: index of this node
typedef pair<int, int> nodePair;

vector< vector<nodePair> > adjList;
vector<int> distanceVect;
vector<int> banksVect;
unordered_set<int> policeVect;
unordered_map<int, set<int> > ans;
set<nodePair> pq;

int explore(int source);

void printL() {
	int count = 0;

}

int main(void) {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL); cout.tie(NULL);
	int sites, connections, banks, pStations;
	int node1, node2, weight;
	
	while (cin >> sites >> connections >> banks >> pStations, !cin.eof()) {
		// Reset and initialise
		adjList.assign(sites, vector<nodePair>(0));
		banksVect.clear();
		policeVect.clear();
		pq.clear();
		
		set<nodePair> originPQ;
		
		// Read in the graph connections
		for (int i = 0; i < connections; i++) {
			cin >> node1 >> node2 >> weight;
			adjList[node1].push_back(make_pair(weight, node2));
			adjList[node2].push_back(make_pair(weight, node1));
			originPQ.insert(make_pair(INF, node1));
			originPQ.insert(make_pair(INF, node2));
		}
		
		// Read in the bank nodes
		for (int i = 0; i < banks; i++) {
			cin >> node1;
			banksVect.push_back(node1);
		}
		
		// Read in the police station nodes
		for (int i = 0; i < pStations; i++) {
			cin >> node1;
			policeVect.insert(node1);
		}
		
		// For each bank, run Djikstra to all nodes
		// Find the police station node with the shortest path
		ans.clear();
		int distance = INF, highest = -1;
		for (int j = 0; j < banks; j++) {
			distance = INF;
			distanceVect.assign(sites, INF);
			pq = originPQ;
			distance = explore(banksVect[j]);
			
			if (distance > highest) {
				highest = distance;
				ans.clear();
				ans[distance].insert(banksVect[j]);
			}
			else if (distance == highest) {
				ans[distance].insert(banksVect[j]);
			}
		}

		// Find the banks with the highest minimum time from the police
		cout << (int)ans[highest].size() << " ";
		if (highest == INF) cout << "*" << endl;
		else cout << highest << endl;
		for (auto it : ans[highest]) {
			cout << it << " ";
		}
		cout << endl;
	}	
	return 0;
}

// Explore from one police station to another bank with Djikstra
// Return the distance
int explore(int source) {
	int lowest = INF;
	int policeCount = (int)policeVect.size();

	distanceVect[source]= 0;
	
	pq.erase(make_pair(INF, source));
	pq.insert(make_pair(0, source));
	
	nodePair current;
	int node, sum, neighbour;
	
	while (!pq.empty()) {
		if (policeCount <= 0) break;
		current = *(pq.begin());
		pq.erase(current);
		node = current.second;
		
		if (policeVect.count(node) > 0 && current.first < lowest) {
			lowest = current.first;
			policeCount--;
		}

		// Go through all the node's neighbours
		for (int i = 0; i < (int)adjList[node].size(); i++) {
			neighbour = adjList[node][i].second;
			// If the sum of the current node distance and the weight to
			// the neighbour node is lesser than the neighbour's current
			// node distance, relax this edge
			sum = distanceVect[node] + adjList[node][i].first;
			
			if (sum < distanceVect[neighbour]) {
				pq.erase(make_pair(distanceVect[neighbour], neighbour));
				pq.insert(make_pair(sum, neighbour));
				distanceVect[neighbour] = sum;
			}
		}
	}
	
	return lowest;
}
