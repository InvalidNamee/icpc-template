struct SuffixTree {
    struct Node {
        int par = -1; // 父结点
        int dep = 0;  // 根到该结点的字符串长度
        int rep = 0;  // 一个代表后缀的起点
        int suf = -1; // 叶子对应的后缀起点，内部结点为 -1
        int rank = -1; // 叶子对应的 SA 排名，内部结点为 -1
    };

    int n;
    string s;
    vector<int> sa, leaf;
    vector<int> cnt, lo, hi; // 子树叶数、最小和最大 SA 排名
    vector<int> mn, mx;      // 子树内最小和最大后缀起点
    vector<Node> t;
    vector<vector<int>> g;

    SuffixTree(const string& s, const SA& a)
        : n(s.size()), s(s), sa(a.sa), leaf(n, -1) {
        node(0, 0);
        vector<int> stk{0};
        for (int i = 0; i < n; i++) {
            int h = a.height[i];
            while (t[stk.back()].dep > h) stk.pop_back();
            if (t[stk.back()].dep < h) {
                int p = stk.back();
                int v = g[p].back();
                g[p].pop_back();
                int u = node(h, t[v].rep);
                link(p, u);
                link(u, v);
                stk.push_back(u);
            }
            int v = node(n - sa[i], sa[i], sa[i], i);
            leaf[sa[i]] = v;
            link(stk.back(), v);
            stk.push_back(v);
        }
        pull();
    }

    int node(int dep, int rep, int suf = -1, int rank = -1) {
        int u = t.size();
        t.push_back({-1, dep, rep, suf, rank});
        g.push_back({});
        return u;
    }

    void link(int u, int v) {
        t[v].par = u;
        g[u].push_back(v);
    }

    // 父结点到 v 的边标记为原串闭区间 [l, r]
    pair<int, int> edge(int v) {
        int p = t[v].par;
        return {t[v].rep + t[p].dep, t[v].rep + t[v].dep - 1};
    }

    // 根到 v 的路径字符串可取原串闭区间 [l, r]
    pair<int, int> path(int v) {
        return {t[v].rep, t[v].rep + t[v].dep - 1};
    }

    void pull() {
        int sz = t.size();
        cnt.assign(sz, 0);
        lo.assign(sz, n);
        hi.assign(sz, -1);
        mn.assign(sz, n);
        mx.assign(sz, -1);
        vector<int> ord{0};
        for (int i = 0; i < (int)ord.size(); i++)
            for (int v : g[ord[i]]) ord.push_back(v);
        for (int v = 1; v < sz; v++) if (t[v].suf != -1) {
            cnt[v] = 1;
            lo[v] = hi[v] = t[v].rank;
            mn[v] = mx[v] = t[v].suf;
        }
        for (int i = (int)ord.size() - 1; i > 0; i--) {
            int v = ord[i], p = t[v].par;
            cnt[p] += cnt[v];
            lo[p] = min(lo[p], lo[v]);
            hi[p] = max(hi[p], hi[v]);
            mn[p] = min(mn[p], mn[v]);
            mx[p] = max(mx[p], mx[v]);
        }
    }

    // 返回模式串所在边的下端结点；不存在时返回 -1
    int find(const string& p) {
        int u = 0, i = 0, m = p.size();
        while (i < m) {
            int v = -1, l = 0, r = -1;
            for (int x : g[u]) {
                auto e = edge(x);
                if (s[e.first] == p[i]) {
                    v = x;
                    l = e.first;
                    r = e.second;
                    break;
                }
            }
            if (v == -1) return -1;
            for (int j = l; j <= r && i < m; j++, i++)
                if (s[j] != p[i]) return -1;
            if (i == m) return v;
            u = v;
        }
        return u;
    }

    int occurrences(const string& p) {
        int v = find(p);
        return v == -1 ? 0 : cnt[v];
    }

    // 返回匹配后缀在 SA 中的闭区间，无匹配时 L > R
    pair<int, int> match(const string& p) {
        int v = find(p);
        return v == -1 ? pair<int, int>{0, -1}
                       : pair<int, int>{lo[v], hi[v]};
    }

    ll distinct() {
        ll ans = 0;
        for (int v = 1; v < (int)t.size(); v++)
            ans += t[v].dep - t[t[v].par].dep;
        return ans;
    }

    int repeat_at_least(int k) {
        int ans = 0;
        for (int v = 1; v < (int)t.size(); v++)
            if (cnt[v] >= k) ans = max(ans, t[v].dep);
        return ans;
    }

    int non_overlap_repeat() {
        int ans = 0;
        for (int v = 1; v < (int)t.size(); v++)
            ans = max(ans, min(t[v].dep, mx[v] - mn[v]));
        return ans;
    }
};
