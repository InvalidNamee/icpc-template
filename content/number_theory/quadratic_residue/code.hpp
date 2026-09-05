struct Cipolla {
  using ll = long long;
  using i128 = __int128_t;

  struct Node {
    ll x, y;
  };

  ll p, w;

  ll qpow(ll a, ll b) const {
    ll res = 1;
    while (b) {
      if (b & 1) res = (i128)res * a % p;
      a = (i128)a * a % p;
      b >>= 1;
    }
    return res;
  }

  Node mul(Node a, Node b) const {
    return {
      (ll)(((i128)a.x * b.x + (i128)a.y * b.y % p * w) % p),
      (ll)(((i128)a.x * b.y + (i128)a.y * b.x) % p)
    };
  }

  Node qpow(Node a, ll b) const {
    Node res{1, 0};
    while (b) {
      if (b & 1) res = mul(res, a);
      a = mul(a, a);
      b >>= 1;
    }
    return res;
  }

  // p 为素数。返回一个平方根；-1 表示无解。
  ll solve(ll n, ll mod) {
    p = mod;
    n = (n % p + p) % p;
    if (p == 2 || n == 0) return n;
    if (qpow(n, (p - 1) / 2) != 1) return -1;

    static mt19937_64 rng(
      chrono::steady_clock::now()
        .time_since_epoch().count()
    );
    ll a;
    while (true) {
      a = rng() % p;
      w = ((i128)a * a - n + p) % p;
      if (qpow(w, (p - 1) / 2) == p - 1) break;
    }
    return qpow(Node{a, 1}, (p + 1) / 2).x;
  }
};
