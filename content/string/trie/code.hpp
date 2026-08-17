#include <array>
#include <string>
#include <vector>

using ll = long long;

struct Trie {
    vector<array<int, 26>> ch{{}};
    vector<int> pass{0}, term{0};

    int node() {
        ch.push_back({});
        pass.push_back(0);
        term.push_back(0);
        return (int)ch.size() - 1;
    }

    void insert(const string& s) {
        int u = 0;
        pass[u]++;
        for (int i = 1; i < (int)s.size(); i++) {
            int c = s[i] - 'a';
            if (!ch[u][c]) ch[u][c] = node();
            u = ch[u][c];
            pass[u]++;
        }
        term[u]++;
    }

    int find(const string& s) {
        int u = 0;
        for (int i = 1; i < (int)s.size(); i++) {
            int c = s[i] - 'a';
            if (!ch[u][c]) return -1;
            u = ch[u][c];
        }
        return u;
    }

    int count(const string& s) {
        int u = find(s);
        return u == -1 ? 0 : term[u];
    }

    int prefix_count(const string& s) {
        int u = find(s);
        return u == -1 ? 0 : pass[u];
    }
};

struct XorTrie {
    static const int B = 60;
    vector<array<int, 2>> ch{{}};
    vector<int> cnt{0};

    int node() {
        ch.push_back({});
        cnt.push_back(0);
        return (int)ch.size() - 1;
    }

    void add(ll x, int delta) {
        int u = 0;
        cnt[u] += delta;
        for (int b = B; b >= 0; b--) {
            int c = x >> b & 1;
            if (!ch[u][c]) ch[u][c] = node();
            u = ch[u][c];
            cnt[u] += delta;
        }
    }

    ll max_xor(ll x) {
        int u = 0;
        ll ans = 0;
        for (int b = B; b >= 0; b--) {
            int c = x >> b & 1, v = ch[u][c ^ 1];
            if (v && cnt[v]) ans |= 1LL << b, u = v;
            else u = ch[u][c];
        }
        return ans;
    }

    ll min_xor(ll x) {
        int u = 0;
        ll ans = 0;
        for (int b = B; b >= 0; b--) {
            int c = x >> b & 1, v = ch[u][c];
            if (v && cnt[v]) u = v;
            else ans |= 1LL << b, u = ch[u][c ^ 1];
        }
        return ans;
    }
};
