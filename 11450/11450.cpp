// Dynamic Programming, Top Down Approach
#include <iostream>
#include <vector>
#include <algorithm>

#define MAX_MONEY 200

using namespace std;
// int states = 0;
int explore(vector< vector<int> > &prices, vector< vector<int> > &memo,
	int money, int garment, int garmentLimit, int moneyLimit, vector<int> arr);

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
		memo.assign(MAX_MONEY, vector<int>(garments, -1));
		
		// Read input
		for (int i = 0; i < garments; i++) {
			cin >> models;
			while (models--) {
				cin >> price;
				prices[i].push_back(price);
			}
		}

		// Run through all possible combinations using Dynamic Programming
		// Top Down approach
		// Same 'outcomes' or 'states' are not computed more than once.
		int ans = explore(prices, memo, money, 0, garments, money, arr);

		if (ans < 0)
			cout << "no solution" << endl;
		else
			cout << ans << endl;

		// cout << "states = " << states << endl;
	}
	return 0;
}

int explore(vector< vector<int> > &prices, vector< vector<int> > &memo, int money, int garment, int garmentLimit, int moneyLimit, vector<int> arr) {
	// If we run out of money, this combination of garments is not possible
	if (money < 0) {
		// if (!arr.empty()) arr.pop_back();
		return -1;
	}

	// Once we have reached the pieces of garments required
	// and money is within range, we return the spent amount
	if (garment == garmentLimit) {
		// if (!arr.empty()) arr.pop_back();
		return moneyLimit - money;
	}

	// We check if this state has already been computed
	if (memo[money][garment] != -1) {
		// cout << "	Duplicate state: money = " << money << " garment = " << garment << endl;
		// cout << "	garments list: ";
		// for (auto it : arr) cout << it << " ";
		// cout << endl << endl;
		// if (!arr.empty()) arr.pop_back();
		return memo[money][garment];
	}

	int ans = -1;	
	// Run through all the models of current garment
	for (int i = 0; i < (int)prices[garment].size(); i++) {
		// arr.push_back(prices[garment][i]);
		// cout << "Checking the follow garments: ";
		// for (auto it : arr) cout << it << " ";
		// cout << endl;
		ans = max(ans, explore(prices, memo, money - prices[garment][i], 
			(garment + 1), garmentLimit, moneyLimit, arr));
		// arr.pop_back();
	}

	// cout << "Memoising of state: money = " << money << " garment = " << garment << " with " << ans << endl;
	// cout << "garments list: ";
	// for (auto it : arr) cout << it << " ";
	// cout << endl << endl;

	// if (!arr.empty()) arr.pop_back();
	// states++;
	return memo[money][garment] = ans;
}