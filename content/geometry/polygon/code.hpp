__int128 polygon_area2(const vector<Point>& p) {
    __int128 s = 0;
    for (int i = 0, n = p.size(); i < n; i++)
        s += cross(p[i], p[(i + 1) % n]);
    return s;
}

// -1: 外部，0: 边界，1: 内部。
int point_in_polygon(Point q, const vector<Point>& p) {
    bool in = false;
    for (int i = 0, n = p.size(); i < n; i++) {
        Point a = p[i], b = p[(i + 1) % n];
        if (on_segment(q, a, b)) return 0;
        __int128 c = cross(a, b, q);
        if (a.y <= q.y && q.y < b.y && c > 0) in = !in;
        if (b.y <= q.y && q.y < a.y && c < 0) in = !in;
    }
    return in ? 1 : -1;
}

ll lattice_boundary(const vector<Point>& p) {
    ll b = 0;
    for (int i = 0, n = p.size(); i < n; i++) {
        Point d = p[(i + 1) % n] - p[i];
        b += gcd(llabs(d.x), llabs(d.y));
    }
    return b;
}

__int128 lattice_interior(const vector<Point>& p) {
    __int128 a2 = polygon_area2(p);
    if (a2 < 0) a2 = -a2;
    return (a2 - lattice_boundary(p) + 2) / 2;
}
