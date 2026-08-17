#include <algorithm>
#include <string>
#include <utility>
#include <vector>

using ll = long long;

struct StringHash {
    static const int M1 = 1000000007;
    static const int M2 = 1000000009;
    static const int B = 13331;

    int n;
    string s;
    vector<ll> h1, h2, p1, p2;

    StringHash(const string& s) : n((int)s.size() - 1), s(s),
        h1(n + 1), h2(n + 1), p1(n + 1, 1), p2(n + 1, 1) {
        for (int i = 1; i <= n; i++) {
            h1[i] = (h1[i - 1] * B + (unsigned char)s[i]) % M1;
            h2[i] = (h2[i - 1] * B + (unsigned char)s[i]) % M2;
            p1[i] = p1[i - 1] * B % M1;
            p2[i] = p2[i - 1] * B % M2;
        }
    }

    pair<int, int> get(int l, int r) {
        ll x = (h1[r] - h1[l - 1] * p1[r - l + 1]) % M1;
        ll y = (h2[r] - h2[l - 1] * p2[r - l + 1]) % M2;
        if (x < 0) x += M1;
        if (y < 0) y += M2;
        return {(int)x, (int)y};
    }

    int lcp(int i, int j, int limit) {
        int lo = 0, hi = min({limit, n - i + 1, n - j + 1});
        while (lo < hi) {
            int m = (lo + hi + 1) / 2;
            if (get(i, i + m - 1) == get(j, j + m - 1)) lo = m;
            else hi = m - 1;
        }
        return lo;
    }

    int cmp(int l1, int r1, int l2, int r2) {
        int a = r1 - l1 + 1, b = r2 - l2 + 1;
        int k = lcp(l1, l2, min(a, b));
        if (k == min(a, b)) return (a > b) - (a < b);
        return (s[l1 + k] > s[l2 + k]) - (s[l1 + k] < s[l2 + k]);
    }
};
