#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int main(void) {
	int N, val;
	vector< vector<int> > grid;

	cin >> N;
	grid.assign(N, vector<int>(N));

	// Read input and compute the running sum of each cell for 
	// each row from left to right
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> val;
			grid[i][j] = val;
			if (j > 0) {
				grid[i][j] += grid[i][j-1];
			}
		}
	}

	// Process all sub rectangles by pairing column indices and run
	// Kadane's algorithm from the top to bottom, first to last row
	int maxSum = -127 * 100 * 100; // Minimum possible sum for this problem
	for (int l = 0; l < N; l++) {
		for (int r = l; r < N; r++) {
			// Run Kadane's algorithm downwards in the grid
			// The right index position's value indicates the running sum
			// of that entire row up till right index position
			// Take that value and minus the value of the cell that is one cell
			// left to the left index position
			// The resulting value is the sum of that sub row
			int subRectSum = 0;
			for (int row = 0; row < N; row++) {
				// Add the current sub row's sum to sub rectangle running sum
				if (l > 0)
					subRectSum += grid[row][r] - grid[row][l-1];
				else
					subRectSum += grid[row][r];

				// Use Kadane's algorithm idea to get the maximum possible sum
				if (subRectSum < 0) {
					subRectSum = 0;
				}
				maxSum = max(maxSum, subRectSum);
			} 
		}
	}

	cout << maxSum << endl;
	return 0;
}