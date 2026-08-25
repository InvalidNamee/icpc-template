struct RollbackDSU {
    vector<int> fa, siz;
    vector<pair<int, int>> stk;

    void init(int n) {
        fa.resize(n + 1);
        siz.assign(n + 1, 1);
        iota(fa.begin(), fa.end(), 0);
        stk.clear();
    }

    int find(int x) const {
        while (x != fa[x]) x = fa[x];
        return x;
    }

    int snapshot() const { return stk.size(); }

    bool merge(int x, int y) {
        x = find(x), y = find(y);
        if (x == y) return false;
        if (siz[x] < siz[y]) swap(x, y);
        stk.push_back({y, siz[x]});
        fa[y] = x;
        siz[x] += siz[y];
        return true;
    }

    void rollback(int t) {
        while ((int)stk.size() > t) {
            auto [y, old_size] = stk.back();
            stk.pop_back();
            int x = fa[y];
            fa[y] = y;
            siz[x] = old_size;
        }
    }

    int size(int x) const { return siz[find(x)]; }
};
