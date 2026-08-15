using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;
using pii = pair<int, int>;

struct CentroidTree {
    static const int INF = 1e9;
    int n;
    const vvi& g;
    vi sz, dead, cpar, clev, active;
    vector<vector<pii>> path;
    vector<multiset<int>> bag;

    CentroidTree(const vvi& g) : n((int)g.size() - 1), g(g) {
        sz.resize(n + 1); dead.assign(n + 1, 0);
        cpar.assign(n + 1, 0); clev.assign(n + 1, 0);
        active.assign(n + 1, 0); path.resize(n + 1); bag.resize(n + 1);
        build(1, 0);
    }

    void dfs_sz(int u, int p) {
        sz[u] = 1;
        for (int v : g[u]) if (v != p && !dead[v]) dfs_sz(v, u), sz[u] += sz[v];
    }

    int find(int u, int p, int tot) {
        for (int v : g[u])
            if (v != p && !dead[v] && sz[v] > tot / 2) return find(v, u, tot);
        return u;
    }

    void collect(int u, int p, int d, int c) {
        path[u].push_back({c, d});
        for (int v : g[u]) if (v != p && !dead[v]) collect(v, u, d + 1, c);
    }

    int build(int entry, int p) {
        dfs_sz(entry, 0);
        int c = find(entry, 0, sz[entry]);
        dead[c] = 1; cpar[c] = p; clev[c] = p ? clev[p] + 1 : 0;
        collect(c, 0, 0, c);
        for (int v : g[c]) if (!dead[v]) build(v, c);
        return c;
    }

    void toggle(int u) {
        active[u] ^= 1;
        for (auto [c, d] : path[u]) {
            if (active[u]) bag[c].insert(d);
            else bag[c].erase(bag[c].find(d));
        }
    }

    int query(int u) const {
        int ans = INF;
        for (auto [c, d] : path[u])
            if (!bag[c].empty()) ans = min(ans, d + *bag[c].begin());
        return ans;
    }
};
