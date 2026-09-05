struct MinimumPrimeSieve {
  std::vector<int> primes, minp, minp_exp;

  explicit MinimumPrimeSieve(int n)
      : minp(n + 1), minp_exp(n + 1) {
    for (int i = 2; i <= n; ++i) {
      if (!minp[i]) {
        minp[i] = i;
        minp_exp[i] = 1;
        primes.push_back(i);
      }
      for (int p : primes) {
        if (1LL * i * p > n || p > minp[i]) break;
        minp[i * p] = p;
        minp_exp[i * p] = (p == minp[i] ? minp_exp[i] + 1 : 1);
      }
    }
  }
};
