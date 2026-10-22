struct RadixSort {
    int n, len = 0;
    vector<int> a, b, c, rk, nrk;
    int cnt[11];

    RadixSort(const string& s) {
        n = s.size();
        a.resize(n + 2);
        b.resize(n + 2);
        c.resize(n + 2);
        rk.resize(n + 2);
        nrk.resize(n + 2);
        for (int i = 1; i <= n; i++)
            a[i] = s[i - 1] - '0';
        iota(b.begin(), b.end(), 0);
    }

    // 长度 len -> len + 1；b 为顺序，rk 为排名
    bool next() {
        if (len == n) return false;
        int m = n - ++len + 1;
        fill(cnt, cnt + 11, 0);
        for (int i = 1; i <= m; i++)
            cnt[a[i] + 1]++;
        for (int i = 1; i <= 10; i++)
            cnt[i] += cnt[i - 1];

        for (int i = 1; i <= m + 1; i++) {
            int x = b[i];
            if (x == 1) continue;
            c[++cnt[a[x - 1]]] = x - 1;
        }
        b.swap(c);

        int t = 0;
        for (int i = 1; i <= m; i++) {
            int x = b[i], y = b[i - 1];
            if (i == 1 || a[x] != a[y] ||
                rk[x + 1] != rk[y + 1]) t++;
            nrk[x] = t;
        }
        rk.swap(nrk);
        return true;
    }
};
