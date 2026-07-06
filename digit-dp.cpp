#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cstdio>

// Problem Statement:
// A company issues gift certificates with unique serial numbers (numeric only).
// The digit sum of all serial numbers issued on the same day is S.
// Given A (max serial number) and S, find how many valid serial numbers exist.

// Constraints:
// 1 <= A < 10^100  (A can be very large)
// 1 <= S <= 1000    (Digit sum limit)

// Output:
// Return the count of valid serial numbers modulo 10^9 + 7.

// Example Cases:
// A = 101, S = 3 → Answer: 4  (Valid: 21, 12, 3, 30)
// A = 172, S = 3 → Answer: 7  (Valid: 3, 12, 21, 30, 102, 111, 120)
// A = 50, S = 4  → Answer: 5  (Valid: 4, 40, 13, 31, 22)
// A = 999, S = 500 → Answer: 0 (Max digit sum is 27, so no valid numbers)

using namespace std;

const int mod = 1e9 + 7;

int solve(int pos, int rem, int tight, vector<vector<vector<int>>> &dp, string &A) {
	if (rem < 0) {
		return 0;
	}
	if (pos == (int)A.size()) {
		return rem == 0;
	}
	if (dp[pos][rem][tight] != -1) {
		return dp[pos][rem][tight];
	}
	int limit = (tight) ? A[pos] - '0' : 9;
	int ans = 0;  
	for (int i = 0; i <= limit; i++) {

        int next_limit = (tight && (i == limit));  //calculate next_limit here
        ans = (ans+solve(pos+1,rem-i,next_limit,dp,A))%mod;   // this is rem - i and not 1. also this is pos + 1 and not pos + i

	}
	return dp[pos][rem][tight]=ans;
}


int main() {
	string A;
	int S;
	cin >> A >> S;
	int n = A.size();
	int rem = S;
	// dp of n, s and tight or not - 3D dp
	vector<vector<vector<int>>> dp(n, vector<vector<int>>(S + 1, vector<int>(2, -1)));
	cout << solve(0, rem, 1, dp, A);

}