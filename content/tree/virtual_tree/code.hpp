struct VirtualTree {
    int n, lg = 1, tim = 0;
    const vvi& g;
    vvi up, vt;
    vi dep, tin, tout, nodes;

    VirtualTree(const vvi& g, int root = 1)
        : n((int)g.size() - 1), g(g), vt(n + 1),
          dep(n + 1), tin(n + 1), tout(n + 1) {
        while ((1 << lg) <= n) lg++;
        up.assign(lg, vi(n + 1));
        dfs(root, root);
    }

    void dfs(int u, int p) {
        tin[u] = ++tim;
        up[0][u] = p;
        for (int i = 1; i < lg; i++)
            up[i][u] = up[i - 1][up[i - 1][u]];
        for (int v : g[u]) if (v != p) {
            dep[v] = dep[u] + 1;
            dfs(v, u);
        }
        tout[u] = tim;
    }

    bool ancestor(int u, int v) const {
        return tin[u] <= tin[v] && tout[v] <= tout[u];
    }

    int lca(int u, int v) const {
        if (ancestor(u, v)) return u;
        if (ancestor(v, u)) return v;
        for (int i = lg - 1; i >= 0; i--)
            if (!ancestor(up[i][u], v)) u = up[i][u];
        return up[0][u];
    }

    int build(vi key) {
        for (int u : nodes) vt[u].clear();
        nodes.clear();
        if (key.empty()) return 0;

        auto cmp = [&](int u, int v) { return tin[u] < tin[v]; };
        sort(key.begin(), key.end(), cmp);
        key.erase(unique(key.begin(), key.end()), key.end());
        int k = key.size();
        for (int i = 0; i + 1 < k; i++)
            key.push_back(lca(key[i], key[i + 1]));
        sort(key.begin(), key.end(), cmp);
        key.erase(unique(key.begin(), key.end()), key.end());
        nodes = key;

        vi stk;
        for (int u : nodes) {
            while (!stk.empty() && !ancestor(stk.back(), u))
                stk.pop_back();
            if (!stk.empty()) vt[stk.back()].push_back(u);
            stk.push_back(u);
        }
        return nodes[0];
    }
};
