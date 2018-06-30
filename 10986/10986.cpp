/******************************************************************************
  CS2040C AY2017/18 Semester 2
  10986.cpp
  This program 
  Lee Kok Teng
  C04
  ****************************************************************************/

#include <iostream>
#include <vector>
#include <set>

#define INF 1000000000

using namespace std;

// arg0: weight to the neighbour
// arg1: neighbour's node number
typedef pair<int, int> nodePair;

vector< vector<nodePair> > adjList;
vector<int> timeVect;

void explore(int source);

int main(void) {
	int cases, servers, connections, start, end;
	int node1, node2, weight;
	int count = 1;
	
	cin >> cases;
	
	for (int i = 0; i < cases; i++) {
		cin >> servers >> connections >> start >> end;
		
		// Reset and initialise
		adjList.assign(servers, vector<nodePair>(0));
		timeVect.assign(servers, INF);
		
		// Read in the graph connections
		for (int j = 0; j < connections; j++) {
			cin >> node1 >> node2 >> weight;
			adjList[node1].push_back(make_pair(weight, node2));
			adjList[node2].push_back(make_pair(weight, node1));
		}
		
		// Run Dijkstra from start to end node
		explore(start);
		
		// Output results
		if (timeVect[end] == INF)
			cout << "Case #" << count++ << ": unreachable" << endl;
		else
			cout << "Case #" << count++ << ": " << timeVect[end] << endl;
	
	}
	
	return 0;
}

void explore(int source) {
	set<nodePair> pq;
	timeVect[source] = 0;
	for (int i = 0; i < (int)timeVect.size(); i++) {
		if (i == source)
			pq.insert(make_pair(0, i));
		else
			pq.insert(make_pair(INF, i));
	}
	
	nodePair current;
	int node, sum;
	
	while (!pq.empty()) {
		current = *(pq.begin());
		pq.erase(pq.begin());
		node = current.second;
		
		// Go through all the neighbours
		for (int i = 0; i < (int)adjList[node].size(); i++) {
			// If the computed distance to neighbour is greater than
			// the neighbour's distance, update pq and timeVect
			sum = timeVect[node] + adjList[node][i].first;
			if (sum < timeVect[adjList[node][i].second]) {
				pq.erase(pq.find(make_pair(timeVect[adjList[node][i].second], adjList[node][i].second)));
				timeVect[adjList[node][i].second] = sum;
				pq.insert(make_pair(sum, adjList[node][i].second));
			}
		}
	}
}
