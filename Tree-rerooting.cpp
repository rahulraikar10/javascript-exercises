// 📋 Problem Statement
// Given a tree of n nodes, each with a value. Compute the maximum sum of weighted distances from any node to all others. Contribution of node v = value[v] × distance(u,v).

// Input:  t / n / a1..an / u1 v1 / ...
// Output: ans
// 📥 Sample Input
// STDIN

// 1
// 4
// 1 2 3 4
// 1 2
// 2 3
// 2 4

// 📤 Sample Output
// STDOUT

// 16

#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdio>
#include <algorithm>
using namespace std;
typedef long long ll;

const int MAXN = 200001;
vector<ll> g[MAXN];
vector<ll> val(MAXN), sub(MAXN), dist(MAXN);
ll ans = 0;

void dfs1(int u, int p) {
	sub[u] = val[u];
	for (int v : g[u]) {
		if (v == p) continue;
		dfs1(v, u);
		sub[u] += sub[v]; 
		dist[u] += dist[v] + sub[v];
	}
}

void reroot(int u, int p) {
	ans = max(ans, dist[u]);
	for (int v : g[u]) {
		if (v == p) continue;
		sub[u] -= sub[v]; //remove child from subtree
		dist[u] -= (dist[v] + sub[v]);
		sub[v] += sub[u];
		dist[v] += (dist[u] + sub[u]);
		reroot(v, u);
		sub[v] -= sub[u];
		dist[v] -= (dist[u] + sub[u]);
		sub[u] += sub[v];
		dist[u] += (dist[v] + sub[v]);
	}
}

int main() {
	FILE *fp;
	freopen_s(&fp, "input.txt", "r", stdin);
	freopen_s(&fp, "output.txt", "w", stdout);
	ios_base::sync_with_stdio(false); cin.tie(NULL);
	int n; 
	cin >> n;
	for (int i = 1; i <= n; i++) 
    cin >> val[i];
	for (int i = 1; i < n; i++) { 
		int u, v; 
		cin >> u >> v;
		g[u].push_back(v);
		g[v].push_back(u);
	}
	dfs1(1, -1);
	reroot(1, -1);
	cout << ans <<"\n";
}