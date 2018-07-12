#include <iostream>
#include <vector>
#include <algorithm>
#include <cstring>
#include <cmath>

using namespace std;

// Global variables
int N, X, T, K;
int price;

vector<int> dimsums;
// Indicates the total favours from each person for each dimsum
vector<int> favours;
// Memoization table 3D
int memo[110][25][1105] = {{{ -1 }}};


int search(int idx, int dishes, int sum);

int main(void) {

	while (cin >> N >> X >> T >> K, N || X || K || T) {
		// Reset all structures
		dimsums.assign(K, 0);
		favours.assign(K, 0);
		memset(memo, -1, sizeof memo);
		
		// Read in the dimsums
		for (int i = 0; i < K; i++) {
			cin >> price;
			dimsums[i] = price;

			// Read in the favours
			int f;
			for (int j = 0; j < N+1; j++) {
				cin >> f;
				favours[i] += f;
			}
		}

		double ans = search(0, 0, 0);

		printf("%.2lf\n", ans/(N+1));
	}
	return 0;
}

int search(int idx, int dishes, int sum) {
	// If we looked through all dimsums
	if (idx == K) return 0;
	// If we have already computed this state, skip it
	if (memo[idx][dishes][sum] != -1) return memo[idx][dishes][sum];
	
	int fav1 = 0, fav2 = 0, fav3 = 0;
	// We ignore current dimsum
	fav1 = search(idx + 1, dishes, sum);
	// OR pick one of the current dimsum 
	// IF would not exceed allowable cost AND would not exceed dishes limit
	double sumCurrT = sum + (T * (N + 1));
	if (dishes < (2*(N+1)) && ceil((sumCurrT + dimsums[idx]) * 1.1L ) <= (N+1) * X)
		fav2 = favours[idx] + search(idx + 1, dishes + 1, sum + dimsums[idx]);
	// OR pick two of the current dimsum 
	// IF would not exceed allowable cost AND would not exceed dishes limit
	if (dishes+1 < (2*(N+1)) && ceil((sumCurrT + (2 * dimsums[idx])) * 1.1L) <= (N+1) * X)
		fav3 = (2 * favours[idx]) + search(idx + 1, dishes + 2, sum + (2 * dimsums[idx]));

	int m = max(fav3, max(fav1, fav2));

	return memo[idx][dishes][sum] = m;
}