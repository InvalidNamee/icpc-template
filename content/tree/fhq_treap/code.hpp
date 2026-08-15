using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;

struct FHQ {
    struct Node {
        int l = 0, r = 0, sz = 0, cnt = 0, key = 0;
        unsigned pri = 0;
    };
    vector<Node> t = {Node()};
    int root = 0;
    unsigned seed = 712367821;

    unsigned rnd() {
        seed ^= seed << 13; seed ^= seed >> 17; seed ^= seed << 5;
        return seed;
    }

    int size(int p) const { return p ? t[p].sz : 0; }

    void pull(int p) { t[p].sz = size(t[p].l) + size(t[p].r) + t[p].cnt; }

    int node(int x) {
        t.push_back({0, 0, 1, 1, x, rnd()});
        return (int)t.size() - 1;
    }

    int merge(int a, int b) {
        if (!a || !b) return a | b;
        if (t[a].pri < t[b].pri) return t[a].r = merge(t[a].r, b), pull(a), a;
        return t[b].l = merge(a, t[b].l), pull(b), b;
    }

    void split_lt(int p, int x, int& a, int& b) {
        if (!p) return void(a = b = 0);
        if (t[p].key < x) a = p, split_lt(t[p].r, x, t[p].r, b), pull(a);
        else b = p, split_lt(t[p].l, x, a, t[p].l), pull(b);
    }

    void split_le(int p, int x, int& a, int& b) {
        if (!p) return void(a = b = 0);
        if (t[p].key <= x) a = p, split_le(t[p].r, x, t[p].r, b), pull(a);
        else b = p, split_le(t[p].l, x, a, t[p].l), pull(b);
    }

    void insert(int x) {
        int a, b, c;
        split_lt(root, x, a, b); split_le(b, x, b, c);
        if (b) t[b].cnt++, pull(b); else b = node(x);
        root = merge(merge(a, b), c);
    }

    void erase(int x) {
        int a, b, c;
        split_lt(root, x, a, b); split_le(b, x, b, c);
        if (b && t[b].cnt > 1) t[b].cnt--, pull(b);
        else if (b) b = merge(t[b].l, t[b].r);
        root = merge(merge(a, b), c);
    }

    int rank(int x) const {
        int p = root, ans = 1;
        while (p) {
            if (x <= t[p].key) p = t[p].l;
            else ans += size(t[p].l) + t[p].cnt, p = t[p].r;
        }
        return ans;
    }

    optional<int> kth(int k) const {
        if (k < 1 || k > size(root)) return {};
        int p = root;
        while (p) {
            if (k <= size(t[p].l)) p = t[p].l;
            else if (k <= size(t[p].l) + t[p].cnt) return t[p].key;
            else k -= size(t[p].l) + t[p].cnt, p = t[p].r;
        }
        return {};
    }

    optional<int> pre(int x) const {
        int p = root, ans = 0;
        while (p) {
            if (t[p].key < x) ans = p, p = t[p].r;
            else p = t[p].l;
        }
        if (!ans) return {};
        return t[ans].key;
    }

    optional<int> nxt(int x) const {
        int p = root, ans = 0;
        while (p) {
            if (t[p].key > x) ans = p, p = t[p].l;
            else p = t[p].r;
        }
        if (!ans) return {};
        return t[ans].key;
    }
};
