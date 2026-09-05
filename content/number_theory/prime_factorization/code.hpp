struct PollardRho {
  using u64 = unsigned long long;
  using u128 = __uint128_t;

  mt19937_64 rng{
    (u64)chrono::steady_clock::now()
      .time_since_epoch().count()
  };

  static u64 mul(u64 a, u64 b, u64 mod) {
    return (u128)a * b % mod;
  }

  static u64 qpow(u64 a, u64 b, u64 mod) {
    u64 res = 1;
    while (b) {
      if (b & 1) res = mul(res, a, mod);
      a = mul(a, a, mod);
      b >>= 1;
    }
    return res;
  }

  static bool isprime(u64 n) {
    static constexpr u64 small[] =
      {2, 3, 5, 7, 11, 13, 17, 19, 23, 29, 31, 37};
    static constexpr u64 bases[] =
      {2, 325, 9375, 28178, 450775, 9780504, 1795265022};

    if (n < 2) return false;
    for (u64 p : small) if (n % p == 0) return n == p;

    u64 d = n - 1;
    int s = 0;
    while (!(d & 1)) d >>= 1, ++s;

    for (u64 a : bases) {
      if (a % n == 0) continue;
      u64 x = qpow(a % n, d, n);
      if (x == 1 || x == n - 1) continue;

      bool witness_passed = false;
      for (int i = 1; i < s; ++i) {
        x = mul(x, x, n);
        if (x == n - 1) {
          witness_passed = true;
          break;
        }
      }
      if (!witness_passed) return false;
    }
    return true;
  }

  u64 rho(u64 n) {
    if (n % 2 == 0) return 2;
    if (n % 3 == 0) return 3;

    while (true) {
      u64 c = rng() % (n - 1) + 1;
      u64 x = rng() % (n - 2) + 2;
      u64 y = x, d = 1;
      auto f = [&](u64 v) {
        return (mul(v, v, n) + c) % n;
      };

      while (d == 1) {
        x = f(x);
        y = f(f(y));
        d = gcd(x > y ? x - y : y - x, n);
      }
      if (d != n) return d;
    }
  }

  void divide(u64 n, vector<u64>& fac) {
    if (n == 1) return;
    if (isprime(n)) {
      fac.push_back(n);
      return;
    }
    u64 d = rho(n);
    divide(d, fac);
    divide(n / d, fac);
  }

  vector<u64> factor(u64 n) {
    vector<u64> fac;
    divide(n, fac);
    sort(fac.begin(), fac.end());
    return fac;
  }

  vector<u64> divisors(u64 n) {
    auto fac = factor(n);
    vector<pair<u64, int>> grouped;
    for (u64 p : fac) {
      if (grouped.empty() || grouped.back().first != p)
        grouped.push_back({p, 1});
      else
        ++grouped.back().second;
    }

    vector<u64> result;
    auto dfs = [&](
      auto&& self, int i, u64 value
    ) -> void {
      if (i == (int)grouped.size()) {
        result.push_back(value);
        return;
      }
      auto [p, exponent] = grouped[i];
      for (int e = 0; e <= exponent; ++e) {
        self(self, i + 1, value);
        value *= p;
      }
    };
    dfs(dfs, 0, 1);
    sort(result.begin(), result.end());
    return result;
  }
};
