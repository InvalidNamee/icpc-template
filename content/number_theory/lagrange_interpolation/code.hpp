using ll = long long;

ll mod_pow(ll a, ll e, ll mod) {
  ll r = 1;
  for (; e; e >>= 1, a = (__int128)a * a % mod)
    if (e & 1) r = (__int128)r * a % mod;
  return r;
}

// mod 必须为素数，且所有 xs 在模 mod 下两两不同。
ll lagrange_eval(const vector<ll>& xs,
                 const vector<ll>& ys,
                 ll x, ll mod) {
  int n = (int)xs.size();
  x = (x % mod + mod) % mod;
  for (int i = 0; i < n; ++i)
    if ((xs[i] % mod + mod) % mod == x)
      return (ys[i] % mod + mod) % mod;

  ll ans = 0;
  for (int i = 0; i < n; ++i) {
    ll num = 1, den = 1;
    for (int j = 0; j < n; ++j) if (i != j) {
      num = (__int128)num * (x - xs[j] + mod) % mod;
      den = (__int128)den * (xs[i] - xs[j] + mod) % mod;
    }
    ll term = (__int128)(ys[i] % mod + mod)
            % mod * num % mod;
    term = (__int128)term
         * mod_pow(den, mod - 2, mod) % mod;
    ans = (ans + term) % mod;
  }
  return ans;
}
