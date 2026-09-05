struct SAM {
    struct State {
        array<int, 26> ch{};
        int link = -1, len = 0, first = -1;
        ll occ = 0, dp = 0;
    };
    struct LCS {
        int len, l1, r1, l2, r2;
    };

    int n, last = 0;
    vector<State> st{1};
    vector<int> order, pref;

    SAM(const string& s) : n(s.size()), pref(n) {
        st.reserve(2 * n);
        for (int i = 0; i < n; i++) extend(s[i] - 'a', i);
        finish();
    }

    void extend(int c, int pos) {
        int cur = st.size();
        st.push_back({});
        st[cur].len = st[last].len + 1;
        st[cur].first = pos;
        st[cur].occ = 1;
        pref[pos] = cur;

        int p = last;
        while (p != -1 && !st[p].ch[c]) {
            st[p].ch[c] = cur;
            p = st[p].link;
        }
        if (p == -1) {
            st[cur].link = 0;
        } else {
            int q = st[p].ch[c];
            if (st[p].len + 1 == st[q].len) {
                st[cur].link = q;
            } else {
                int clone = st.size();
                st.push_back(st[q]);
                st[clone].len = st[p].len + 1;
                st[clone].occ = 0;
                while (p != -1 && st[p].ch[c] == q) {
                    st[p].ch[c] = clone;
                    p = st[p].link;
                }
                st[q].link = st[cur].link = clone;
            }
        }
        last = cur;
    }

    void finish() {
        int sz = st.size(), mx = 0;
        for (auto &x : st) mx = max(mx, x.len);
        vector<int> cnt(mx + 1);
        for (auto &x : st) cnt[x.len]++;
        for (int i = 1; i <= mx; i++) cnt[i] += cnt[i - 1];
        order.resize(sz);
        for (int v = sz - 1; v >= 0; v--)
            order[--cnt[st[v].len]] = v;

        for (int i = sz - 1; i > 0; i--) {
            int v = order[i];
            st[st[v].link].occ += st[v].occ;
        }

        const ll cap = 1LL << 62;
        for (int i = sz - 1; i >= 0; i--) {
            int u = order[i];
            for (int c = 0; c < 26; c++) if (st[u].ch[c]) {
                ll add = 1 + st[st[u].ch[c]].dp;
                st[u].dp = min(cap, st[u].dp + add);
            }
        }
    }

    int walk(const string& p) {
        int u = 0;
        for (char x : p) {
            int c = x - 'a';
            if (!st[u].ch[c]) return -1;
            u = st[u].ch[c];
        }
        return u;
    }

    ll occurrences(const string& p) {
        int u = walk(p);
        return u == -1 ? 0 : st[u].occ;
    }

    ll distinct() { return st[0].dp; }

    // k 从 1 开始，返回第 k 小不同子串；越界返回空串
    string kth(ll k) {
        if (k < 1 || k > st[0].dp) return "";
        string ans;
        int u = 0;
        while (k) {
            for (int c = 0; c < 26; c++) {
                int v = st[u].ch[c];
                if (!v) continue;
                ll cnt = 1 + st[v].dp;
                if (k > cnt) {
                    k -= cnt;
                } else {
                    ans.push_back('a' + c);
                    if (k == 1) return ans;
                    k--;
                    u = v;
                    break;
                }
            }
        }
        return ans;
    }

    int repeat_at_least(ll k) {
        int ans = 0;
        for (int v = 1; v < (int)st.size(); v++)
            if (st[v].occ >= k) ans = max(ans, st[v].len);
        return ans;
    }

    LCS lcs(const string& t) {
        int u = 0, len = 0, best = 0, end = -1, state = 0;
        for (int i = 0; i < (int)t.size(); i++) {
            int c = t[i] - 'a';
            while (u && !st[u].ch[c]) {
                u = st[u].link;
                len = min(len, st[u].len);
            }
            if (st[u].ch[c]) {
                u = st[u].ch[c];
                len++;
            } else {
                u = 0;
                len = 0;
            }
            if (len > best) best = len, end = i, state = u;
        }
        if (!best) return {0, -1, -1, -1, -1};
        return {
            best,
            st[state].first - best + 1,
            st[state].first,
            end - best + 1, end
        };
    }

    vector<vector<int>> link_tree() {
        vector<vector<int>> g(st.size());
        for (int v = 1; v < (int)st.size(); v++)
            g[st[v].link].push_back(v);
        return g;
    }
};
