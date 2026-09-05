using ll = long long;

struct DynamicDP {
    static constexpr ll NINF = -(1LL << 60);

    struct Mat {
        ll a[2][2]{{NINF, NINF}, {NINF, NINF}};

        Mat operator*(const Mat& b) const {
            Mat c;
            for (int i = 0; i < 2; i++)
                for (int j = 0; j < 2; j++)
                    for (int k = 0; k < 2; k++)
                        c.a[i][j] = max(
                            c.a[i][j],
                            a[i][k] + b.a[k][j]
                        );
            return c;
        }
    };

    int n, rt = 1, tim = 0;
    vector<vector<int>> adj;
    vector<int> fa, dep, siz, son, dfn, rev, top, tail;
    vector<ll> w, f, g;
    vector<Mat> tr;

    DynamicDP(int n) : n(n), adj(n + 1),
        fa(n + 1), dep(n + 1), siz(n + 1),
        son(n + 1), dfn(n + 1), rev(n + 1),
        top(n + 1), tail(n + 1), w(n + 1),
        f(n + 1), g(n + 1), tr(n * 4 + 4) {}

    void add_edge(int x, int y) {
        adj[x].push_back(y);
        adj[y].push_back(x);
    }

    void set_weight(int x, ll v) { w[x] = v; }

    void dfs1(int x) {
        siz[x] = 1;
        f[x] = g[x] = 0;
        for (int y : adj[x]) if (y != fa[x]) {
            fa[y] = x;
            dep[y] = dep[x] + 1;
            dfs1(y);
            siz[x] += siz[y];
            if (siz[y] > siz[son[x]]) son[x] = y;
            f[x] += f[y];
        }
        f[x] = max(f[x], w[x]);
        for (int y : adj[x])
            if (y != fa[x] && y != son[x]) g[x] += f[y];
    }

    void dfs2(int x, int h) {
        dfn[x] = ++tim, rev[tim] = x, top[x] = h;
        if (son[x]) dfs2(son[x], h);
        else tail[h] = x;
        for (int y : adj[x])
            if (y != fa[x] && y != son[x]) dfs2(y, y);
    }

    Mat value(int x) const {
        Mat m;
        m.a[0][0] = g[x];
        m.a[1][0] = w[x];
        m.a[1][1] = 0;
        return m;
    }

    void build_seg(int u, int l, int r) {
        if (l == r) return tr[u] = value(rev[l]), void();
        int m = (l + r) / 2;
        build_seg(u * 2, l, m);
        build_seg(u * 2 + 1, m + 1, r);
        tr[u] = tr[u * 2 + 1] * tr[u * 2];
    }

    void modify_seg(int u, int l, int r, int p) {
        if (l == r) return tr[u] = value(rev[l]), void();
        int m = (l + r) / 2;
        if (p <= m) modify_seg(u * 2, l, m, p);
        else modify_seg(u * 2 + 1, m + 1, r, p);
        tr[u] = tr[u * 2 + 1] * tr[u * 2];
    }

    Mat query_seg(int u, int l, int r, int ql, int qr) const {
        if (ql <= l && r <= qr) return tr[u];
        int m = (l + r) / 2;
        Mat res;
        res.a[0][0] = res.a[1][1] = 0;
        if (m < qr)
            res = query_seg(
                u * 2 + 1, m + 1, r, ql, qr
            );
        if (ql <= m)
            res = res * query_seg(
                u * 2, l, m, ql, qr
            );
        return res;
    }

    ll chain_value(int h) const {
        Mat m = query_seg(1, 1, n, dfn[h], dfn[tail[h]]);
        return max(m.a[0][0], m.a[1][0]);
    }

    void build(int root = 1) {
        rt = root, tim = 0;
        fill(son.begin(), son.end(), 0);
        fa[root] = 0, dep[root] = 1;
        dfs1(root);
        dfs2(root, root);
        build_seg(1, 1, n);
    }

    ll modify(int x, ll v) {
        w[x] = v;
        while (x) {
            int h = top[x], p = fa[h];
            ll old = chain_value(h);
            modify_seg(1, 1, n, dfn[x]);
            ll now = chain_value(h);
            if (p) g[p] += now - old;
            x = p;
        }
        return answer();
    }

    ll answer() const { return chain_value(top[rt]); }
};
