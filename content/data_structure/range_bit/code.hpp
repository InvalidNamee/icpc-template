using ll = long long;

struct RangeBIT {
    int n;
    vector<ll> t1, t2;

    void init(int n) {
        this->n = n;
        t1.assign(n + 1, 0);
        t2.assign(n + 1, 0);
    }

    void add(vector<ll>& tr, int x, ll v) {
        for (; x <= n; x += x & -x) tr[x] += v;
    }

    ll sum(const vector<ll>& tr, int x) const {
        ll res = 0;
        for (; x; x -= x & -x) res += tr[x];
        return res;
    }

    void add(int l, int r, ll v) {
        add(t1, l, v), add(t1, r + 1, -v);
        add(t2, l, v * (l - 1)), add(t2, r + 1, -v * r);
    }

    ll query(int x) const {
        return sum(t1, x) * x - sum(t2, x);
    }

    ll query(int l, int r) const {
        return query(r) - query(l - 1);
    }
};
