#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int search(int id, int remainWeight, int size, vector<int> &weights, 
	vector<int> &prices, vector< vector<int> > &states);

int main(void) {
	int cases, size, weight, price, persons;

	cin >> cases;
	while (cases--) {
		// Reset all data structures
		cin >> size;
		vector<int> itemsWeight;
		vector<int> itemsPrice;
		vector< vector<int> > states;
		states.assign(size, vector<int>(31, -1));
		// Read in the items
		for (int i = 0; i < size; i++) {
			cin >> price >> weight;
			itemsPrice.push_back(price);
			itemsWeight.push_back(weight);
		}

		// Read in the people
		// Recursively complete search all possible states
		cin >> persons;
		int totalValue = 0;
		for (int i = 0; i < persons; i++) {
			cin >> weight;
			totalValue += search(0, weight, size, itemsWeight, itemsPrice, states);
		}
		
		cout << totalValue << endl;
	}
	return 0;
}

int search(int id, int remainWeight, int size, vector<int> &weights, 
	vector<int> &prices, vector< vector<int> > &states) {
	if (remainWeight == 0 || id == size) return 0;

	if (states[id][remainWeight] != -1) return states[id][remainWeight];	

	if (weights[id] > remainWeight)
		return states[id][remainWeight] = 
			search(id + 1, remainWeight, size, weights, prices, states);

	return states[id][remainWeight] = 
		max(search(id+1, remainWeight, size, weights, prices, states), 
			prices[id] + search(id+1, remainWeight-weights[id], size, weights, prices, states));
}