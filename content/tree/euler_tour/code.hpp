using ll = long long;
using vi = vector<int>;
using vvi = vector<vi>;

struct EulerTour {
    int tim = 0;
    const vvi& g;
    vi dep, fa, tin, tout, pre;
    vi in2, out2, walk2; // 每个点进入、离开各出现一次，长度 2n
    vi first, walk;      // LCA 欧拉序，长度 2n-1

    EulerTour(const vvi& g, int root = 1) : g(g) {
        int n = (int)g.size() - 1;
        dep.assign(n + 1, 0); fa.assign(n + 1, 0);
        tin.assign(n + 1, 0); tout.assign(n + 1, 0);
        pre.assign(n + 1, 0); in2.assign(n + 1, 0);
        out2.assign(n + 1, 0); first.assign(n + 1, 0);
        walk2.push_back(0); walk.push_back(0); // 占住 0 号位置
        dfs(root, 0);
    }

    void dfs(int u, int p) {
        fa[u] = p;
        tin[u] = ++tim; pre[tim] = u;
        in2[u] = (int)walk2.size(); walk2.push_back(u);
        first[u] = (int)walk.size(); walk.push_back(u);
        for (int v : g[u]) if (v != p) {
            dep[v] = dep[u] + 1;
            dfs(v, u);
            walk.push_back(u);
        }
        tout[u] = tim;
        out2[u] = (int)walk2.size(); walk2.push_back(u);
    }
};
