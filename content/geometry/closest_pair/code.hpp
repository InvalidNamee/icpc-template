struct ClosestPair {
    vector<Point> p, tmp, strip;

    __int128 solve(int l, int r) {
        const __int128 INF = (__int128)1 << 120;
        if (r - l <= 3) {
            __int128 ans = INF;
            for (int i = l; i < r; i++)
                for (int j = i + 1; j < r; j++)
                    ans = min(ans, norm2(p[i] - p[j]));
            sort(p.begin() + l, p.begin() + r,
                 [](Point a, Point b) {
                     return a.y != b.y ?
                         a.y < b.y : a.x < b.x;
                 });
            return ans;
        }

        int m = (l + r) / 2;
        ll midx = p[m].x;
        __int128 ans = min(solve(l, m), solve(m, r));
        merge(p.begin() + l, p.begin() + m,
              p.begin() + m, p.begin() + r, tmp.begin() + l,
              [](Point a, Point b) {
                  return a.y != b.y ? a.y < b.y : a.x < b.x;
              });
        copy(tmp.begin() + l, tmp.begin() + r, p.begin() + l);

        strip.clear();
        for (int i = l; i < r; i++) {
            __int128 dx = (__int128)p[i].x - midx;
            if (dx * dx >= ans) continue;
            for (int j = (int)strip.size() - 1; j >= 0; j--) {
                __int128 dy = (__int128)p[i].y - strip[j].y;
                if (dy * dy >= ans) break;
                ans = min(ans, norm2(p[i] - strip[j]));
            }
            strip.push_back(p[i]);
        }
        return ans;
    }

    __int128 run(vector<Point> a) {
        if (a.size() < 2) return -1;
        p.swap(a);
        sort(p.begin(), p.end());
        tmp.resize(p.size());
        strip.reserve(p.size());
        return solve(0, p.size());
    }
};
