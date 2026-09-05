using Info = ll;
const Info E = 0; // 空信息的单位元

// 按路径从左到右合并，必须满足结合律；比赛时修改这里
Info merge(Info a, Info b) {
    return a + b;
}

struct LCT {
    struct Node {
        int ch[2] = {}, fa = 0, rev = 0, sz = 1;
        Info val = E, fwd = E, bwd = E;
    };
    vector<Node> t;

    LCT(int n) : t(n + 1) { t[0].sz = 0; }

    bool isroot(int x) const {
        int f = t[x].fa;
        return !f || (t[f].ch[0] != x && t[f].ch[1] != x);
    }

    void pushup(int x) {
        int l = t[x].ch[0], r = t[x].ch[1];
        t[x].sz = t[l].sz + t[r].sz + 1;
        t[x].fwd = merge(merge(t[l].fwd, t[x].val), t[r].fwd);
        t[x].bwd = merge(merge(t[r].bwd, t[x].val), t[l].bwd);
    }

    void reverse(int x) {
        if (!x) return;
        swap(t[x].ch[0], t[x].ch[1]);
        swap(t[x].fwd, t[x].bwd);
        t[x].rev ^= 1;
    }

    void pushdown(int x) {
        if (!t[x].rev) return;
        reverse(t[x].ch[0]);
        reverse(t[x].ch[1]);
        t[x].rev = 0;
    }

    void rotate(int x) {
        int y = t[x].fa, z = t[y].fa;
        int k = (t[y].ch[1] == x);
        int w = t[x].ch[k ^ 1];
        if (!isroot(y)) t[z].ch[t[z].ch[1] == y] = x;
        t[x].fa = z; t[x].ch[k ^ 1] = y; t[y].fa = x;
        t[y].ch[k] = w; if (w) t[w].fa = y;
        pushup(y); pushup(x);
    }

    void splay(int x) {
        static vector<int> stk;
        stk.clear();
        int u = x;
        stk.push_back(u);
        while (!isroot(u)) u = t[u].fa, stk.push_back(u);
        while (!stk.empty()) pushdown(stk.back()), stk.pop_back();
        while (!isroot(x)) {
            int y = t[x].fa, z = t[y].fa;
            if (!isroot(y)) {
                bool zigzig = (t[y].ch[1] == x) ==
                              (t[z].ch[1] == y);
                rotate(zigzig ? y : x);
            }
            rotate(x);
        }
    }

    int access(int x) {
        int y = 0;
        for (int u = x; u; u = t[u].fa) {
            splay(u);
            t[u].ch[1] = y;
            pushup(u);
            y = u;
        }
        splay(x);
        return y;
    }

    void makeroot(int x) { access(x); reverse(x); }

    int findroot(int x) {
        access(x);
        while (pushdown(x), t[x].ch[0]) x = t[x].ch[0];
        splay(x);
        return x;
    }

    bool connected(int u, int v) {
        if (u == v) return true;
        makeroot(u);
        return findroot(v) == u;
    }

    bool link(int u, int v) {
        makeroot(u);
        if (findroot(v) == u) return false;
        t[u].fa = v;
        return true;
    }

    bool cut(int u, int v) {
        makeroot(u); access(v);
        if (t[v].ch[0] != u || t[u].ch[1]) return false;
        t[v].ch[0] = t[u].fa = 0; pushup(v);
        return true;
    }

    void split(int u, int v) { makeroot(u); access(v); }

    void set_value(int u, Info x) {
        access(u);
        t[u].val = x;
        pushup(u);
    }

    Info query(int u, int v) { split(u, v); return t[v].fwd; }
};
