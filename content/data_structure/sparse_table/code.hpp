template<class T, class Op>
struct SparseTable {
    vector<int> lg;
    vector<vector<T>> st;
    Op op;

    SparseTable(const vector<T>& a, Op op) : op(op) {
        int n = a.size(), m = 1;
        while ((1 << m) <= n) m++;
        lg.resize(n + 1);
        for (int i = 2; i <= n; i++) lg[i] = lg[i / 2] + 1;
        st.assign(m, vector<T>(n));
        st[0] = a;
        for (int j = 1; j < m; j++)
            for (int i = 0; i + (1 << j) <= n; i++)
                st[j][i] = op(st[j - 1][i], st[j - 1][i + (1 << (j - 1))]);
    }

    T query(int l, int r) const {
        int k = lg[r - l + 1];
        return op(st[k][l], st[k][r - (1 << k) + 1]);
    }
};
