struct LineHull {
    struct Line {
        long long k, b;
        long long get(long long x) const { return k * x + b; }
    };

    vector<Line> q;

    bool bad(const Line& a, const Line& b, const Line& c) {
        return (__int128)(a.b - b.b) * (c.k - b.k) >=
               (__int128)(b.b - c.b) * (b.k - a.k);
    }

    void add(long long k, long long b) {
        Line nw{k, b};
        if (!q.empty() && q.back().k == k) {
            if (q.back().b >= b) return;
            q.pop_back();
        }
        while (q.size() >= 2 && bad(q[q.size() - 2], q.back(), nw))
            q.pop_back();
        q.push_back(nw);
    }

    long long query(long long x) const {
        int l = 0, r = (int)q.size() - 1;
        while (l < r) {
            int m = (l + r) / 2;
            if (q[m].get(x) <= q[m + 1].get(x)) l = m + 1;
            else r = m;
        }
        return q[l].get(x);
    }
};
