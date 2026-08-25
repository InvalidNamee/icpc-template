using u32 = uint32_t;

template<int B = 20>
struct PersistentTrie {
    static_assert(1 <= B && B <= 32);

    struct Node {
        int ch[2]{}, cnt = 0;
    };

    vector<Node> tr{Node()};
    vector<int> root{0};

    PersistentTrie(int n = 0) {
        tr.reserve((n + 1) * (B + 1));
        root.reserve(n + 1);
    }

    int clone(int p) {
        tr.push_back(tr[p]);
        return tr.size() - 1;
    }

    int insert(int pre, u32 x) {
        int rt = clone(pre), cur = rt;
        tr[cur].cnt++;
        for (int i = B - 1; i >= 0; i--) {
            int t = x >> i & 1;
            int nxt = clone(tr[pre].ch[t]);
            tr[cur].ch[t] = nxt;
            cur = nxt, pre = tr[pre].ch[t];
            tr[cur].cnt++;
        }
        return rt;
    }

    void push(u32 x) {
        root.push_back(insert(root.back(), x));
    }

    u32 query(u32 x, int l, int r) const {
        int a = root[l - 1], b = root[r];
        u32 res = 0;
        for (int i = B - 1; i >= 0; i--) {
            int t = x >> i & 1, w = t ^ 1;
            int ca = tr[a].ch[w], cb = tr[b].ch[w];
            if (tr[cb].cnt > tr[ca].cnt) {
                res |= 1u << i;
                a = ca, b = cb;
            } else {
                a = tr[a].ch[t], b = tr[b].ch[t];
            }
        }
        return res;
    }

    int size() const { return (int)root.size() - 1; }
};
