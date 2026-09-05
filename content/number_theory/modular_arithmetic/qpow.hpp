using ll = long long;

ll qpow(ll a, ll b, ll mod) {
  ll res = 1 % mod;
  a %= mod;
  if (a < 0) a += mod;
  while (b) {
    if (b & 1) res = (__int128)res * a % mod;
    a = (__int128)a * a % mod;
    b >>= 1;
  }
  return res;
}
