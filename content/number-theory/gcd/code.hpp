#pragma once

using ll = long long;

ll gcd_euclid(ll a, ll b) {
  a = std::abs(a);
  b = std::abs(b);
  while (b != 0) {
    ll r = a % b;
    a = b;
    b = r;
  }
  return a;
}

// 返回 g = gcd(a, b)，并求出 ax + by = g 的一组系数。
ll exgcd(ll a, ll b, ll& x, ll& y) {
  if (b == 0) {
    x = (a >= 0 ? 1 : -1);
    y = 0;
    return std::abs(a);
  }
  ll x1, y1;
  ll g = exgcd(b, a % b, x1, y1);
  x = y1;
  y = x1 - (a / b) * y1;
  return g;
}
