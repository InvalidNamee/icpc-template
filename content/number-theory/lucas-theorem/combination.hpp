struct Combination {
  using ll = long long;
  int n;
  ll mod;
  std::vector<ll> fact, ifact;

  Combination(int n, ll mod)
      : n(n), mod(mod), fact(n + 1), ifact(n + 1) {
    fact[0] = 1;
    for (int i = 1; i <= n; ++i) fact[i] = fact[i - 1] * i % mod;
    ifact[n] = qpow(fact[n], mod - 2);
    for (int i = n; i >= 1; --i) ifact[i - 1] = ifact[i] * i % mod;
  }

  ll qpow(ll a, ll b) const {
    ll res = 1;
    while (b) {
      if (b & 1) res = (__int128)res * a % mod;
      a = (__int128)a * a % mod;
      b >>= 1;
    }
    return res;
  }

  ll C(ll a, ll b) const {
    if (b < 0 || b > a || a > n) return 0;
    return fact[a] * ifact[a - b] % mod * ifact[b] % mod;
  }
};
