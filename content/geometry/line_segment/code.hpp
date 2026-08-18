bool on_segment(Point p, Point a, Point b) {
    return cross(a, b, p) == 0 && dot(p - a, p - b) <= 0;
}

bool segment_intersect(Point a, Point b, Point c, Point d) {
    __int128 c1 = cross(a, b, c), c2 = cross(a, b, d);
    __int128 c3 = cross(c, d, a), c4 = cross(c, d, b);
    if (c1 == 0 && on_segment(c, a, b)) return true;
    if (c2 == 0 && on_segment(d, a, b)) return true;
    if (c3 == 0 && on_segment(a, c, d)) return true;
    if (c4 == 0 && on_segment(b, c, d)) return true;
    return sign(c1) * sign(c2) < 0 && sign(c3) * sign(c4) < 0;
}

bool line_parallel(DPoint v, DPoint w) {
    return dsign(cross(v, w)) == 0;
}

DPoint line_intersection(DPoint p, DPoint v, DPoint q, DPoint w) {
    long double t = cross(q - p, w) / cross(v, w);
    return p + v * t;
}
