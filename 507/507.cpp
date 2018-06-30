#include <iostream>
#include <vector>
#include <climits>

using namespace std;

int main(void) {
	int cases, stops, val;

	cin >> cases;
	for (int r = 1; r <= cases; r++) {
		// Read input
		cin >> stops; 

		// cout << "Route:" << endl;
		// for (auto it : niceness) cout << it << " ";
		// cout << endl;

		// Compute the largest range sum using Kadane's algorithm
		int sum = 0, max = INT_MIN;
		int startIndex = 1, endIndex = 0, tempIndex = 1;
		for (int i = 2; i <= stops; i++) {
			cin >> val;
			sum += val;
			// cout << "sum = " << sum << " max = " << max << endl;
			if (sum >= max) {
				if (sum > max || (sum == max && (i - tempIndex) > (endIndex-startIndex))) {
					startIndex = tempIndex;
					endIndex = i;
					// cout << "start = " << startIndex << " end = " << endIndex << endl;
				}
				max = sum;
			}
			
			if (sum < 0) {
				sum = 0;
				tempIndex = i;
			}
		}

		if (max < 0) {
			cout << "Route " << r << " has no nice parts" << endl; 
		}
		else {
			cout << "The nicest part of route " << r <<
			" is between stops " << startIndex <<
			" and " << endIndex << endl;
		}
	}
	return 0;
}