using ll = long long;

struct BFlow {
    // 原图顶点编号：1..n（1-based）；原边编号：1..m（1-based）
    struct R { int u, p; ll r; };

    int n;
    Dinic d;
    vector<ll> b;
    vector<R> e;

    BFlow(int n) : n(n), d(n + 2), b(n + 1), e(1) {}

    int add(int u, int v, ll l, ll r) {
        int id = e.size();
        e.push_back({u, (int)d.g[u].size(), r});
        d.add(u, v, r - l);
        b[u] -= l;
        b[v] += l;
        return id;
    }

    bool ok(int s = -1, int t = -1) {
        const ll inf = 1LL << 60;
        int S = n + 1, T = n + 2;
        if (s != -1) d.add(t, s, inf);
        ll need = 0;
        for (int i = 1; i <= n; i++) {
            if (b[i] > 0) d.add(S, i, b[i]), need += b[i];
            if (b[i] < 0) d.add(i, T, -b[i]);
        }
        return d.flow(S, T) == need;
    }

    // ok() 返回 true 后，获取第 id 条原边的实际流量
    ll get(int id) {
        auto [u, p, r] = e[id];
        return r - d.g[u][p].c;
    }
};
