#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdio>
#include <array>
#include <queue>
#include <set>
#include <map>
#include <algorithm>

using namespace std;
//Given two arrays arr1 and arr2.Define score : value ≤ D → score 1, value > D → score 2. Find integer D that maximizes score(arr1) − score(arr2).
//
//Input:  t / n m / a1..an / b1..bm
//	Output : D

//sort the arrays for using the bound functions

int n,m;
int ans = -1;
vector<int> a;
vector<int> b;

void solve() {
	set<int> cand;
	for (int i = 0; i < m; i++) {
		cand.insert(b[i]);
	}
	for (int i = 0; i < n; i++) {
		cand.insert(a[i]);
	}
	vector<int> v;
	v.push_back(*cand.begin() - 1);
	for (auto &it : cand) {
		v.push_back(it);
	}
	v.push_back(*cand.rbegin() + 1); //use r begin here very important. this is used for adding the last elemnt of the set to the search space array
	int bestDiff = INT_MIN;
	for (int i = 0; i < v.size(); i++) {
		int d = v[i];
		int lessA = upper_bound(a.begin(), a.end(), d) - a.begin();
		int scoreA = lessA + ((a.size() - lessA) * 2);
		int lessB = upper_bound(b.begin(), b.end(), d) - b.begin();
		int scoreB = lessB + ((b.size() - lessB) * 2);
		int score = (scoreA - scoreB);
		if (score > bestDiff) {
			bestDiff = score;
			ans = d;
		}
	}
}

int main() {
	cin >> n;
	cin >> m;
	for (int i = 0; i < n; i++) {
		int ele;
		cin >> ele;
		a.push_back(ele);
	}
	for (int i = 0; i < m; i++) {
		int ele;
		cin >> ele;
		b.push_back(ele);
	}
	// sort your two arrays no matter what
	sort(a.begin(), a.end());
	sort(b.begin(), b.end());
	solve();
	cout << ans;
}
