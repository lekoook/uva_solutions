#include <iostream>
#include <vector>

using namespace std;

double search(int dishes, int remain, int fav, int N, int id, vector<int> &dimsums, 
	vector< vector<int> > &favours, vector< vector<int> > &memo);

int main(void) {
	int N, X, T, K;
	int price, favour;

	while (cin >> N >> X >> T >> K, N && X && T && K) {
		// Reset all data structures
		vector<int> dimsums;
		vector< vector<int> > favours;
		vector< vector<int> > memo;
		favours.assign(N+1, vector<int>(0));
		memo.assign(2*(N+1), vector<int>(X*(N+1)));

		// Read input
		for (int i = 0; i < K; i++) {
			cin >> price;
			dimsums.push_back(price);

			for (int j = 0; j < N+1; j++) {
				cin >> favour;
				favours[j].push_back(favour);
			}
		}

		double answer = search();

		printf("%.2lf\n", answer);
	}
	
	return 0;
}

double search(int dishes, int remain, int fav, int N, int id, vector<int> &dimsums, 
	vector< vector<int> > &favours, vector< vector<int> > &memo) {
	if (dishes > (2*(N+1)) || remain == 0) return 0;
	if (memo[dishes][remain] != -1) return memo[dishes][remain];
	if (dimsums[id] > remain) return memo[dishes][remain] = search(dishes, remain, fav, N, id+1, dimsums, favours, memo); // Ignore this dish and move on

	double sum1 = 0;
	for (int i = 0; i < N+1; i++) {
		sum1 += favours[i][id];
	}
	sum1 /= 2.0;

	double temp = max(search(dishes, remain, fav, N, id+1, dimsums, favours, memo), search(dishes+1, remain-dimsums[id], fav, N, id+1, dimsums, favours, memo)); // Ignore or take 1 of this dish
	return memo[dishes][remain] = max(temp, search()); // Take 2 of this dish
}