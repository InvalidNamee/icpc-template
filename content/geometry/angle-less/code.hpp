struct Point {
    long long x, y;
};

int half(const Point& a) {
    return a.y > 0 || (a.y == 0 && a.x >= 0) ? 0 : 1;
}

// 要求 a、b 都不是零向量
bool angle_less(const Point& a, const Point& b) {
    int ha = half(a), hb = half(b);
    if (ha != hb) return ha < hb;

    __int128 cross =
        (__int128)a.x * b.y -
        (__int128)a.y * b.x;

    return cross > 0;
}