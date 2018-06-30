/******************************************************************************
  CS2040C AY2017/18 Semester 2
  10653.cpp
  This program 
  Lee Kok Teng
  C04
  ****************************************************************************/

#include <iostream>
#include <vector>
#include <queue>

#define CLEAR 0
#define BOMB 1
#define INF 10000

using namespace std;

int R, C;

vector< vector<int> > grid;
vector< vector<int> > distancesGrid;

void flood(int sourceR, int sourceC, int endR, int endC);

void printL() {
	cout << "grid:" << endl;
	for (int i = 0; i < (int)grid.size(); i++) {
		for (int j = 0; j < (int)grid[i].size(); j++) {
			if (grid[i][j] == BOMB)
				cout << "X ";
			else
				cout << "| ";
		}
		cout << endl;
	}
	
	cout << "distances grid:" << endl;
	for (int i = 0; i < (int)distancesGrid.size(); i++) {
		for (int j = 0; j < (int)distancesGrid[i].size(); j++) {
			if (grid[i][j] == BOMB)
				cout << "X\t";
			else
				cout << distancesGrid[i][j] << '\t';
		}
		cout << endl;
	}
}

int main(void) {
	int rows, rowNum, cols, colNum;
	int startRow, startCol, endRow, endCol;
	
	while (cin >> R >> C, R > 0 && C > 0) {
		grid.assign(R, vector<int>(C));
		distancesGrid.assign(R, vector<int>(C, INF));
		
		// Read in the grid
		cin >> rows;
		for (int i = 0; i < rows; i++) {
			cin >> rowNum;
			cin >> cols;
			for (int j = 0; j < cols; j++) {
				cin >> colNum;
				grid[rowNum][colNum] = BOMB;
			}
		}
		
		//printL();
		
		// Read in the start and end point
		cin >> startRow >> startCol >> endRow >> endCol;
		//cout << "start: " << startRow << "," << startCol << " end: " << endRow << "," << endCol << endl;
		// Flood fill algo to find the end point from source
		flood(startRow, startCol, endRow, endCol);
		
		cout << distancesGrid[endRow][endCol] << endl;
	}
	return 0;
}

void flood(int sourceR, int sourceC, int endR, int endC) {
	queue< pair<int, int> > que;
	que.push(make_pair(sourceR, sourceC));
	pair<int, int> current;
	distancesGrid[sourceR][sourceC] = 0;
	int nextR, nextC;
	
	while (!que.empty()) {
		current = que.front();
		//cout << "current: " << current.first << "," << current.second << endl;
		// If this location is the end point, break
		if (current.first == endR && current.second == endC) break;
		
		// Go through all its neighbours
		// Up
		nextR = current.first - 1;
		nextC = current.second;
		//cout << "nextR: " << nextR << " nextC: " << nextC << endl;
		if (nextR >= 0 && nextR < R && nextC >= 0 && nextC < C)
			if (grid[nextR][nextC] != BOMB)
				if (distancesGrid[nextR][nextC] == INF) {
					//cout << "going up" << endl;
					distancesGrid[nextR][nextC] = distancesGrid[current.first][current.second] + 1;
					que.push(make_pair(nextR, nextC));
				}
		// Down
		nextR = current.first + 1;
		nextC = current.second;
		//cout << "nextR: " << nextR << " nextC: " << nextC << endl;
		if (nextR >= 0 && nextR < R && nextC >= 0 && nextC < C)
			if (grid[nextR][nextC] != BOMB)
				if (distancesGrid[nextR][nextC] == INF) {
					//cout << "going up" << endl;
					distancesGrid[nextR][nextC] = distancesGrid[current.first][current.second] + 1;
					que.push(make_pair(nextR, nextC));
				}
		// Left
		nextR = current.first;
		nextC = current.second - 1;
		//cout << "nextR: " << nextR << " nextC: " << nextC << endl;
		if (nextR >= 0 && nextR < R && nextC >= 0 && nextC < C)
			if (grid[nextR][nextC] != BOMB)
				if (distancesGrid[nextR][nextC] == INF) {
					//cout << "going up" << endl;
					distancesGrid[nextR][nextC] = distancesGrid[current.first][current.second] + 1;
					que.push(make_pair(nextR, nextC));
				}
		// Right
		nextR = current.first;
		nextC = current.second + 1;
		//cout << "nextR: " << nextR << " nextC: " << nextC << endl;
		if (nextR >= 0 && nextR < R && nextC >= 0 && nextC < C)
			if (grid[nextR][nextC] != BOMB)
				if (distancesGrid[nextR][nextC] == INF) {
					//cout << "going up" << endl;
					distancesGrid[nextR][nextC] = distancesGrid[current.first][current.second] + 1;
					que.push(make_pair(nextR, nextC));
				}
		
		que.pop();
	}
}
