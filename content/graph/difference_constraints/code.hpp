#include <queue>
#include <utility>
#include <vector>

using ll = long long;

struct Diff {
    int n;
    vector<vector<pair<int, ll>>> g;
    vector<ll> d;

    Diff(int n) : n(n), g(n), d(n) {}

    // xv - xu <= w
    void add(int u, int v, ll w) {
        g[u].push_back({v, w});
    }

    bool run() {
        fill(d.begin(), d.end(), 0);
        vector<int> in(n, 1), cnt(n);
        queue<int> q;
        for (int i = 0; i < n; i++) q.push(i);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            in[u] = 0;
            for (auto [v, w] : g[u]) {
                if (d[v] <= d[u] + w) continue;
                d[v] = d[u] + w;
                cnt[v] = cnt[u] + 1;
                if (cnt[v] >= n) return false;
                if (!in[v]) q.push(v), in[v] = 1;
            }
        }
        return true;
    }
};
