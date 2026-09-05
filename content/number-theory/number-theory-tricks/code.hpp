// 0-based：n 个人每次数到 k 的人出队，返回最后留下的位置。
long long josephus_last(long long n, long long k) {
  long long pos = 0;
  for (long long size = 2; size <= n; ++size)
    pos = (pos + k) % size;
  return pos;
}

// 0-based：返回第 m 个出队者。递归深度为 m，不适合极大 m。
long long josephus_kth(long long n, long long k, long long m) {
  if (m == 1) return (k - 1) % n;
  return (josephus_kth(n - 1, k, m - 1) + k) % n;
}

// 0-based：n、m 很大时求第 m 个出队者；要求 1 <= m <= n, k > 1。
long long josephus_kth_fast(long long n, long long k, long long m) {
  long long size = n - m + 1;
  long long ans = (k - 1) % size;
  while (size < n) {
    long long step = (size - ans) / (k - 1)
                   + ((size - ans) % (k - 1) != 0);
    if (size + step > n) step = n - size;
    ans += step * k;
    size += step;
    ans %= size;
  }
  return ans;
}
