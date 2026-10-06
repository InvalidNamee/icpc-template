struct MCMF {
    struct Edge {
        int to, rev, cap;
        long long cost;
    };

    int n;
    vector<vector<Edge>> g;

    MCMF(int n) : n(n), g(n + 1) {}

    void add(int u, int v, int c, long long w) {
        g[u].push_back({v, (int)g[v].size(), c, w});
        g[v].push_back({u, (int)g[u].size() - 1, 0, -w});
    }

    pair<int, long long> flow(int s, int t) {
        int mf = 0;
        long long mc = 0;

        const long long INF = 4e18;

        vector<long long> h(n + 1);
        vector<long long> dis(n + 1);
        vector<int> pv(n + 1), pe(n + 1);

        while (1) {
            fill(dis.begin(), dis.end(), INF);
            priority_queue<pair<long long,int>,
                           vector<pair<long long,int>>,
                           greater<pair<long long,int>>> pq;

            dis[s] = 0;
            pq.push({0, s});

            while (!pq.empty()) {
                auto [d, u] = pq.top();
                pq.pop();

                if (d != dis[u])
                    continue;

                for (int i = 0; i < (int)g[u].size(); i++) {
                    auto &e = g[u][i];

                    if (e.cap == 0)
                        continue;

                    long long nd = d + e.cost + h[u] - h[e.to];

                    if (nd < dis[e.to]) {
                        dis[e.to] = nd;
                        pv[e.to] = u;
                        pe[e.to] = i;
                        pq.push({nd, e.to});
                    }
                }
            }

            if (dis[t] == INF)
                break;

            for (int i = 1; i <= n; i++) {
                if (dis[i] < INF)
                    h[i] += dis[i];
            }

            int aug = INT_MAX;

            for (int v = t; v != s; v = pv[v]) {
                aug = min(aug, g[pv[v]][pe[v]].cap);
            }

            for (int v = t; v != s; v = pv[v]) {
                auto &e = g[pv[v]][pe[v]];
                e.cap -= aug;
                g[v][e.rev].cap += aug;
            }

            mf += aug;
            mc += 1LL * aug * h[t];
        }

        return {mf, mc};
    }
};
