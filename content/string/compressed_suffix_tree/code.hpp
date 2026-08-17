#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using ll = long long;

struct SuffixTree {
    struct Node {
        int par = -1, dep = 0, rep = 0;
        int suffix = 0, rank = 0;
    };

    int n;
    string s;
    vector<int> sa, leaf, cnt, lo, hi, mn, mx;
    vector<Node> t;
    vector<vector<int>> g;

    SuffixTree(const string& s, const SA& a)
        : n((int)s.size() - 1), s(s), sa(a.sa), leaf(n + 1) {
        node(0, 1);
        vector<int> stk{0};
        for (int i = 1; i <= n; i++) {
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
            int v = node(n - sa[i] + 1, sa[i], sa[i], i);
            leaf[sa[i]] = v;
            link(stk.back(), v);
            stk.push_back(v);
        }
        pull();
    }

    int node(int dep, int rep, int suffix = 0, int rank = 0) {
        int u = t.size();
        t.push_back({-1, dep, rep, suffix, rank});
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
        lo.assign(sz, n + 1);
        hi.assign(sz, 0);
        mn.assign(sz, n + 1);
        mx.assign(sz, 0);
        vector<int> ord{0};
        for (int i = 0; i < (int)ord.size(); i++)
            for (int v : g[ord[i]]) ord.push_back(v);
        for (int v = 1; v < sz; v++) if (t[v].suffix) {
            cnt[v] = 1;
            lo[v] = hi[v] = t[v].rank;
            mn[v] = mx[v] = t[v].suffix;
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
        int u = 0, i = 1, m = (int)p.size() - 1;
        while (i <= m) {
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
            for (int j = l; j <= r && i <= m; j++, i++)
                if (s[j] != p[i]) return -1;
            if (i > m) return v;
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
        return v == -1 ? pair<int, int>{1, 0}
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
