/******************************************************************************
  CS2040C AY2017/18 Semester 2
  336.cpp
  This program 
  Lee Kok Teng
  C04
  ****************************************************************************/

#include <bits/stdc++.h>

#define INF 1000000
using namespace std;

vector< pair<int, vector<int> > > adjList;
unordered_map<int, int> nodesMap;
vector< pair<int, int> > queries;
vector<int> distancesVect;

int reachableNodes = 0;

void searchNodes(int source, int ttl);

void printL() {
	cout << "adjList/distances:" << endl;
	for (auto &it : adjList) {
		cout << it.first << ", distance = " << distancesVect[nodesMap[it.first]] << ":";
		for (auto &it2 : it.second) {
			cout << " " << it2;
		}
		cout << endl;
	}
}

int main(void) {
	int edges, nodeU, nodeV, startNode, ttl;
	int caseCount = 1;
	
	// Reset all
	
	// Keep reading for the number of edges
	while (cin >> edges) {
		// Read all edges
		adjList.clear();
		nodesMap.clear();
		for (int i = 0; i < edges; i++) {
			cin >> nodeU >> nodeV;
			int index;
			// Check if nodeU already exists
			if (nodesMap.count(nodeU) > 0) {
				index = nodesMap[nodeU];
				adjList[index].second.push_back(nodeV);
			}
			else {
				adjList.push_back(make_pair(nodeU, vector<int>()));
				distancesVect.push_back(INF);
				index = (int)adjList.size() - 1;
				nodesMap[nodeU] = index;
				adjList[index].second.push_back(nodeV);
			}
			
			// Check if nodeV already exists
			if (nodesMap.count(nodeV) > 0) {
				index = nodesMap[nodeV];
				adjList[index].second.push_back(nodeU);
			}
			else {
				adjList.push_back(make_pair(nodeV, vector<int>()));
				distancesVect.push_back(INF);
				index = (int)adjList.size() - 1;
				nodesMap[nodeV] = index;
				adjList[index].second.push_back(nodeU);
			}
		}
		
		// Read all queries
		queries.assign(0, pair<int, int>());
		cin >> startNode >> ttl;
		while (startNode || ttl) {
			queries.push_back(make_pair(startNode, ttl));
			cin >> startNode >> ttl;
		}

		// Run BFS and output results		
		for (auto &it : queries) {
			int nodesCount = 0;
			reachableNodes = 1;
			
			searchNodes(it.first, it.second);
			nodesCount = nodesMap.size() - reachableNodes;
			cout << "Case " << caseCount << ": " << nodesCount << " nodes not reachable from node " << it.first << " with TTL = " << it.second << "." << endl;
			caseCount++;
		}
	}
	
	return 0;
}

void searchNodes(int source, int ttl) {
	queue<int> que;
	que.push(source);
	int current;
	int index;
	distancesVect.assign((int)nodesMap.size(), INF);
	distancesVect[nodesMap[source]] = 0;
	
	while (!que.empty()) {
		current = que.front();
		index = nodesMap[current];
		
		// Go through all the neighbours
		for (int i = 0; i < (int)adjList[index].second.size(); i++) {
			int idx = nodesMap[adjList[index].second[i]];
			if (distancesVect[idx] == INF) {
				distancesVect[idx] = distancesVect[index]+1;
				que.push(adjList[index].second[i]);
				if (distancesVect[idx] <= ttl) reachableNodes++;
			}
		}
		
		que.pop();
	}
}
