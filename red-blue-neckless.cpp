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

//STORE PREFIX SUMS. THE INDEX WHERE THE PREFIX SUM MATCHES MEANS THAT TILL THERE THE LENGTH OF THE CORRESPONDING NECKLESS IS SAME

int main() {
	FILE *fp;
	freopen_s(&fp, "input.txt", "r", stdin);
	freopen_s(&fp, "output.txt", "w", stdout);
	string s;
	cin >> s;
	map<int, int> mpp;
	mpp[0] = -1;
	int pSum = 0;
	int maxLen = INT_MIN;
	for (int i = 0; i < s.size();i++) {
		if (s[i] == 'R') pSum += 1;
		else pSum += -1;
		if (mpp.find(pSum) != mpp.end()) {
			int len = i - mpp[pSum];
			maxLen = max(maxLen, len);
		}
		else {
			mpp[pSum] = i;
		}
	}
	cout << s.size()-maxLen;
}
