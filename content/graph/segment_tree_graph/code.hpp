using ll = long long;

struct SegGraph {
    struct E { int v; ll w; };
    int n, s = 1, o;
    vector<vector<E>> g;

    SegGraph(int n) : n(n) {
        while (s < n) s *= 2;
        o = 2 * s;
        g.resize(4 * s);
        for (int p = 1; p < s; p++) {
            add(p, p * 2, 0);
            add(p, p * 2 + 1, 0);
            add(o + p * 2, o + p, 0);
            add(o + p * 2 + 1, o + p, 0);
        }
        for (int i = 1; i <= n; i++) add(id(i), o + id(i), 0);
    }

    int id(int u) { return s + u - 1; }
    int node() { g.push_back({}); return (int)g.size() - 1; }
    void add(int u, int v, ll w) { g[u].push_back({v, w}); }
    void edge(int u, int v, ll w) { add(id(u), id(v), w); }

    // 扩展图结点 u 向原图区间 [l, r] 连边
    void from(int u, int l, int r, ll w) {
        for (l += s - 1, r += s; l < r; l /= 2, r /= 2) {
            if (l & 1) add(u, l++, w);
            if (r & 1) add(u, --r, w);
        }
    }

    // 原图区间 [l, r] 向扩展图结点 v 连边
    void to(int l, int r, int v, ll w) {
        for (l += s - 1, r += s; l < r; l /= 2, r /= 2) {
            if (l & 1) add(o + l++, v, w);
            if (r & 1) add(o + --r, v, w);
        }
    }

    void point_range(int u, int l, int r, ll w) {
        from(id(u), l, r, w);
    }
    void range_point(int l, int r, int v, ll w) {
        to(l, r, id(v), w);
    }
    void range_range(int l1, int r1, int l2, int r2, ll w) {
        int x = node();
        to(l1, r1, x, w);
        from(x, l2, r2, 0);
    }

};
