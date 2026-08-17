struct EdgeBCC {
    struct E { int v, id; };

    int n, tim = 0, cnt = 0;
    vector<pair<int, int>> edges;
    vector<vector<E>> g;
    vector<vector<int>> tree;
    vector<int> dfn, low, stk, bel;

    EdgeBCC(int n) : n(n), g(n + 1), dfn(n + 1),
        low(n + 1), bel(n + 1) {}

    void add(int u, int v) {
        if (u == v) return;
        int id = edges.size();
        edges.push_back({u, v});
        g[u].push_back({v, id});
        g[v].push_back({u, id});
    }

    void tarjan(int u, int pe) {
        dfn[u] = low[u] = ++tim;
        stk.push_back(u);
        for (auto [v, id] : g[u]) {
            if (id == pe) continue;
            if (!dfn[v]) {
                tarjan(v, id);
                low[u] = min(low[u], low[v]);
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (dfn[u] != low[u]) return;
        ++cnt;
        while (true) {
            int v = stk.back();
            stk.pop_back();
            bel[v] = cnt;
            if (v == u) break;
        }
    }

    void run() {
        for (int u = 1; u <= n; u++)
            if (!dfn[u]) tarjan(u, -1);

        tree.assign(cnt + 1, {});
        for (auto [u, v] : edges) {
            int x = bel[u], y = bel[v];
            if (x == y) continue;
            tree[x].push_back(y);
            tree[y].push_back(x);
        }
    }
};
