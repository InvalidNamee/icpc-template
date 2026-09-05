using ll = long long;

vector<vector<ll>> stirling2(
  int n, int k, ll mod
) {
  vector s(n + 1, vector<ll>(k + 1));
  s[0][0] = 1;
  for (int i = 1; i <= n; ++i) {
    for (int j = 1; j <= min(i, k); ++j) {
      s[i][j] = (s[i - 1][j - 1]
               + (__int128)j * s[i - 1][j]) % mod;
    }
  }
  return s;
}
