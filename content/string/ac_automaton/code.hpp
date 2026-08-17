struct AC {
    struct Node {
        int ch[26]{};
        int fail = 0, out = 0;
        vector<int> ids;
    };

    vector<Node> tr{1};

    void add(const string& s, int id) {
        int u = 0;
        for (char c : s) {
            int x = c - 'a';
            if (!tr[u].ch[x]) {
                tr[u].ch[x] = tr.size();
                tr.push_back({});
            }
            u = tr[u].ch[x];
        }
        tr[u].ids.push_back(id);
    }

    void build() {
        queue<int> q;
        for (int c = 0; c < 26; c++) {
            int v = tr[0].ch[c];
            if (v) q.push(v);
        }

        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int c = 0; c < 26; c++) {
                int v = tr[u].ch[c];
                if (!v) {
                    tr[u].ch[c] = tr[tr[u].fail].ch[c];
                    continue;
                }

                tr[v].fail = tr[tr[u].fail].ch[c];
                int f = tr[v].fail;
                tr[v].out = tr[f].ids.empty() ? tr[f].out : f;
                q.push(v);
            }
        }
    }

    // ans[i] 是在文本位置 i 结尾的所有模式串编号。
    vector<vector<int>> query(const string& s) const {
        vector<vector<int>> ans(s.size());
        int u = 0;
        for (int i = 0; i < (int)s.size(); i++) {
            u = tr[u].ch[s[i] - 'a'];
            for (int v = u; v; v = tr[v].out)
                for (int id : tr[v].ids)
                    ans[i].push_back(id);
        }
        return ans;
    }
};
