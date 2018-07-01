#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

void p(vector<int> &array, int size);

int main(void) {
	vector<int> array; int val;
	while (cin >> val) {
		array.push_back(val);
	}
	vector<int> output;
	int size = array.size();

	output.assign(size, 0);

	int currLen = 0;
	for (int i = 0; i < size; i++) {
		int pos = lower_bound(output.begin(), output.begin() + currLen, array[i]) 
			- output.begin();
			
		output[pos] = array[i];
		if (pos+1 >= currLen) {
			currLen = pos + 1;
		}
	}

	cout << currLen << endl << "-" << endl;
	p(output, currLen);
	
	return 0;
}

void p(vector<int> &array, int size) {
	for (int i = 0; i < size; i++) {
		cout << array[i] << endl;
	}
}