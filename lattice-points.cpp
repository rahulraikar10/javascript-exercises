#include <bits/stdc++.h>
using namespace std;
/*
📋 Problem Statement
A 2D grid contains N query points. There are M route points forming a connected Manhattan path (consecutive points connected by axis-aligned line segments). Find how many query points lie on the path.
Constraints: N ≤ 10⁶, M ≤ 10⁵, coordinates ≤ 10⁹.

Input Format:
  T
  N M
  x1 x2 ... xN
  y1 y2 ... yN
  px1 px2 ... pxM
  py1 py2 ... pyM

Output Format: #count
📥 Sample Input
STDIN

4 4
0 0 2 3
2 5 4 3
0 0 3 3
1 4 4 2

📤 Sample Output
STDOUT

#3
*/
void mergeIntervals(vector<pair<int,int>> &v) {
    sort(v.begin(), v.end());
    vector<pair<int,int>> merged;
    for (auto &seg : v) {
        if (!merged.empty() && seg.first <= merged.back().second) {
            merged.back().second = max(merged.back().second, seg.second);
        } else {
            merged.push_back(seg);
        }
    }
    v = merged;
}

bool onSegment(map<int, vector<pair<int,int>>> &segMap, int key, int val) {
    auto it = segMap.find(key);
    if (it == segMap.end()) return false;
    auto &v = it->second;
    auto j = upper_bound(v.begin(), v.end(), make_pair(val, INT_MAX));
    if (j == v.begin()) return false;
    --j;
    return j->first <= val && val <= j->second;
}

int main() {
    ios_base::sync_with_stdio(false);
    cin.tie(nullptr);

    int T;
    cin >> T;	
    while (T--) {
        int n, m;
        cin >> n >> m;

        vector<int> qx(n), qy(n), px(m), py(m);
        for (int i = 0; i < n; i++) cin >> qx[i];
        for (int i = 0; i < n; i++) cin >> qy[i];
        for (int i = 0; i < m; i++) cin >> px[i];
        for (int i = 0; i < m; i++) cin >> py[i];

        //populate the maps u will create
        map<int, vector<pair<int,int>>> vertSeg, horizSeg; // x-> [y_lo,y_hi], y-> [x_lo,x_hi]
        for (int i = 0; i + 1 < m; i++) {
            int x1 = px[i], y1 = py[i], x2 = px[i+1], y2 = py[i+1];
            if (x1 == x2) vertSeg[x1].push_back({min(y1,y2), max(y1,y2)});
            else if (y1 == y2) horizSeg[y1].push_back({min(x1,x2), max(x1,x2)});
            // (degenerate x1==x2 && y1==y2 falls into vertical branch harmlessly)
        }

        for (auto &p : vertSeg) mergeIntervals(p.second);
        for (auto &p : horizSeg) mergeIntervals(p.second);

        long long count = 0;
        for (int i = 0; i < n; i++) {
            if (onSegment(vertSeg, qx[i], qy[i]) || onSegment(horizSeg, qy[i], qx[i]))
                count++;
        }

        cout << "#" << count << "\n";
    }
    return 0;
}
