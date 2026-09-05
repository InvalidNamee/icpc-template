using ll = long long;
using u32 = uint32_t;
using u64 = uint64_t;

struct RandomGenerator {
    u64 state;

    RandomGenerator(u64 seed = chrono::steady_clock::now()
        .time_since_epoch().count()) : state(seed) {}

    u64 next_u64() {
        u64 z = (state += 0x9e3779b97f4a7c15ULL);
        z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9ULL;
        z = (z ^ (z >> 27)) * 0x94d049bb133111ebULL;
        return z ^ (z >> 31);
    }

    u32 next_u32() { return next_u64(); }
    ll next_i64() { return (ll)next_u64(); }
    int32_t next_i32() { return (int32_t)next_u32(); }
    static u64 power(u64 a, u64 b, u64 mod) {
        u64 res = 1;
        while (b) {
            if (b & 1) res = (__uint128_t)res * a % mod;
            a = (__uint128_t)a * a % mod;
            b >>= 1;
        }
        return res;
    }
    static bool is_prime(u64 n) {
        if (n < 2) return false;
        for (u64 p : {2, 3, 5, 7, 11, 13,
                      17, 19, 23, 29, 31, 37}) {
            if (n % p == 0) return n == p;
        }
        u64 d = n - 1, s = 0;
        while (!(d & 1)) d >>= 1, s++;
        for (u64 a : {2, 325, 9375, 28178,
                      450775, 9780504, 1795265022}) {
            if (a % n == 0) continue;
            u64 x = power(a % n, d, n);
            if (x == 1 || x == n - 1) continue;
            bool ok = false;
            for (u64 r = 1; r < s; r++) {
                x = (__uint128_t)x * x % n;
                if (x == n - 1) {
                    ok = true;
                    break;
                }
            }
            if (!ok) return false;
        }
        return true;
    }
    ll random_prime() {
        while (true) {
            u64 x = next_u64() & ((1ULL << 60) - 1);
            x |= (1ULL << 60) | 1;
            if (is_prime(x)) return x;
        }
    }
};
