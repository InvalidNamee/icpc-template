__int128 convex_diameter2(const vector<Point>& p) {
    int n = p.size();
    if (n <= 1) return 0;
    if (n == 2) return norm2(p[0] - p[1]);

    __int128 ans = 0;
    int j = 1;
    for (int i = 0; i < n; i++) {
        int ni = (i + 1) % n;
        while (cross(p[i], p[ni], p[(j + 1) % n]) >
               cross(p[i], p[ni], p[j]))
            j = (j + 1) % n;
        ans = max(ans, norm2(p[i] - p[j]));
        ans = max(ans, norm2(p[ni] - p[j]));
    }
    return ans;
}
