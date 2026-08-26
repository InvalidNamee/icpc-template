using ll = long long;

struct Tarjan {
    // 顶点编号：1..n（1-based）；SCC 编号：1..sc（1-based）
    vector<vector<int>> g;
    vector<int> dfn, low, scc, stk;
    vector<bool> ins;
    int n, tim = 0, sc = 0;
 
    Tarjan(int n) : n(n) {
        g.resize(n + 1);
        dfn.resize(n + 1);
        low.resize(n + 1);
        scc.resize(n + 1);
        ins.resize(n + 1);
    }
 
    void add(int u, int v) { g[u].push_back(v); }

    void dfs(int u) {
        dfn[u] = low[u] = ++tim;
        stk.push_back(u);
        ins[u] = true;
        for (int v : g[u]) {
            if (!dfn[v]) {
                dfs(v);
                low[u] = min(low[u], low[v]);
            } else if (ins[v]) {
                low[u] = min(low[u], dfn[v]);
            }
        }
        if (dfn[u] == low[u]) {
            sc++;
            while (true) {
                int v = stk.back();
                stk.pop_back();
                ins[v] = false;
                scc[v] = sc;
                if (v == u) break;
            }
        }
    }
 
    void run() {
        for (int i = 1; i <= n; i++)
            if (!dfn[i]) dfs(i);
    }
};
