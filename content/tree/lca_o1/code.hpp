struct LCA {
    const vector<vector<int>>& g;
    vector<int> dep, first, eul, lg;
    vector<vector<int>> st;

    LCA(const vector<vector<int>>& g, int root = 1)
        : g(g), dep(g.size()), first(g.size()) {
        eul.push_back(0); // 欧拉序使用 1 下标
        dfs(root, 0);
        int m = (int)eul.size() - 1;
        lg.assign(m + 1, 0);
        for (int i = 2; i <= m; i++) lg[i] = lg[i / 2] + 1;
        st.assign(lg[m] + 1, vector<int>(m + 1));
        st[0] = eul;
        for (int k = 1; k < (int)st.size(); k++)
            for (int i = 1; i + (1 << k) - 1 <= m; i++) {
                int x = st[k - 1][i], y = st[k - 1][i + (1 << (k - 1))];
                st[k][i] = dep[x] < dep[y] ? x : y;
            }
    }

    void dfs(int u, int p) {
        first[u] = (int)eul.size(); eul.push_back(u);
        for (int v : g[u]) if (v != p) {
            dep[v] = dep[u] + 1;
            dfs(v, u); eul.push_back(u);
        }
    }

    int lca(int u, int v) const {
        int l = first[u], r = first[v];
        if (l > r) swap(l, r);
        int k = lg[r - l + 1], x = st[k][l], y = st[k][r - (1 << k) + 1];
        return dep[x] < dep[y] ? x : y;
    }

    int dist(int u, int v) const {
        return dep[u] + dep[v] - 2 * dep[lca(u, v)];
    }

    bool on_path(int x, int u, int v) const {
        return dist(u, x) + dist(x, v) == dist(u, v);
    }
};
