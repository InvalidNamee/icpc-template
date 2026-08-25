template<class T, class Cmp = less<T>>
struct LeftistHeap {
    struct Node {
        T val{};
        int ls = 0, rs = 0, dis = 1;
    };

    vector<Node> tr{Node()};
    Cmp cmp;

    int new_node(const T& val) {
        tr.push_back({val, 0, 0, 1});
        return tr.size() - 1;
    }

    int merge(int x, int y) {
        if (!x || !y) return x | y;
        if (cmp(tr[y].val, tr[x].val)) swap(x, y);
        tr[x].rs = merge(tr[x].rs, y);
        if (tr[tr[x].ls].dis < tr[tr[x].rs].dis)
            swap(tr[x].ls, tr[x].rs);
        tr[x].dis = tr[tr[x].rs].dis + 1;
        return x;
    }

    void push(int& root, const T& val) {
        root = merge(root, new_node(val));
    }

    const T& top(int root) const { return tr[root].val; }

    void pop(int& root) {
        root = merge(tr[root].ls, tr[root].rs);
    }
};
