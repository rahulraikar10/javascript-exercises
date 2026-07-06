// Problem Statement
// A city grid has: 0=road, 1=tree (blocked), 2=garage (start), 3=warehouse, 4=airport. Moving 1 cell costs (1 + goods_carried). The truck picks up goods at warehouses and delivers to the airport. Budget C. Find the maximum goods deliverable.
// Sample Input / Output
// INPUT — Sample Input

// 3
// 2 6 30
// 2 0 0 3 0 0
// 0 0 0 3 0 4
// 1 5 5
// 2 0 0 3 4
// 2 6 30
// 2 0 0 3 0 0
// 0 0 0 1 0 4

// OUTPUT — Sample Output

// 12
// 1
// 8





#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const ll INF = 1e9;
const ll dx[] = {0,1,-1,0}, dy[] = {1,0,0,-1};

void bfs(int sx, int sy, vector<vector<ll>>& dist, const vector<vector<ll>>& mat) {
    int h = mat.size(), w = mat[0].size();
    queue<pair<int,int>> q;
    dist[sx][sy] = 0;
    q.push({sx, sy});
    while (!q.empty()) {
        auto [x,y] = q.front(); q.pop();
        for (int i = 0; i < 4; i++) {
            int nx=x+dx[i], ny=y+dy[i];
            if (nx>=0 && ny>=0 && nx<h && ny<w && mat[nx][ny]!=1 && dist[nx][ny] > dist[x][y]+1) {
                dist[nx][ny] = dist[x][y]+1;
                q.push({nx,ny});
            }
        }
    }
}

int main() {
    int t; cin >> t;
    while (t--) {
        ll h,w,c; cin >> h >> w >> c;
        vector<vector<ll>> mat(h, vector<ll>(w));
        vector<pair<ll,ll>> warehouses;
        ll gx,gy,ax,ay;
        for (ll i=0;i<h;i++) for (ll j=0;j<w;j++) {
            cin >> mat[i][j];
            if (mat[i][j]==2) gx=i,gy=j;
            if (mat[i][j]==4) ax=i,ay=j;
            if (mat[i][j]==3) warehouses.push_back({i,j});
        }
        vector<vector<ll>> dg(h,vector<ll>(w,INF)), da(h,vector<ll>(w,INF));
        bfs(gx,gy,dg,mat);
        bfs(ax,ay,da,mat);

        ll ans = 0;
        for (auto [wx,wy] : warehouses) {
            ll budget = c - dg[wx][wy];
            if (budget > 0 && da[wx][wy] > 0) {
                ll goods = (budget / da[wx][wy]) - 1;
                if (goods > 0) ans = max(ans, goods);
            }
        }
        cout << ans << "\n";
    }
}

