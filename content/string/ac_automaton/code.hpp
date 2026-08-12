#include <array>
#include <queue>
#include <string>
#include <vector>

using ll = long long;

struct AC {
    struct Node {
        array<int, 26> ch{};
        int fail = 0;
    };

    vector<Node> tr{1};
    vector<int> order;
    vector<vector<int>> tree;

    int insert(const string& s) {
        int u = 0;
        for (int i = 1; i < (int)s.size(); i++) {
            int c = s[i] - 'a';
            if (!tr[u].ch[c]) {
                tr[u].ch[c] = tr.size();
                tr.push_back({});
            }
            u = tr[u].ch[c];
        }
        return u;
    }

    void build() {
        queue<int> q;
        for (int c = 0; c < 26; c++)
            if (tr[0].ch[c]) q.push(tr[0].ch[c]);
        while (!q.empty()) {
            int u = q.front(); q.pop();
            order.push_back(u);
            for (int c = 0; c < 26; c++) {
                int v = tr[u].ch[c];
                if (v) {
                    tr[v].fail = tr[tr[u].fail].ch[c];
                    q.push(v);
                } else {
                    tr[u].ch[c] = tr[tr[u].fail].ch[c];
                }
            }
        }
        tree.assign(tr.size(), {});
        for (int u = 1; u < (int)tr.size(); u++)
            tree[tr[u].fail].push_back(u);
    }

    vector<ll> match(const string& s) {
        vector<ll> cnt(tr.size());
        int u = 0;
        for (int i = 1; i < (int)s.size(); i++) {
            u = tr[u].ch[s[i] - 'a'];
            cnt[u]++;
        }
        for (int i = (int)order.size() - 1; i >= 0; i--) {
            int v = order[i];
            cnt[tr[v].fail] += cnt[v];
        }
        return cnt;
    }
};
