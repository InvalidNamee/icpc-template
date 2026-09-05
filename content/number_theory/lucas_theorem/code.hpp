struct Lucas {
  using ll = long long;
  ll p;
  vector<ll> fact, ifact;

  explicit Lucas(int prime) : p(prime), fact(p), ifact(p) {
    fact[0] = 1;
    for (int i = 1; i < p; ++i)
      fact[i] = fact[i - 1] * i % p;
    ifact[p - 1] = qpow(fact[p - 1], p - 2);
    for (int i = p - 1; i >= 1; --i)
      ifact[i - 1] = ifact[i] * i % p;
  }

  ll qpow(ll a, ll b) const {
    ll res = 1;
    while (b) {
      if (b & 1) res = (__int128)res * a % p;
      a = (__int128)a * a % p;
      b >>= 1;
    }
    return res;
  }

  ll C(ll n, ll m) const {
    if (m < 0 || m > n) return 0;
    return fact[n] * ifact[n - m] % p * ifact[m] % p;
  }

  ll calc(ll n, ll m) const {
    if (!m) return 1;
    return C(n % p, m % p) * calc(n / p, m / p) % p;
  }
};
