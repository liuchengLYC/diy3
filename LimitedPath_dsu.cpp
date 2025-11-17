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
    vector<bool> distanceLimitedPathsExist(int n, vector<vector<int>> &edgeList,
                                           vector<vector<int>> &queries) {
        sort(edgeList.begin(), edgeList.end(),
             [](vector<int> &a, vector<int> &b) { return a[2] < b[2]; });

        int m = queries.size();

        for (int i = 0; i < m; i++) {
            queries[i].push_back(i);
        }
        sort(queries.begin(), queries.end(),
             [](vector<int> &a, vector<int> &b) { return a[2] < b[2]; });

        vector<bool> ans(m, false);
        DSU dsu(n);
        int i = 0;
        for (auto &q : queries) {
            int p = q[0], r = q[1], limit = q[2], id = q[3];
            while (i < edgeList.size() && edgeList[i][2] < limit) {
                int u = edgeList[i][0];
                int v = edgeList[i][1];
                dsu.unite(u, v);
                i++;
            }
            ans[id] = (dsu.find(p) == dsu.find(r));
        }
        return ans;
    }
};
