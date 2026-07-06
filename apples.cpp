#include <iostream>
#include <vector>
#include <unordered_map>
#include <cstdio>
#include <array>
#include<queue>
#include <set>
#include<map>
#include <algorithm>

//deque comes here VERY IMPORTANT
//keep a count if the apples here, increment cnt only when the the gird value is 1+ the old cnt. also initialise a 4d dp

using namespace std;
typedef long long ll;


// 📋 Problem Statement
// N×N map. Apples numbered 1..M appear in order. Start at (0,0) moving right. Only right turns allowed (no left/backward). Eat apples in order 1, 2, ..., M. -1 = trap (blocked). Find minimum right turns to eat all apples. Return -1 if impossible.

// Input:  n m / <grid of n×m integers>  (0=empty, -1=trap, positive=apple number)
// Output: ans
// 📥 Sample Input
// STDIN

// 3 3
// 0 1 0
// 0 2 0
// 0 -1 3

// 📤 Sample Output
// STDOUT

// 5


int main() {
	int m, n;
	vector<int> dx = { 0, 1, 0, -1 }, dy = { 1, 0, -1, 0 };
	cin >> m >> n;
	int totApples = 0;
	vector<vector<int>> grid(m, vector<int>(n));
	for (int i = 0; i < m; i++) {
		for (int j = 0; j < n; j++) {
			cin >> grid[i][j];
			if(grid[i][j] > 0)
			totApples = max(totApples, grid[i][j]);
		}
	}
	 const int INF = INT_MAX / 2;
	 vector<vector<vector<array<int, 4>>>> dp(m, vector<vector<array<int, 4>>>(n, vector<array<int, 4>>(totApples + 1, array<int, 4>{INF,INF,INF,INF})));
	 deque<array<int, 4>> dq;
	 dq.push_back({ 0,0,grid[0][0] == 1,0 });
	 dp[0][0][grid[0][0] == 1][0] = 0;

	 // Check if start is a trap? (Optional based on problem constraints, but good practice)
    if (grid[0][0] == -1) {
        cout << -1 << endl;
        return 0;
    }

	 while (!dq.empty()) {
		 array<int, 4> cur = dq.front();
		 int x = cur[0];
		 int y = cur[1];
		 int cnt = cur[2];
		 int dir = cur[3];
		 dq.pop_front();
		 {
			 int nx = x + dx[dir];
			 int ny = y + dy[dir];
			 if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] != -1) {
				 int ncnt = cnt + (grid[nx][ny] == cnt + 1);
				 if (dp[nx][ny][ncnt][dir] > dp[x][y][cnt][dir]) {
					 dp[nx][ny][ncnt][dir] = dp[x][y][cnt][dir];
					 dq.push_front({ nx,ny,ncnt,dir });
				 }
			 }
		 }
		 {		
			 int ndir = (dir + 1) % 4;
			 int nx = x + dx[ndir];
			 int ny = y + dy[ndir];
			 if (nx >= 0 && nx < m && ny >= 0 && ny < n && grid[nx][ny] != -1) {
				 int ncnt = cnt + (grid[nx][ny] == cnt + 1);
				 if (dp[nx][ny][ncnt][ndir] > dp[x][y][cnt][dir]+1) {
					 dp[nx][ny][ncnt][ndir] = dp[x][y][cnt][dir]+1;
					 dq.push_back({ nx,ny,ncnt,ndir });
				 }
			 }
		 }
	 }
	 int ans = INT_MAX;
	 for (int i = 0; i < m; i++) {
		 for (int j = 0; j < n; j++) {	
			 for (int k = 0; k < 4; k++) {
				 ans = min(ans, dp[i][j][totApples][k]);
			 }
		 }
	 }
	 cout << ans;
}
