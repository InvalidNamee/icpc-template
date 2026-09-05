struct DivisorSumSieve {
  using ll = long long;
  std::vector<int> primes;
  std::vector<ll> sigma, minp_power;
  std::vector<bool> composite;

  explicit DivisorSumSieve(int n)
      : sigma(n + 1), minp_power(n + 1), composite(n + 1) {
    sigma[1] = minp_power[1] = 1;
    for (int i = 2; i <= n; ++i) {
      if (!composite[i]) {
        primes.push_back(i);
        minp_power[i] = i;
        sigma[i] = i + 1;
      }
      for (int p : primes) {
        if (1LL * i * p > n) break;
        composite[i * p] = true;
        if (i % p == 0) {
          sigma[i * p] = sigma[i]
                       + sigma[i / minp_power[i]] * minp_power[i] * p;
          minp_power[i * p] = minp_power[i] * p;
          break;
        }
        minp_power[i * p] = p;
        sigma[i * p] = sigma[i] * (p + 1);
      }
    }
  }
};
