uint64_t salt = chrono::steady_clock::now()
                    .time_since_epoch().count();

// 放在 g 建好之后，dfs(u, p) 返回不经过 p 的子树哈希
function<uint64_t(int, int)> dfs = [&](int u, int p) {
    uint64_t h = 1;
    for (int v : g[u]) if (v != p) {
        uint64_t x = dfs(v, u) ^ salt;
        x ^= x << 13;
        x ^= x >> 7;
        x ^= x << 17;
        h += x ^ salt;
    }
    return h;
};
