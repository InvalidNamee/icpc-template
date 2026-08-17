using ll = long long;

struct Comb {
    int n;
    ll mod;
    vector<ll> fac, invfac;

    Comb(int _n, ll _mod) {
        n = _n;
        mod = _mod;
        fac.assign(n + 1, 1);
        invfac.assign(n + 1, 1);

        for (int i = 1; i <= n; i++) {
            fac[i] = fac[i - 1] * i % mod;
        }

        invfac[n] = qpow(fac[n], mod - 2);

        for (int i = n - 1; i >= 0; i--) {
            invfac[i] = invfac[i + 1] * (i + 1) % mod;
        }
    }

    ll qpow(ll a, ll b) {
        ll res = 1;
        while (b) {
            if (b & 1) res = res * a % mod;
            a = a * a % mod;
            b >>= 1;
        }
        return res;
    }
    ll A(int n, int m) {
        if (m < 0 || m > n) return 0;
        return fac[n] * invfac[n - m] % mod;
    }
    ll C(int n, int m) {
        if (m < 0 || m > n) return 0;
        return fac[n] * invfac[m] % mod * invfac[n - m] % mod;
    }
};
