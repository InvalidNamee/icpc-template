using ll = long long;

struct VirtualTree {
    using Edge = pair<ll, int>; // {边权, 终点}

    int n, lg = 1, tim = 0;
    const vector<vector<Edge>>& g;
    vector<int> up, dep, tin, tout, nodes, stk, buf;
    vector<ll> dis;
    vector<vector<Edge>> vt;

    VirtualTree(const vector<vector<Edge>>& g, int root = 1)
        : n((int)g.size() - 1), g(g), dep(n + 1), tin(n + 1),
          tout(n + 1), dis(n + 1), vt(n + 1) {
        while ((1LL << lg) <= n) lg++;
        up.resize((n + 1) * lg);
        nodes.reserve(64), stk.reserve(64), buf.reserve(64);
        init(root);
    }

    int& U(int u, int j) { return up[u * lg + j]; }
    int U(int u, int j) const { return up[u * lg + j]; }

    void init(int root) {
        vector<int> par(n + 1), st;
        st.reserve(n * 2);
        par[root] = root;
        st.push_back(root);
        while (!st.empty()) {
            int x = st.back();
            st.pop_back();
            if (x < 0) {
                tout[-x] = tim;
                continue;
            }
            int u = x;
            tin[u] = ++tim;
            U(u, 0) = par[u];
            for (int j = 1; j < lg; j++)
                U(u, j) = U(U(u, j - 1), j - 1);
            st.push_back(-u);
            for (auto it = g[u].rbegin();
                 it != g[u].rend(); it++) {
                auto [w, v] = *it;
                if (v == par[u]) continue;
                par[v] = u;
                dep[v] = dep[u] + 1;
                dis[v] = dis[u] + w;
                st.push_back(v);
            }
        }
    }

    bool ancestor(int u, int v) const {
        return tin[u] <= tin[v] && tin[v] <= tout[u];
    }

    int lca(int u, int v) const {
        if (ancestor(u, v)) return u;
        if (ancestor(v, u)) return v;
        for (int j = lg - 1; j >= 0; j--) {
            int p = U(u, j);
            if (!ancestor(p, v)) u = p;
        }
        return U(u, 0);
    }

    ll dist(int u, int v) const {
        int p = lca(u, v);
        return dis[u] + dis[v] - 2 * dis[p];
    }

    void link(int u, int v) {
        vt[u].push_back({dis[v] - dis[u], v});
    }

    template<class Vec>
    int build(const Vec& key) {
        for (int u : nodes) vt[u].clear();
        nodes.clear(), stk.clear(), buf.clear();
        if (key.empty()) return 0;

        int k = key.size();
        if ((int)buf.capacity() < k) buf.reserve(k);
        if ((int)nodes.capacity() < k * 2)
            nodes.reserve(k * 2);
        if ((int)stk.capacity() < k * 2)
            stk.reserve(k * 2);
        for (auto u : key) buf.push_back((int)u);
        sort(buf.begin(), buf.end(), [&](int u, int v) {
            return tin[u] < tin[v];
        });
        buf.erase(unique(buf.begin(), buf.end()), buf.end());

        stk.push_back(buf[0]);
        nodes.push_back(buf[0]);
        for (int i = 1; i < (int)buf.size(); i++) {
            int u = buf[i], p = lca(u, stk.back());
            while (stk.size() >= 2 &&
                   dep[stk[stk.size() - 2]] >= dep[p]) {
                link(stk[stk.size() - 2], stk.back());
                stk.pop_back();
            }
            if (stk.back() != p) {
                link(p, stk.back());
                stk.pop_back();
                stk.push_back(p);
                nodes.push_back(p);
            }
            stk.push_back(u);
            nodes.push_back(u);
        }
        while (stk.size() > 1) {
            link(stk[stk.size() - 2], stk.back());
            stk.pop_back();
        }
        return stk[0];
    }
};
