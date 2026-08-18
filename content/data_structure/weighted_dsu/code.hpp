struct WeightedDSU {
  vector<int> fa;
  vector<long long> dis;

  explicit WeightedDSU(int n) : fa(n), dis(n) {
    iota(fa.begin(), fa.end(), 0);
  }

  int find(int x) {
    if (fa[x] == x) return x;
    int parent = fa[x];
    fa[x] = find(parent);
    dis[x] += dis[parent];
    return fa[x];
  }

  // 添加约束 value[y] - value[x] = w。
  bool merge(int x, int y, long long w) {
    int fx = find(x), fy = find(y);
    if (fx == fy) return dis[y] - dis[x] == w;
    fa[fy] = fx;
    dis[fy] = w + dis[x] - dis[y];
    return true;
  }

  bool same(int x, int y) {
    return find(x) == find(y);
  }

  // 调用前保证 x、y 连通。
  long long query(int x, int y) {
    find(x);
    find(y);
    return dis[y] - dis[x];
  }
};
