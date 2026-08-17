#include <algorithm>
#include <deque>
#include <string>
#include <utility>
#include <vector>

using ll = long long;

struct SA {
    int n;
    string s;
    vector<int> sa, rk, height, lg;
    vector<vector<int>> st;

    SA(const string& s) : n((int)s.size() - 1), s(s) {
        build_sa();
        build_lcp();
    }

    void build_sa() {
        int m = 256;
        vector<int> x(n + 1), y(n + 1), c(max(n, m) + 2);
        sa.assign(n + 1, 0);
        for (int i = 1; i <= n; i++) x[i] = (unsigned char)s[i] + 1;
        for (int i = 1; i <= n; i++) c[x[i]]++;
        for (int i = 1; i <= m; i++) c[i] += c[i - 1];
        for (int i = n; i >= 1; i--) sa[c[x[i]]--] = i;

        for (int k = 1; k < n; k *= 2) {
            int p = 0;
            for (int i = n - k + 1; i <= n; i++) y[++p] = i;
            for (int i = 1; i <= n; i++)
                if (sa[i] > k) y[++p] = sa[i] - k;

            fill(c.begin(), c.begin() + m + 1, 0);
            for (int i = 1; i <= n; i++) c[x[y[i]]]++;
            for (int i = 1; i <= m; i++) c[i] += c[i - 1];
            for (int i = n; i >= 1; i--) sa[c[x[y[i]]]--] = y[i];

            y = x;
            p = 1;
            x[sa[1]] = 1;
            for (int i = 2; i <= n; i++) {
                int a = sa[i - 1], b = sa[i];
                int a2 = a + k <= n ? y[a + k] : 0;
                int b2 = b + k <= n ? y[b + k] : 0;
                x[b] = y[a] == y[b] && a2 == b2 ? p : ++p;
            }
            m = p;
            if (p == n) break;
        }

        rk.assign(n + 1, 0);
        for (int i = 1; i <= n; i++) rk[sa[i]] = i;
    }

    void build_lcp() {
        height.assign(n + 1, 0);
        for (int i = 1, k = 0; i <= n; i++) {
            int r = rk[i];
            if (r == 1) continue;
            int j = sa[r - 1];
            while (i + k <= n && j + k <= n && s[i + k] == s[j + k]) k++;
            height[r] = k;
            if (k) k--;
        }

        lg.assign(n + 1, 0);
        for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;
        st.assign(lg[n] + 1, vector<int>(n + 1));
        st[0] = height;
        for (int k = 1; k < (int)st.size(); k++)
            for (int i = 1; i + (1 << k) - 1 <= n; i++)
                st[k][i] = min(st[k - 1][i],
                               st[k - 1][i + (1 << (k - 1))]);
    }

    int lcp(int i, int j) {
        if (i == j) return n - i + 1;
        int a = rk[i], b = rk[j];
        if (a > b) swap(a, b);
        int len = b - a, k = lg[len];
        return min(st[k][a + 1], st[k][b - (1 << k) + 1]);
    }

    int cmp(int l1, int r1, int l2, int r2) {
        int a = r1 - l1 + 1, b = r2 - l2 + 1;
        int k = min({lcp(l1, l2), a, b});
        if (k == min(a, b)) return (a > b) - (a < b);
        return (s[l1 + k] > s[l2 + k]) - (s[l1 + k] < s[l2 + k]);
    }

    int cmp_pat(int pos, const string& p) {
        int i = 1, m = (int)p.size() - 1;
        while (pos <= n && i <= m && s[pos] == p[i]) pos++, i++;
        if (i > m) return 0;
        if (pos > n) return -1;
        return (s[pos] > p[i]) - (s[pos] < p[i]);
    }

    // 返回匹配后缀在 SA 中的闭区间 [L, R]，无匹配时 L > R
    pair<int, int> match(const string& p) {
        int l = 1, r = n + 1;
        while (l < r) {
            int m = (l + r) / 2;
            if (cmp_pat(sa[m], p) >= 0) r = m;
            else l = m + 1;
        }
        int L = l;
        l = 1, r = n + 1;
        while (l < r) {
            int m = (l + r) / 2;
            if (cmp_pat(sa[m], p) > 0) r = m;
            else l = m + 1;
        }
        return {L, l - 1};
    }

    ll distinct() {
        ll ans = 1LL * n * (n + 1) / 2;
        for (int i = 2; i <= n; i++) ans -= height[i];
        return ans;
    }

    // k 从 1 开始，返回第 k 小不同子串在原串中的闭区间
    pair<int, int> kth(ll k) {
        for (int i = 1; i <= n; i++) {
            ll cnt = n - sa[i] + 1 - height[i];
            if (k > cnt) k -= cnt;
            else {
                int len = height[i] + (int)k;
                return {sa[i], sa[i] + len - 1};
            }
        }
        return {-1, -1};
    }

    int repeat_at_least(int k) {
        if (k <= 1) return n;
        if (k > n) return 0;
        deque<int> q;
        int ans = 0;
        for (int r = 2; r <= n; r++) {
            while (!q.empty() && height[q.back()] >= height[r]) q.pop_back();
            q.push_back(r);
            while (q.front() < r - k + 2) q.pop_front();
            if (r >= k) ans = max(ans, height[q.front()]);
        }
        return ans;
    }
};
