using ll = long long;

struct Euler {
    // 顶点编号：1..n（1-based）；边编号 id 为内部 0-based 编号
    struct E { int v, id; };

    int n, m = 0;
    vector<vector<E>> g;
    vector<int> vis, cur, ans;

    Euler(int n) : n(n), g(n + 1), cur(n + 1) {}

    void add(int u, int v) { g[u].push_back({v, m++}); }

    void addu(int u, int v) {
        g[u].push_back({v, m});
        g[v].push_back({u, m++});
    }

    void dfs(int u) {
        while (cur[u] < (int) g[u].size()) {
            E e = g[u][cur[u]++];
            if (vis[e.id]) continue;
            vis[e.id] = 1;
            dfs(e.v);
        }
        ans.push_back(u);
    }

    vector<int> run(int s) {
        vis.assign(m, 0);
        ans.clear();
        dfs(s);
        if ((int) ans.size() != m + 1) return {};
        reverse(ans.begin(), ans.end());
        return ans;
    }
};
