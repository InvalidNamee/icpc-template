using ll = long long;

struct SegmentTreeBeats {
    static constexpr ll INF = 1LL << 60;

    struct Node {
        ll sum = 0, add = 0;
        ll mx = -INF, smx = -INF;
        ll mn = INF, smn = INF;
        int mxc = 0, mnc = 0;
    };

    int n;
    vector<Node> tr;

    SegmentTreeBeats(const vector<ll>& a) : n(a.size()), tr(n * 4) {
        build(1, 0, n - 1, a);
    }

    Node merge_node(const Node& a, const Node& b) {
        Node c;
        c.sum = a.sum + b.sum;
        if (a.mx == b.mx) {
            c.mx = a.mx, c.mxc = a.mxc + b.mxc;
            c.smx = max(a.smx, b.smx);
        } else if (a.mx > b.mx) {
            c.mx = a.mx, c.mxc = a.mxc;
            c.smx = max(a.smx, b.mx);
        } else {
            c.mx = b.mx, c.mxc = b.mxc;
            c.smx = max(a.mx, b.smx);
        }
        if (a.mn == b.mn) {
            c.mn = a.mn, c.mnc = a.mnc + b.mnc;
            c.smn = min(a.smn, b.smn);
        } else if (a.mn < b.mn) {
            c.mn = a.mn, c.mnc = a.mnc;
            c.smn = min(a.smn, b.mn);
        } else {
            c.mn = b.mn, c.mnc = b.mnc;
            c.smn = min(a.mn, b.smn);
        }
        return c;
    }

    void build(int u, int l, int r, const vector<ll>& a) {
        if (l == r) {
            tr[u].sum = tr[u].mx = tr[u].mn = a[l];
            tr[u].mxc = tr[u].mnc = 1;
            return;
        }
        int m = (l + r) / 2;
        build(u * 2, l, m, a);
        build(u * 2 + 1, m + 1, r, a);
        tr[u] = merge_node(tr[u * 2], tr[u * 2 + 1]);
    }

    void apply_add(int u, int len, ll x) {
        Node& p = tr[u];
        p.sum += x * len;
        p.mx += x, p.mn += x;
        if (p.smx != -INF) p.smx += x;
        if (p.smn != INF) p.smn += x;
        p.add += x;
    }

    void apply_chmin(int u, ll x) {
        Node& p = tr[u];
        p.sum += (x - p.mx) * p.mxc;
        if (p.mn == p.mx) p.mn = x;
        else if (p.smn == p.mx) p.smn = x;
        p.mx = x;
    }

    void apply_chmax(int u, ll x) {
        Node& p = tr[u];
        p.sum += (x - p.mn) * p.mnc;
        if (p.mx == p.mn) p.mx = x;
        else if (p.smx == p.mn) p.smx = x;
        p.mn = x;
    }

    void push(int u, int l, int r) {
        int m = (l + r) / 2;
        if (tr[u].add) {
            apply_add(u * 2, m - l + 1, tr[u].add);
            apply_add(u * 2 + 1, r - m, tr[u].add);
            tr[u].add = 0;
        }
        if (tr[u * 2].mx > tr[u].mx)
            apply_chmin(u * 2, tr[u].mx);
        if (tr[u * 2 + 1].mx > tr[u].mx)
            apply_chmin(u * 2 + 1, tr[u].mx);
        if (tr[u * 2].mn < tr[u].mn)
            apply_chmax(u * 2, tr[u].mn);
        if (tr[u * 2 + 1].mn < tr[u].mn)
            apply_chmax(u * 2 + 1, tr[u].mn);
    }

    void pull(int u) {
        tr[u] = merge_node(tr[u * 2], tr[u * 2 + 1]);
    }

    void add(int u, int l, int r, int ql, int qr, ll x) {
        if (ql <= l && r <= qr)
            return apply_add(u, r - l + 1, x);
        push(u, l, r);
        int m = (l + r) / 2;
        if (ql <= m) add(u * 2, l, m, ql, qr, x);
        if (m < qr)
            add(u * 2 + 1, m + 1, r, ql, qr, x);
        pull(u);
    }

    void chmin(int u, int l, int r, int ql, int qr, ll x) {
        if (tr[u].mx <= x) return;
        if (ql <= l && r <= qr && tr[u].smx < x)
            return apply_chmin(u, x);
        push(u, l, r);
        int m = (l + r) / 2;
        if (ql <= m) chmin(u * 2, l, m, ql, qr, x);
        if (m < qr)
            chmin(u * 2 + 1, m + 1, r, ql, qr, x);
        pull(u);
    }

    void chmax(int u, int l, int r, int ql, int qr, ll x) {
        if (tr[u].mn >= x) return;
        if (ql <= l && r <= qr && tr[u].smn > x)
            return apply_chmax(u, x);
        push(u, l, r);
        int m = (l + r) / 2;
        if (ql <= m) chmax(u * 2, l, m, ql, qr, x);
        if (m < qr)
            chmax(u * 2 + 1, m + 1, r, ql, qr, x);
        pull(u);
    }

    ll query_sum(int u, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tr[u].sum;
        push(u, l, r);
        int m = (l + r) / 2;
        ll res = 0;
        if (ql <= m)
            res += query_sum(u * 2, l, m, ql, qr);
        if (m < qr)
            res += query_sum(u * 2 + 1, m + 1, r, ql, qr);
        return res;
    }

    ll query_min(int u, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tr[u].mn;
        push(u, l, r);
        int m = (l + r) / 2;
        ll res = INF;
        if (ql <= m)
            res = min(res, query_min(u * 2, l, m, ql, qr));
        if (m < qr)
            res = min(res, query_min(
                u * 2 + 1, m + 1, r, ql, qr
            ));
        return res;
    }

    ll query_max(int u, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return tr[u].mx;
        push(u, l, r);
        int m = (l + r) / 2;
        ll res = -INF;
        if (ql <= m)
            res = max(res, query_max(u * 2, l, m, ql, qr));
        if (m < qr)
            res = max(res, query_max(
                u * 2 + 1, m + 1, r, ql, qr
            ));
        return res;
    }

    void add(int l, int r, ll x) {
        add(1, 0, n - 1, l, r, x);
    }
    void chmin(int l, int r, ll x) {
        chmin(1, 0, n - 1, l, r, x);
    }
    void chmax(int l, int r, ll x) {
        chmax(1, 0, n - 1, l, r, x);
    }
    ll query_sum(int l, int r) {
        return query_sum(1, 0, n - 1, l, r);
    }
    ll query_min(int l, int r) {
        return query_min(1, 0, n - 1, l, r);
    }
    ll query_max(int l, int r) {
        return query_max(1, 0, n - 1, l, r);
    }
};
