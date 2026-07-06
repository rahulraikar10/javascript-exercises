#include <iostream>
#include <vector>
#include <bitset>
#include <unordered_map>
#include <cstdio>
#include <array>
#include <queue>
#include <set>
#include <map>
#include <algorithm>
using namespace std;

// this is the 2D prefix sum question. calc in place 2d prefix sum

// Given N tiles with integer coordinates (width, height) in range [0,400], find the minimum side length s of an axis-aligned square such that at least K tile coordinates fall within it.

// Input:  n k / x1 y1 / x2 y2 / ...
// Output: ans
// 📥 Sample Input
// STDIN

// 5 3
// 1 1
// 2 2
// 3 3
// 4 4
// 5 5

// 📤 Sample Output
// STDOUT

// 2

bool isValid(vector<vector<int>> &freq, int mid, int k) {
	for (int i = 0; i + mid < 401; i++) {
		for (int j = 0; j + mid < 401; j++) {
			int cnt = freq[i + mid][j + mid];
			if (i > 0) cnt -= freq[i - 1][j + mid];
			if (j > 0) cnt -= freq[i + mid][j - 1];
			if (i>0 && j > 0) cnt += freq[i-1][j-1];
			if (cnt >= k) return true;
		}
	}
	return false;	
}

int main() {
	FILE *fp;
	freopen_s(&fp, "input.txt", "r", stdin);
	freopen_s(&fp, "output.txt", "w", stdout);
	int n = 0;
	cin >> n;
	int k = 0;
	cin >> k;
	vector<vector<int>> freq(401, vector<int>(401, 0));
	for (int i = 0; i < n; i++) {
		int r, s;
		cin >> r >> s;
		freq[r][s]++;
	}
	//create the 2D prefix matrix
	for (int i = 0; i < 401; i++) {
		for (int j = 0; j < 401; j++) {
			if (i > 0) freq[i][j] += freq[i - 1][j];
			if (j > 0) freq[i][j] += freq[i][j - 1];
			if (i>0 && j > 0) freq[i][j] -= freq[i-1][j-1];
		}
	}

	int low = 0;
	int high = 400;
	int ans = 400;
	while (low <= high) {
		int mid = (low + high) / 2;
		if (isValid(freq, mid, k)) {
			high = mid - 1;
			ans = mid;
		}
		else {
			low = mid + 1;
		}
	}
	cout << ans;
}
