struct VertexBCC {
    struct E { int v, id; };

    int n, tim = 0, cnt = 0, eid = 0;
    vector<vector<E>> g;
    vector<vector<int>> bcc, tree;
    vector<int> dfn, low, stk;
    vector<bool> cut;

    VertexBCC(int n) : n(n), g(n + 1), bcc(1),
        dfn(n + 1), low(n + 1), cut(n + 1) {}

    void add(int u, int v) {
        if (u == v) return;
        int id = eid++;
        g[u].push_back({v, id});
        g[v].push_back({u, id});
    }

    void tarjan(int u, int pe) {
        dfn[u] = low[u] = ++tim;
        stk.push_back(u);
        int child = 0;
        for (auto [v, id] : g[u]) {
            if (id == pe) continue;
            if (!dfn[v]) {
                child++;
                tarjan(v, id);
                low[u] = min(low[u], low[v]);
                if (low[v] < dfn[u]) continue;

                if (pe != -1 || child > 1) cut[u] = true;
                ++cnt;
                bcc.push_back({u});
                while (true) {
                    int x = stk.back();
                    stk.pop_back();
                    bcc[cnt].push_back(x);
                    if (x == v) break;
                }
            } else {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (pe == -1 && child == 0) {
            ++cnt;
            bcc.push_back({u});
            stk.pop_back();
        }
    }

    void run() {
        for (int u = 1; u <= n; u++) {
            if (dfn[u]) continue;
            tarjan(u, -1);
            stk.clear();
        }

        tree.assign(n + cnt + 1, {});
        for (int i = 1; i <= cnt; i++) {
            int p = n + i;
            for (int u : bcc[i]) {
                tree[p].push_back(u);
                tree[u].push_back(p);
            }
        }
    }
};
