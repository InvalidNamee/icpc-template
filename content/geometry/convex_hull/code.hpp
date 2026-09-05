vector<Point> convex_hull(vector<Point> p) {
    sort(p.begin(), p.end());
    p.erase(unique(p.begin(), p.end()), p.end());
    if (p.size() <= 2) return p;

    vector<Point> lo, hi;
    for (Point x : p) {
        while (lo.size() >= 2 &&
               cross(lo[lo.size() - 2], lo.back(), x) <= 0)
            lo.pop_back();
        lo.push_back(x);
    }
    for (int i = (int)p.size() - 1; i >= 0; i--) {
        Point x = p[i];
        while (hi.size() >= 2 &&
               cross(hi[hi.size() - 2], hi.back(), x) <= 0)
            hi.pop_back();
        hi.push_back(x);
    }
    lo.pop_back();
    hi.pop_back();
    lo.insert(lo.end(), hi.begin(), hi.end());
    return lo;
}

void rotate_to_lowest(vector<Point>& p) {
    int s = min_element(p.begin(), p.end(), [](Point a, Point b) {
        return a.y != b.y ? a.y < b.y : a.x < b.x;
    }) - p.begin();
    rotate(p.begin(), p.begin() + s, p.end());
}

vector<Point> minkowski_sum(vector<Point> a, vector<Point> b) {
    rotate_to_lowest(a);
    rotate_to_lowest(b);
    vector<Point> ea, eb;
    for (int i = 0; i < (int)a.size(); i++)
        ea.push_back(a[(i + 1) % a.size()] - a[i]);
    for (int i = 0; i < (int)b.size(); i++)
        eb.push_back(b[(i + 1) % b.size()] - b[i]);

    vector<Point> c{a[0] + b[0]};
    int i = 0, j = 0;
    while (i < (int)ea.size() || j < (int)eb.size()) {
        Point e;
        if (j == (int)eb.size()) e = ea[i++];
        else if (i == (int)ea.size()) e = eb[j++];
        else {
            __int128 cr = cross(ea[i], eb[j]);
            if (cr > 0) e = ea[i++];
            else if (cr < 0) e = eb[j++];
            else e = ea[i++] + eb[j++];
        }
        c.push_back(c.back() + e);
    }
    c.pop_back();
    return c;
}
