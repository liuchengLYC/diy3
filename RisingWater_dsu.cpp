#include <bits/stdc++.h>
using namespace std;
class DSU {
  private:
    vector<int> parent, rank;

  public:
    DSU(int n) {
        parent.resize(n);
        rank.assign(n, 0);
        iota(parent.begin(), parent.end(), 0);
    }
    int find(int x) {
        if (parent[x] != x)
            parent[x] = find(parent[x]);
        return parent[x];
    }
    void unite(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b)
            return;
        if (rank[a] < rank[b])
            swap(a, b);
        parent[b] = a;
        if (rank[a] == rank[b])
            rank[a]++;
    }
};

class Solution {
  public:
    int swimInWater(vector<vector<int>> &grid) {
        int n = grid.size();
        using pii = pair<int, int>;
        using ipii = pair<int, pii>;
        vector<ipii> edges;
        auto id = [&](int x, int y) { return x * n + y; };

        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (i + 1 < n) {
                    int w = max(grid[i][j], grid[i + 1][j]);
                    edges.push_back({w, {id(i, j), id(i + 1, j)}});
                }
                if (j + 1 < n) {
                    int w = max(grid[i][j], grid[i][j + 1]);
                    edges.push_back({w, {id(i, j), id(i, j + 1)}});
                }
            }
        }
        sort(edges.begin(), edges.end(),
             [](auto &x, auto &y) { return x.first < y.first; });
        DSU dsu(n * n);
        for (auto &e : edges) {
            int w = e.first, u = e.second.first, v = e.second.second;
            dsu.unite(u, v);
            if (dsu.find(0) == dsu.find(n * n - 1)) {
                return w;
            }
        }
        return 0;
    }
};
