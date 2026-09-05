#pragma once

using ll = long long;
using i128 = __int128_t;

struct DuJiaoSieve {
  int limit;
  std::vector<int> primes, mu, phi;
  std::vector<bool> is_composite;
  std::vector<ll> prefix_mu, prefix_phi;
  std::unordered_map<ll, ll> memo_mu, memo_phi;

  explicit DuJiaoSieve(int limit)
      : limit(std::max(limit, 1)),
        mu(this->limit + 1),
        phi(this->limit + 1),
        is_composite(this->limit + 1),
        prefix_mu(this->limit + 1),
        prefix_phi(this->limit + 1) {
    mu[1] = phi[1] = 1;
    for (int i = 2; i <= this->limit; ++i) {
      if (!is_composite[i]) {
        primes.push_back(i);
        mu[i] = -1;
        phi[i] = i - 1;
      }
      for (int p : primes) {
        if ((ll)i * p > this->limit) break;
        int x = i * p;
        is_composite[x] = true;
        if (i % p == 0) {
          mu[x] = 0;
          phi[x] = phi[i] * p;
          break;
        }
        mu[x] = -mu[i];
        phi[x] = phi[i] * (p - 1);
      }
    }
    for (int i = 1; i <= this->limit; ++i) {
      prefix_mu[i] = prefix_mu[i - 1] + mu[i];
      prefix_phi[i] = prefix_phi[i - 1] + phi[i];
    }
    memo_mu.reserve(this->limit);
    memo_phi.reserve(this->limit);
  }

  ll sum_mu(ll n) {
    if (n <= limit) return prefix_mu[n];
    auto it = memo_mu.find(n);
    if (it != memo_mu.end()) return it->second;

    i128 ans = 1;
    for (ll l = 2, r; l <= n; l = r + 1) {
      ll q = n / l;
      r = n / q;
      ans -= (i128)(r - l + 1) * sum_mu(q);
    }
    return memo_mu[n] = (ll)ans;
  }

  ll sum_phi(ll n) {
    if (n <= limit) return prefix_phi[n];
    auto it = memo_phi.find(n);
    if (it != memo_phi.end()) return it->second;

    i128 ans = (i128)n * (n + 1) / 2;
    for (ll l = 2, r; l <= n; l = r + 1) {
      ll q = n / l;
      r = n / q;
      ans -= (i128)(r - l + 1) * sum_phi(q);
    }
    return memo_phi[n] = (ll)ans;
  }
};
