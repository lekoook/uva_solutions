// Dynamic Programming, Bottom Up Approach
#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_MONEY 200

using namespace std;

int main(void) {
	int cases, money, garments, models, price;
	vector< vector<int> > prices;
	vector< vector<int> > memo;
	
	cin >> cases;

	while (cases--) {
		cin >> money >> garments;
		vector<int> arr;

		// Reset all data structures
		prices.assign(garments, vector<int>(0));
		memo.assign(garments, vector<int>(MAX_MONEY+10, 0));
		
		// Read input
		for (int i = 0; i < garments; i++) {
			cin >> models;
			while (models--) {
				cin >> price;
				prices[i].push_back(price);
			}
		}

		// for (auto it : prices) {
			// for (auto it2 : it) {
				// cout << it2 << " ";
			// }
			// cout << endl;
		// }
		
		// Compute all possible states in the memo table
		// Run through the first garment's models
		for (int i = 0; i < (int)prices[0].size(); i++) {
			if (money - prices[0][i] >= 0) {
				memo[0][money - prices[0][i]] = 1;
			}
		}

		// Run through subsequent garments
		for (int g = 1; g < garments; g++) {
			for (int m = 0; m < money; m++) {
				// If the state of the previos garment is reachable, we
				// compute the resulting states in this current garment
				if (memo[g-1][m] > 0) {
					for (int k = 0; k < (int)prices[g].size(); k++) {
						if (m - prices[g][k] >= 0) {
							memo[g][m - prices[g][k]] = 1;
						}
					}
				}
			}
		}
		// cout << "  ";
		// for (int i = 0; i <= money; i++) {
			// cout << i%s0 << " ";
		// }
		// cout << endl;
		// for (int i = 0; i < garments; i++) {
			// cout << i << "|";
			// for (int j = 0; j <= money; j++) {
				// cout << memo[i][j] << " ";
			// }
			// cout << endl;
		// }
		// Given the computed states in memo table
		// We determine the answer by look for the state closest to money = 0
		int ans = -1;
		for (int i = 0; i <= money; i++) {
			if (memo[garments-1][i] > 0) {
				ans = money - i;
				break;
			}
		}

		if (ans > 0) {
			cout << ans << endl;
		}
		else {
			cout << "no solution" << endl;
		}
	}
	return 0;
}