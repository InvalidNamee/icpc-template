#pragma once

#include "../gcd/code.hpp"

using i128 = __int128_t;

ll norm(ll x, ll mod) {
  x %= mod;
  return x < 0 ? x + mod : x;
}

// 合并 x = a1 (mod m1) 与 x = a2 (mod m2)。
// 成功时写回 (a1, m1)，使 0 <= a1 < m1。
bool merge_crt(ll& a1, ll& m1, ll a2, ll m2) {
  ll x, y;
  ll g = exgcd(m1, m2, x, y);
  ll diff = a2 - a1;
  if (diff % g != 0) return false;

  ll mod = m2 / g;
  ll t = (ll)((i128)(diff / g) * x % mod);
  i128 lcm = (i128)m1 / g * m2;
  i128 ans = (i128)a1 + (i128)m1 * t;
  ans %= lcm;
  if (ans < 0) ans += lcm;

  // 调用者应保证 lcm 不超过 long long。
  a1 = (ll)ans;
  m1 = (ll)lcm;
  return true;
}
