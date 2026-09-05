using ll = long long;

// 0-based：n 个人依次数到 k 出队。
// 返回最后留下的位置。
ll josephus_last(ll n, ll k) {
  ll pos = 0;
  for (ll size = 2; size <= n; ++size)
    pos = (pos + k) % size;
  return pos;
}

// 0-based：返回第 m 个出队者。
// 递归深度为 m，不适合极大 m。
ll josephus_kth(ll n, ll k, ll m) {
  if (m == 1) return (k - 1) % n;
  return (josephus_kth(n - 1, k, m - 1) + k) % n;
}

// 0-based：n、m 很大时求第 m 个出队者。
// 要求 1 <= m <= n, k > 1。
ll josephus_kth_fast(ll n, ll k, ll m) {
  ll size = n - m + 1;
  ll ans = (k - 1) % size;
  while (size < n) {
    ll step = (size - ans) / (k - 1)
            + ((size - ans) % (k - 1) != 0);
    if (size + step > n) step = n - size;
    ans += step * k;
    size += step;
    ans %= size;
  }
  return ans;
}
