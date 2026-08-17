// 返回 f(x)^{-1} mod x^n，要求 f[0] != 0
vector<int> poly_inv(vector<int> f, int n) {
    int f0 = (f[0] % NTT_MOD + NTT_MOD) % NTT_MOD;
    vector<int> g(1, ntt_qpow(f0, NTT_MOD - 2));

    for (int m = 1; m < n; m <<= 1) {
        int len = min(m << 1, n);
        vector<int> ff(len);
        for (int i = 0; i < len && i < (int)f.size(); i++) {
            ff[i] = f[i];
        }

        vector<int> t = ntt_mul(ff, g);
        t.resize(len);

        // t = 2 - f * g
        for (int& x : t) x = (NTT_MOD - x) % NTT_MOD;
        t[0] += 2;
        if (t[0] >= NTT_MOD) t[0] -= NTT_MOD;

        g = ntt_mul(g, t);
        g.resize(len);
    }

    g.resize(n);
    return g;
}

// 返回 ln(f(x)) mod x^n，要求 f[0] = 1
vector<int> poly_ln(vector<int> f, int n) {
    if (n == 1) return vector<int>(1);

    // 求导
    int lim = min(n, (int)f.size());
    vector<int> d(max(0, lim - 1));
    for (int i = 1; i < lim; i++) {
        d[i - 1] = 1LL * f[i] * i % NTT_MOD;
    }

    // f' / f
    vector<int> g = ntt_mul(d, poly_inv(f, n));
    g.resize(n - 1);

    // 预处理积分需要的逆元
    vector<int> iv(n + 1);
    iv[1] = 1;
    for (int i = 2; i <= n; i++) {
        iv[i] = 1LL * (NTT_MOD - NTT_MOD / i)
              * iv[NTT_MOD % i] % NTT_MOD;
    }

    // 积分
    vector<int> res(n);
    for (int i = 1; i < n; i++) {
        res[i] = 1LL * g[i - 1] * iv[i] % NTT_MOD;
    }
    return res;
}

// 返回 exp(f(x)) mod x^n，n = f.size()，要求 f[0] = 0
vector<int> poly_exp(vector<int> f) {
    int n = f.size();
    vector<int> g(1, 1);

    for (int m = 1; m < n; m <<= 1) {
        int len = min(m << 1, n);
        vector<int> lng = poly_ln(g, len);
        vector<int> t(len);

        // t = 1 + f - ln(g)
        for (int i = 0; i < len; i++) {
            t[i] = f[i] - lng[i];
            if (t[i] < 0) t[i] += NTT_MOD;
        }
        t[0]++;
        if (t[0] >= NTT_MOD) t[0] -= NTT_MOD;

        g = ntt_mul(g, t);
        g.resize(len);
    }
    return g;
}
