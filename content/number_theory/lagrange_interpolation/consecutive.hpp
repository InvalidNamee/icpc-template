using ll = long long;

ll lagrange_qpow(
  ll a, ll b, ll mod
) {
  a = (a % mod + mod) % mod;
  ll res = 1;
  while (b) {
    if (b & 1) res = (__int128)res * a % mod;
    a = (__int128)a * a % mod;
    b >>= 1;
  }
  return res;
}

// 已知 y[i] = f(i), 1 <= i <= n；mod 为素数。
// fact 与 ifact 至少预处理到 n。
ll lagrange_consecutive(
  const vector<ll>& y,
  ll x, ll mod,
  const vector<ll>& ifact
) {
  int n = (int)y.size() - 1;
  x = (x % mod + mod) % mod;
  if (1 <= x && x <= n) return y[x];

  vector<ll> pre(n + 2), suf(n + 2);
  pre[0] = suf[n + 1] = 1;
  for (int i = 1; i <= n; ++i)
    pre[i] = (__int128)pre[i - 1] * (x - i + mod) % mod;
  for (int i = n; i >= 1; --i)
    suf[i] = (__int128)suf[i + 1] * (x - i + mod) % mod;

  ll res = 0;
  for (int i = 1; i <= n; ++i) {
    ll coef = (__int128)pre[i - 1]
                   * suf[i + 1] % mod;
    coef = (__int128)coef * ifact[i - 1] % mod
         * ifact[n - i] % mod;
    if ((n - i) & 1) coef = (mod - coef) % mod;
    res = (res + (__int128)y[i] * coef) % mod;
  }
  return res;
}

// 计算 1^k + ... + x^k；需提供快速幂和逆阶乘。
ll power_sum(
  int k, ll x, ll mod,
  const vector<ll>& ifact
) {
  if (x <= 0) return 0;
  vector<ll> y(k + 3);
  for (int i = 1; i <= k + 2; ++i)
    y[i] = (y[i - 1] + lagrange_qpow(i, k, mod)) % mod;
  return lagrange_consecutive(y, x, mod, ifact);
}
