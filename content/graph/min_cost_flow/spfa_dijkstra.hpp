using ll = long long;

struct MCMF {
    // 顶点编号：1..n；每个版本独立复制使用
    struct E {
        int v, r;
        ll c, w;
    };

    static constexpr ll inf = numeric_limits<ll>::max() / 4;
    int n;
    vector<vector<E>> g;
    vector<ll> h;

    MCMF(int n) : n(n), g(n + 1), h(n + 1) {}

    void add(int u, int v, ll c, ll w) {
        int a = (int) g[u].size(), b = (int) g[v].size();
        g[u].push_back({v, b + (u == v), c, w});
        g[v].push_back({u, a, 0, -w});
    }

    // 初始残量网络允许负费用边，但不能有负费用环
    void init(int s) {
        fill(h.begin(), h.end(), inf);
        vector<int> in(n + 1);
        queue<int> q;
        h[s] = 0;
        q.push(s);
        in[s] = 1;
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            in[u] = 0;
            for (auto &e : g[u]) {
                if (!e.c || h[e.v] <= h[u] + e.w) continue;
                h[e.v] = h[u] + e.w;
                if (!in[e.v]) q.push(e.v), in[e.v] = 1;
            }
        }
        for (int v = 1; v <= n; v++)
            if (h[v] == inf) h[v] = 0;
    }

    // 返回本次新增的 {流量, 费用}；s != t，limit >= 0
    pair<ll, ll> flow(int s, int t, ll limit = inf) {
        init(s);
        ll mf = 0, mc = 0;
        vector<ll> d(n + 1);
        vector<int> pv(n + 1), pe(n + 1);
        while (mf < limit) {
            fill(d.begin(), d.end(), inf);
            priority_queue<pair<ll, int>, vector<pair<ll, int>>,
                           greater<pair<ll, int>>> q;
            d[s] = 0;
            q.push({0, s});
            while (!q.empty()) {
                auto [du, u] = q.top();
                q.pop();
                if (du != d[u]) continue;
                for (int i = 0; i < (int) g[u].size(); i++) {
                    E &e = g[u][i];
                    ll nd = du + e.w + h[u] - h[e.v];
                    if (!e.c || d[e.v] <= nd) continue;
                    d[e.v] = nd;
                    pv[e.v] = u;
                    pe[e.v] = i;
                    q.push({nd, e.v});
                }
            }
            if (d[t] == inf) break;
            for (int v = 1; v <= n; v++)
                if (d[v] != inf) h[v] += d[v];
            ll f = limit - mf;
            for (int v = t; v != s; v = pv[v])
                f = min(f, g[pv[v]][pe[v]].c);
            for (int v = t; v != s; v = pv[v]) {
                E &e = g[pv[v]][pe[v]];
                e.c -= f;
                g[v][e.r].c += f;
            }
            mf += f;
            mc += f * (h[t] - h[s]);
        }
        return {mf, mc};
    }
};
