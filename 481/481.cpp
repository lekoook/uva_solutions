#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void p(vector<int> &input, vector<int> &predecessor, int endIdx);

int main(void) {
	vector<int> array; int val;
	while (cin >> val) {
		array.push_back(val);
	}
	int size = array.size();
	vector<int> output;
	vector<int> predecessor;
	vector<int> indices;

	// cout << "Original input:" << endl;
	// for (int i = 0; i < size; i++) {
		// cout << array[i] << endl;
	// }
	
	output.assign(size, 0);
	predecessor.assign(size, 0);
	indices.assign(size, 0);

	int currLen = 0, endIdx = 0;
	for (int i = 0; i < size; i++) {
		int pos = lower_bound(output.begin(), output.begin() + currLen, array[i]) 
			- output.begin();
			
		output[pos] = array[i];
		indices[pos] = i;
		if (pos > 0) {
			predecessor[i] = indices[pos -1 ];
		}
		else {
			predecessor[i] = -1;
		}
		
		// cout << "Adding " << array[i] << " to pos = " << pos << endl;
		if (pos+1 >= currLen) {
			currLen = pos + 1;
			endIdx = i;
		}
	}

	cout << currLen << endl << "-" << endl;
	p(array, predecessor, endIdx);
	
	return 0;
}

void p(vector<int> &input, vector<int> &predecessor, int endIdx) {
	vector<int> temp;
	int idx = endIdx;

	// Run through the predecessor array and reconstruct the LIS
	while (idx != -1) {
		temp.push_back(input[idx]);
		idx = predecessor[idx];
	}

	// Print output
	for (int i = (int)temp.size()-1; i >= 0; i--) {
		cout << temp[i] << endl;
	}
}