vector<int> centroids(const vector<vector<int>>& g) {
    int n = (int)g.size() - 1;
    vector<int> sz(n + 1), ans;
    function<void(int, int)> dfs = [&](int u, int p) {
        sz[u] = 1; int mx = 0;
        for (int v : g[u]) if (v != p)
            dfs(v, u), sz[u] += sz[v], mx = max(mx, sz[v]);
        if (max(mx, n - sz[u]) <= n / 2) ans.push_back(u);
    };
    dfs(1, 0);
    return ans;
}

// 返回 {直径长度, 端点 a, 端点 b}
array<int, 3> diameter(const vector<vector<int>>& g) {
    auto bfs = [&](int s) {
        vector<int> d(g.size(), -1); queue<int> q; q.push(s); d[s] = 0;
        while (!q.empty()) {
            int u = q.front(); q.pop();
            for (int v : g[u]) if (d[v] < 0) d[v] = d[u] + 1, q.push(v);
        }
        int t = 1;
        for (int i = 1; i < (int)g.size(); i++) if (d[i] > d[t]) t = i;
        return pair<int, int>{t, d[t]};
    };
    int a = bfs(1).first;
    auto [b, d] = bfs(a);
    return {d, a, b};
}
