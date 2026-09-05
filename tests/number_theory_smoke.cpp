#include <bits/stdc++.h>

using namespace std;

#include "../content/number_theory/gcd/code.hpp"
#include "../content/number_theory/modular_arithmetic/code.hpp"
#include "../content/number_theory/modular_arithmetic/crt.hpp"
#include "../content/number_theory/modular_arithmetic/qpow.hpp"
#include "../content/number_theory/linear_sieve/code.hpp"
#include "../content/number_theory/linear_sieve/divisor_count.hpp"
#include "../content/number_theory/linear_sieve/divisor_sum.hpp"
#include "../content/number_theory/linear_sieve/factor_count.hpp"
#include "../content/number_theory/linear_sieve/min_prime.hpp"
#include "../content/number_theory/lagrange_interpolation/code.hpp"
#include "../content/number_theory/lagrange_interpolation/consecutive.hpp"
#include "../content/number_theory/lucas_theorem/code.hpp"
#include "../content/number_theory/lucas_theorem/combination.hpp"
#include "../content/number_theory/du_jiao_sieve/code.hpp"
#include "../content/number_theory/prime_factorization/code.hpp"
#include "../content/number_theory/prime_factorization/trial_divisors.hpp"
#include "../content/number_theory/quadratic_residue/code.hpp"
#include "../content/number_theory/stirling_numbers/code.hpp"
#include "../content/number_theory/number_theory_tricks/code.hpp"

int main() {
  {
    assert(gcd_euclid(30, 18) == 6);
    assert(gcd_euclid(-30, 18) == 6);
    assert(gcd_euclid(0, 0) == 0);
  }
  {
    long long x, y;
    long long g = exgcd(30, 18, x, y);
    assert(g == 6 && 30 * x + 18 * y == g);
  }
  {
    long long a = 2, m = 3;
    assert(merge_crt(a, m, 3, 5));
    assert(a == 8 && m == 15);
    assert(!merge_crt(a, m, 0, 6));
  }
  {
    assert(qpow(2, 10, 1000) == 24);
    assert(crt({2, 3, 2}, {3, 5, 7}) == 23);
  }
  {
    LinearSieve s(20);
    assert((s.primes == std::vector<int>{2, 3, 5, 7, 11, 13, 17, 19}));
    assert(s.phi[10] == 4 && s.mu[6] == 1 && s.mu[12] == 0);
  }
  {
    DivisorCountSieve d(20);
    DivisorSumSieve sigma(20);
    PrimeFactorCountSieve cnt(20);
    MinimumPrimeSieve minp(20);
    assert(d.d[12] == 6);
    assert(sigma.sigma[12] == 28);
    assert(cnt.omega[12] == 2 && cnt.Omega[12] == 3);
    assert(minp.minp[12] == 2 && minp.minp_exp[12] == 2);
  }
  {
    constexpr long long mod = 1000000007;
    std::vector<long long> xs{0, 1, 2}, ys{1, 4, 9};
    assert(lagrange_eval(xs, ys, 3, mod) == 16);
    assert(lagrange_eval(xs, ys, 1, mod) == 4);
  }
  {
    constexpr long long mod = 1000000007;
    Combination comb(20, mod);
    std::vector<long long> y{0, 1, 4, 9};
    assert(lagrange_consecutive(y, 4, mod, comb.ifact) == 16);
    assert(power_sum(2, 5, mod, comb.ifact) == 55);
    assert(comb.C(10, 3) == 120);
    Lucas lucas(7);
    assert(lucas.calc(10, 3) == 1);
  }
  {
    DuJiaoSieve sieve(10);
    assert(sieve.sum_mu(100) == 1);
    assert(sieve.sum_phi(100) == 3044);
    assert(sieve.sum_mu(1000) == 2);
    assert(sieve.sum_phi(1000) == 304192);
  }
  {
    Cipolla cipolla;
    long long root = cipolla.solve(10, 13);
    assert(root >= 0 && root * root % 13 == 10);
  }
  {
    PollardRho pollard;
    assert((pollard.factor(8051) ==
            std::vector<unsigned long long>{83, 97}));
    assert((pollard.divisors(12) ==
            std::vector<unsigned long long>{1, 2, 3, 4, 6, 12}));
    assert((divisors(36) == std::vector<int>{1, 2, 3, 4, 6, 9, 12, 18, 36}));
  }
  {
    auto s = stirling2(5, 5, 1000000007);
    assert(s[5][2] == 15 && s[5][3] == 25 && s[5][5] == 1);
  }
  {
    assert(josephus_last(7, 3) == 3);
    assert(josephus_kth(7, 3, 1) == 2);
    assert(josephus_kth(7, 3, 2) == 5);
  }
}
