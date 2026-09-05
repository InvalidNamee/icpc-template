std::vector<std::vector<long long>> stirling2(int n, int k,
                                               long long mod) {
  std::vector s(n + 1, std::vector<long long>(k + 1));
  s[0][0] = 1;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= std::min(i, k); ++j) {
      s[i][j] = (s[i - 1][j - 1]
               + (__int128)j * s[i - 1][j]) % mod;
    }
  }
  return s;
}

