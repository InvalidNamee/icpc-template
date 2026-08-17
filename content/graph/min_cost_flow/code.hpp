using ll = long long;

struct MCMF {
    struct E {
        int v, r;
        ll c, w;
    };

    int n;
    vector<vector<E>> g;

    MCMF(int n) : n(n), g(n) {}

    void add(int u, int v, ll c, ll w) {
        E a{v, (int) g[v].size(), c, w};
        E b{u, (int) g[u].size(), 0, -w};
        g[u].push_back(a);
        g[v].push_back(b);
    }

    pair<ll, ll> flow(int s, int t) {
        const ll inf = numeric_limits<ll>::max() / 4;
        ll mf = 0, mc = 0;
        vector<ll> d(n);
        vector<int> in(n), pv(n), pe(n);
        while (true) {
            fill(d.begin(), d.end(), inf);
            fill(in.begin(), in.end(), 0);
            queue<int> q;
            d[s] = 0;
            q.push(s);
            in[s] = 1;
            while (!q.empty()) {
                int u = q.front();
                q.pop();
                in[u] = 0;
                for (int i = 0; i < (int) g[u].size(); i++) {
                    E &e = g[u][i];
                    if (!e.c || d[e.v] <= d[u] + e.w) continue;
                    d[e.v] = d[u] + e.w;
                    pv[e.v] = u;
                    pe[e.v] = i;
                    if (!in[e.v]) q.push(e.v), in[e.v] = 1;
                }
            }
            if (d[t] == inf) break;
            ll f = inf;
            for (int v = t; v != s; v = pv[v])
                f = min(f, g[pv[v]][pe[v]].c);
            for (int v = t; v != s; v = pv[v]) {
                E &e = g[pv[v]][pe[v]];
                e.c -= f;
                g[v][e.r].c += f;
            }
            mf += f;
            mc += f * d[t];
        }
        return {mf, mc};
    }
};
