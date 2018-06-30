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
vector<int> policeVect;
set<int> ans;

void explore(int source);

void printL() {
	cout << "distanceVect:" << endl;
	int count = 0;
	for (auto &it : distanceVect) {
		cout << count << ": " << it << endl;
		count++;
	}
}

int main(void) {
	int sites, connections, banks, pStations;
	int node1, node2, weight;
	
	while (cin >> sites >> connections >> banks >> pStations, !cin.eof()) {
		// Reset and initialise
		adjList.assign(sites+1, vector<nodePair>(0));
		banksVect.clear();
		policeVect.clear();
		
		// Read in the graph connections
		for (int i = 0; i < connections; i++) {
			cin >> node1 >> node2 >> weight;
			adjList[node1].push_back(make_pair(weight, node2));
			adjList[node2].push_back(make_pair(weight, node1));
		}
		
		// Read in the bank nodes
		for (int i = 0; i < banks; i++) {
			cin >> node1;
			banksVect.push_back(node1);
		}
		
		// Read in the police station nodes
		for (int i = 0; i < pStations; i++) {
			cin >> node1;
			policeVect.push_back(node1);
			adjList[sites].push_back(make_pair(0, node1));
		}
		
		// We set a super node to all the bank nodes
		// Run Dijkstra from this super node
		// We get the distances of each of every other nodes
		// to a nearest bank node
		ans.clear();
		distanceVect.assign(sites+1, INF);
		int highest = -1;
		explore(sites);
		for (int i = 0; i < banks; i++) {
			if (distanceVect[banksVect[i]] > highest) {
				highest = distanceVect[banksVect[i]];
				ans.clear();
				ans.insert(banksVect[i]);
			}
			else if (distanceVect[banksVect[i]] == highest) {
				ans.insert(banksVect[i]);
			}
		}

		// Find the banks with the highest minimum time from the police
		cout << (int)ans.size() << " ";
		if (highest == INF) cout << "*" << endl;
		else cout << highest << endl;
		int count = ans.size();
		for (auto it : ans) {
			if (count == 1)
				cout << it;
			else
				cout << it << " ";
			count--;
		}
		cout << endl;
	}
	
	return 0;
}

// Explore from one police station to another bank with Djikstra
// Return the distance
void explore(int source) {
	set<nodePair> pq;
	distanceVect[source]= 0;
	
	for (int i = 0; i < (int)adjList.size(); i++) {
		if (i == source)
			pq.insert(make_pair(0, i));
		else
			pq.insert(make_pair(INF, i));
	}
	
	nodePair current;
	int node, sum, neighbour;
	
	while (!pq.empty()) {
		current = *(pq.begin());
		pq.erase(current);
		node = current.second;

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
}
