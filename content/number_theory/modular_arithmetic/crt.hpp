#pragma once

#include "../gcd/code.hpp"

using i128 = __int128_t;

// m[0..k-1] 两两互质，返回 [0, product(m)) 中的唯一解。
ll crt(const vector<ll>& a, const vector<ll>& m) {
  int k = (int)a.size();
  ll mod = 1;
  for (ll x : m) mod = (i128)mod * x;

  ll ans = 0;
  for (int i = 0; i < k; ++i) {
    ll part = mod / m[i], inv, y;
    exgcd(part, m[i], inv, y);
    i128 term = (i128)a[i] * part % mod * inv;
    ans = (ans + term) % mod;
  }
  return (ans % mod + mod) % mod;
}
