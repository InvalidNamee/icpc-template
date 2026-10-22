struct PAM {
    struct Node {
        int len, fail, cnt;
        int ch[26];
        Node(int len = 0) : len(len), fail(0), cnt(0) {
            memset(ch, 0, sizeof ch);
        }
    };

    vector<Node> tr;
    string s;
    int last;

    PAM() {
        tr.emplace_back(0);
        tr.emplace_back(-1);
        tr[0].fail = tr[1].fail = 1;
        last = 0;
    }

    int getfail(int p, int pos) {
        while (pos - tr[p].len - 1 < 0 ||
               s[pos - tr[p].len - 1] != s[pos])
            p = tr[p].fail;
        return p;
    }

    void add(char c) {
        s += c;
        int pos = s.size() - 1;
        int x = c - 'a';
        int p = getfail(last, pos);

        if (!tr[p].ch[x]) {
            int now = tr.size();
            tr.emplace_back(tr[p].len + 2);

            if (tr[now].len == 1) {
                tr[now].fail = 0;
            } else {
                int q = getfail(tr[p].fail, pos);
                tr[now].fail = tr[q].ch[x];
            }
            tr[p].ch[x] = now;
        }

        last = tr[p].ch[x];
        tr[last].cnt++;
    }
    int size() {
        return (int)tr.size() - 2;
    }
};
