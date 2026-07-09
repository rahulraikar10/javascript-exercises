#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdio>
#include <algorithm>
using namespace std;

// 📋 Problem Statement
//Tree where each node has soldiers.Balance: all sibling subtrees have equal sum.Can only remove soldiers.Minimize removals.Return total soldiers after balancing.
//
//Input : n / parent0 soldiers0 / parent1 soldiers1 / ... (root has parent = -1)
//	Output : ans
//	📥 Sample Input
//	STDIN
//
	// 5
	// - 1 5
	// 0 3
	// 0 2
	// 1 4
	// 1 1
//
//	📤 Sample Output
//	STDOUT
//
//	9

const int SIZE  = 500;
vector<int> tree[SIZE];
int parent[SIZE];
int value[SIZE];
int n = 0;

int solve(int u) {
	vector<int> childSum;
	for (auto v : tree[u]) {
		int sub = solve(v);
		childSum.push_back(sub);
	}
	if (childSum.size() == 0) {
		return value[u];
	}
	int target = *min_element(childSum.begin(),childSum.end());
    int totalSum = target*childSum.size();
    return totalSum+value[u];
}


int main() {
	FILE *fp;
	freopen_s(&fp, "input.txt", "r", stdin);
	freopen_s(&fp, "output.txt", "w", stdout);
	cin >> n;
	int root = -1;
	for (int i = 0; i < n; i++) {
		cin>>parent[i]>>value[i];
		if (parent[i] == -1) {
			root = i;
		}
		else {
			tree[parent[i]].push_back(i);
		}

	}
	cout << solve(root);
	

}
