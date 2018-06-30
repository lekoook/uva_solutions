/******************************************************************************
  CS2040C AY2017/18 Semester 2
  429.cpp
  This program 
  Lee Kok Teng
  C04
  ****************************************************************************/

#include <iostream>
#include <map>
#include <vector>
#include <queue>
#include <sstream>

#define INF 10000

using namespace std;

map<string, vector<string> > adjList;
vector< vector<string> > stringsVect;
vector< pair<string, string> > queries;
map<string, int> distancesMap;

bool compareStr(string left, string right);
int transform(string start, string end);

void printL() {
	cout << "adjList:" << endl;
	for (auto &it : adjList) {
		cout << it.first << ":";
		for (auto &it2 : it.second) {
			cout << " " << it2;
		}
		cout << endl;
	}
	
	cout << "queries:" << endl;
	for (auto &it : queries) {
		cout << it.first << ", " << it.second << endl;
	}
	
	cout << "distances from given source:" << endl;
	for (auto &it : distancesMap) {
		cout << it.first << ":" << it.second << endl;
	}
	cout << endl << endl;
}

int main(void) {
	int cases;
	string word, startWord, endWord;
	
	cin >> cases; cin.ignore(10000, '\n');
	// Eat up the blank line
	getline(cin, word, '\n');
	
	for (int c = 0; c < cases; c++) {
		//Reset
		adjList.clear();
		stringsVect.assign(10, vector<string>(0));	
		queries.assign(0, pair<string, string>());
		int stringIdx;

		// Accept each word and find the possible connections
		while (cin >> word, word != "*") {
			stringIdx = word.length() - 1;
			
			for (int i = 0; i < (int)stringsVect[stringIdx].size(); i++) {
				// If the two words differ by exactly one character
				if (compareStr(stringsVect[stringIdx][i], word)) {
					// Form connection
					adjList[word].push_back(stringsVect[stringIdx][i]);
					adjList[stringsVect[stringIdx][i]].push_back(word);
				}
			}
			stringsVect[stringIdx].push_back(word);
			distancesMap[word] = INF;
		}
		cin.ignore(10000, '\n');
		
		// Read in the queries
		while (cin.peek() != '\n' && getline(cin, startWord)) {
			istringstream inStream(startWord);
			inStream >> startWord >> endWord;
			
			queries.push_back(make_pair(startWord, endWord));
		}
		
		//printL();
		
		// Find the shortest connection for each query
		for (auto &q : queries) {
			int path;
			path = transform(q.first, q.second);
			cout << q.first << " " << q.second << " " << path << endl;
			//printL();
		}
		if (c != cases-1) cout << endl;
	}
	return 0;
}

// Using BFS, find the shortest connection between a start and end word
int transform(string start, string end) {
	queue<string> que;
	que.push(start);
	string current;
	string neighbour;
	
	// Reset
	for (auto &it : distancesMap) {
		it.second = INF;
	}
	distancesMap[start] = 0;
	
	while (!que.empty()) {
		current = que.front();
		// Go through all its neighbours
		for (int i = 0; i < (int)adjList[current].size(); i++) {
			neighbour = adjList[current][i];
			// If the distance is infinite
			if (distancesMap[neighbour] == INF) {
				distancesMap[neighbour] = distancesMap[current] + 1;
				que.push(neighbour);
			}
		}
		
		que.pop();
	}
	
	return distancesMap[end];
}

// If the two string differ by exactly one character, return true
bool compareStr(string left, string right) {
	int changeCount = 0;
	
	for (int i = 0; i < (int)left.length(); i++) {
		if (left[i] != right[i]) {
			changeCount++;
		}
		if (changeCount > 1) {
			return false;
		}
	}
	
	if (changeCount == 1) return true;
	else return false;
}
