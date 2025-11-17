#include <bits/stdc++.h>
using namespace std;
class Solution {
  public:
    int swimInWater(vector<vector<int>> &grid) {
        int m = grid.size(), n = grid[0].size();
        using pii = pair<int, int>;
        using ipii = pair<int, pii>;
        int dx[] = {1, -1, 0, 0}, dy[] = {0, 0, 1, -1};
        priority_queue<ipii, vector<ipii>, greater<>> pq;
        vector<bool> visited(m * n, 0);
        pq.push({grid[0][0], {0, 0}}), visited[0] = 1;
        auto isValid = [&](int r, int c) -> bool {
            return r >= 0 && c >= 0 && r < m && c < n;
        };
        while (!pq.empty()) {
            auto top = pq.top();
            pq.pop();
            int t = top.first, r = top.second.first, c = top.second.second;
            for (int i = 0; i < 4; i++) {
                int nr = r + dx[i], nc = c + dy[i];
                if (isValid(nr, nc) && !visited[nr * n + nc]) {
                    if (nr == m - 1 && nc == n - 1)
                        return max(grid[nr][nc], t);
                    pq.push({max(grid[nr][nc], t), {nr, nc}});
                    visited[nr * n + nc] = 1;
                }
            }
        }
        return grid[m - 1][n - 1];
    }
};
