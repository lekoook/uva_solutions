/******************************************************************************
  CS2040C AY2017/18 Semester 2
  .cpp
  This program 
  Lee Kok Teng
  C04
  ****************************************************************************/

#include <iostream>
#include <vector>
#include <queue>
#include <set>

using namespace std;

vector<int> deltaVect;
vector< set<int> > adjList;

void constructGraph(int start, int end);

void printL() {
	int count = 0;
	cout << "adjList:" << endl;
	for (auto &it : adjList) {
		cout << count << ":";
		for (auto &it2: it) {
			cout << " " << it2;
		}
		count++;
		cout << endl;
	}
}

int main(void) {
	int L, U, R, caseCount = 1;
	int delta;
	
	while (cin >> L >> U >> R) {
		adjList.assign(10000, set<int>());
		deltaVect.assign(0, 0);
		if (L == 0 && R == 0 && U == 0) break;
		// Read in all the possible buttons
		for (int i = 0; i < R; i++) {
			cin >> delta;
			deltaVect.push_back(delta);
		}
		
		// Create the graph given the buttons
		constructGraph(L, U);
		
		printL();
	}
	
	return 0;
}
// Use BFS starting from the given start code
// BFS outwards until the end code is encountered
void constructGraph(int start, int end) {
	queue<int> que;
	que.push(start);
	int current;
	int sum;
	
	while (!que.empty()) {
		current = que.front();
		
		if (current == end) break;
		
		// Go through all the possible buttons
		for (int i = 0; i < (int)deltaVect.size(); i++) {
			sum = (deltaVect[i] + current) % 10000;
			
			que.push(sum);
			cout << "pairing " << current << " with " << sum << endl;
			if (adjList[current].count(sum) > 0 || adjList[sum].count(current) > 0) break;
			adjList[current].insert(sum);
			adjList[sum].insert(current);
		}
		if (adjList[current].count(sum) > 0 || adjList[sum].count(current) > 0) break;
		
		que.pop();
	}
	
}
