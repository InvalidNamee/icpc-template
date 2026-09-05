struct PrimeFactorCountSieve {
  vector<int> primes, omega, Omega;
  vector<bool> composite;

  explicit PrimeFactorCountSieve(int n)
      : omega(n + 1), Omega(n + 1), composite(n + 1) {
    for (int i = 2; i <= n; ++i) {
      if (!composite[i]) {
        primes.push_back(i);
        omega[i] = Omega[i] = 1;
      }
      for (int p : primes) {
        if (1LL * i * p > n) break;
        composite[i * p] = true;
        Omega[i * p] = Omega[i] + 1;
        if (i % p == 0) {
          omega[i * p] = omega[i];
          break;
        }
        omega[i * p] = omega[i] + 1;
      }
    }
  }
};
