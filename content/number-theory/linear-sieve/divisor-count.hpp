struct DivisorCountSieve {
  std::vector<int> primes, d, minp_exp;
  std::vector<bool> composite;

  explicit DivisorCountSieve(int n)
      : d(n + 1), minp_exp(n + 1), composite(n + 1) {
    d[1] = 1;
    for (int i = 2; i <= n; ++i) {
      if (!composite[i]) {
        primes.push_back(i);
        d[i] = 2;
        minp_exp[i] = 1;
      }
      for (int p : primes) {
        if (1LL * i * p > n) break;
        composite[i * p] = true;
        if (i % p == 0) {
          minp_exp[i * p] = minp_exp[i] + 1;
          d[i * p] = d[i] / (minp_exp[i] + 1)
                         * (minp_exp[i] + 2);
          break;
        }
        minp_exp[i * p] = 1;
        d[i * p] = d[i] * 2;
      }
    }
  }
};
