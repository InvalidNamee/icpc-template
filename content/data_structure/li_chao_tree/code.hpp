using ll = long long;

struct LiChaoTree {
    static constexpr ll NEG = -(1LL << 62);

    struct Line {
        ll k = 0, b = NEG;
        ll get(ll x) const { return k * x + b; }
    };

    struct Node {
        Line line;
        int ls = 0, rs = 0;
        bool has = false;
    };

    ll L, R;
    vector<Node> tr;
    int root = 0;

    LiChaoTree(ll l, ll r) : L(l), R(r), tr(1) {}

    int new_node() {
        tr.push_back(Node());
        return (int)tr.size() - 1;
    }

    int insert_line(int u, ll l, ll r, Line nw) {
        if (!u) u = new_node();
        if (!tr[u].has) {
            tr[u].line = nw;
            tr[u].has = true;
            return u;
        }

        ll m = l + (r - l) / 2;
        bool lef = nw.get(l) > tr[u].line.get(l);
        bool mid = nw.get(m) > tr[u].line.get(m);
        if (mid) swap(nw, tr[u].line);
        if (l == r) return u;
        if (lef != mid)
            tr[u].ls = insert_line(tr[u].ls, l, m, nw);
        else
            tr[u].rs = insert_line(tr[u].rs, m + 1, r, nw);
        return u;
    }

    int insert_segment(int u, ll l, ll r, ll ql, ll qr, Line nw) {
        if (qr < l || r < ql) return u;
        if (!u) u = new_node();
        if (ql <= l && r <= qr) return insert_line(u, l, r, nw);
        ll m = l + (r - l) / 2;
        tr[u].ls = insert_segment(tr[u].ls, l, m, ql, qr, nw);
        tr[u].rs = insert_segment(tr[u].rs, m + 1, r, ql, qr, nw);
        return u;
    }

    void add_line(ll k, ll b) {
        root = insert_line(root, L, R, {k, b});
    }

    void add_segment(ll l, ll r, ll k, ll b) {
        l = max(l, L), r = min(r, R);
        if (l <= r) root = insert_segment(root, L, R, l, r, {k, b});
    }

    ll query(int u, ll l, ll r, ll x) const {
        if (!u) return NEG;
        ll ans = tr[u].has ? tr[u].line.get(x) : NEG;
        if (l == r) return ans;
        ll m = l + (r - l) / 2;
        if (x <= m) return max(ans, query(tr[u].ls, l, m, x));
        return max(ans, query(tr[u].rs, m + 1, r, x));
    }

    ll query(ll x) const {
        return query(root, L, R, x);
    }
};
