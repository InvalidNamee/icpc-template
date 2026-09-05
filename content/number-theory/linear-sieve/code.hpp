struct LinearSieve {
  std::vector<int> primes, minp, phi, mu;

  explicit LinearSieve(int n)
      : minp(n + 1), phi(n + 1), mu(n + 1) {
    phi[1] = 1;
    mu[1] = 1;
    for (int i = 2; i <= n; ++i) {
      if (minp[i] == 0) {
        minp[i] = i;
        phi[i] = i - 1;
        mu[i] = -1;
        primes.push_back(i);
      }
      for (int p : primes) {
        if (1LL * i * p > n) break;
        minp[i * p] = p;
        if (i % p == 0) {
          phi[i * p] = phi[i] * p;
          mu[i * p] = 0;
          break;
        }
        phi[i * p] = phi[i] * (p - 1);
        mu[i * p] = -mu[i];
      }
    }
  }
};

