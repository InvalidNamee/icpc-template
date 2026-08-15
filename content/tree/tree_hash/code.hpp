using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;

map<vi, int> tree_id;

// 返回以 u 为根、且不经过父亲 p 的有根树编号
int tree_hash(const vvi& g, int u, int p = 0) {
    vi h;
    for (int v : g[u]) if (v != p) h.push_back(tree_hash(g, v, u));
    sort(h.begin(), h.end());
    if (!tree_id.count(h)) tree_id[h] = (int)tree_id.size() + 1;
    return tree_id[h];
}
