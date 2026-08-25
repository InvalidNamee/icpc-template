using ll = long long;

struct Dinic {
    // 顶点编号：1..n（1-based）；邻接表位置 r 为内部 0-based 下标
    struct E {
        int v, r;
        ll c;
    };

    int n;
    vector<vector<E>> g;
    vector<int> dep, cur;

    Dinic(int n) : n(n), g(n + 1), dep(n + 1), cur(n + 1) {}

    void add(int u, int v, ll c) {
        E a{v, (int) g[v].size(), c};
        E b{u, (int) g[u].size(), 0};
        g[u].push_back(a);
        g[v].push_back(b);
    }

    bool bfs(int s, int t) {
        fill(dep.begin(), dep.end(), -1);
        queue<int> q;
        dep[s] = 0;
        q.push(s);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (auto &e : g[u]) {
                if (e.c && dep[e.v] == -1) {
                    dep[e.v] = dep[u] + 1;
                    q.push(e.v);
                }
            }
        }
        return dep[t] != -1;
    }

    ll dfs(int u, int t, ll f) {
        if (u == t || !f) return f;
        for (int &i = cur[u]; i < (int) g[u].size(); i++) {
            E &e = g[u][i];
            if (!e.c || dep[e.v] != dep[u] + 1) continue;
            ll x = dfs(e.v, t, min(f, e.c));
            if (!x) continue;
            e.c -= x;
            g[e.v][e.r].c += x;
            return x;
        }
        return 0;
    }

    ll flow(int s, int t) {
        const ll inf = numeric_limits<ll>::max() / 4;
        ll ans = 0, f;
        while (bfs(s, t)) {
            fill(cur.begin(), cur.end(), 0);
            while ((f = dfs(s, t, inf))) ans += f;
        }
        return ans;
    }
};
