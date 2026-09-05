using ll = long long;

struct Point {
    ll x = 0, y = 0;

    Point operator+(const Point& p) const {
        return {x + p.x, y + p.y};
    }
    Point operator-(const Point& p) const {
        return {x - p.x, y - p.y};
    }
    Point operator*(ll k) const { return {x * k, y * k}; }
    bool operator==(const Point& p) const {
        return x == p.x && y == p.y;
    }
    bool operator<(const Point& p) const {
        return x != p.x ? x < p.x : y < p.y;
    }
};

__int128 dot(Point a, Point b) {
    return (__int128)a.x * b.x + (__int128)a.y * b.y;
}

__int128 cross(Point a, Point b) {
    return (__int128)a.x * b.y - (__int128)a.y * b.x;
}

__int128 cross(Point a, Point b, Point c) {
    return cross(b - a, c - a);
}

__int128 norm2(Point a) { return dot(a, a); }

int sign(__int128 x) { return (x > 0) - (x < 0); }

int half(Point a) {
    return a.y > 0 || (a.y == 0 && a.x >= 0) ? 0 : 1;
}

// 要求 a、b 都不是零向量。
bool angle_less(Point a, Point b) {
    int ha = half(a), hb = half(b);
    if (ha != hb) return ha < hb;
    __int128 c = cross(a, b);
    if (c != 0) return c > 0;
    return norm2(a) < norm2(b);
}

const long double GEPS = 1e-12L;

struct DPoint {
    long double x = 0, y = 0;

    DPoint operator+(const DPoint& p) const {
        return {x + p.x, y + p.y};
    }
    DPoint operator-(const DPoint& p) const {
        return {x - p.x, y - p.y};
    }
    DPoint operator*(long double k) const {
        return {x * k, y * k};
    }
    DPoint operator/(long double k) const {
        return {x / k, y / k};
    }
};

int dsign(long double x) { return (x > GEPS) - (x < -GEPS); }
long double dot(DPoint a, DPoint b) { return a.x * b.x + a.y * b.y; }
long double cross(DPoint a, DPoint b) { return a.x * b.y - a.y * b.x; }
long double cross(DPoint a, DPoint b, DPoint c) {
    return cross(b - a, c - a);
}
long double norm2(DPoint a) { return dot(a, a); }
long double length(DPoint a) { return sqrtl(norm2(a)); }
DPoint unit(DPoint a) { return a / length(a); }

DPoint rotate(DPoint a, long double rad) {
    return {a.x * cosl(rad) - a.y * sinl(rad),
            a.x * sinl(rad) + a.y * cosl(rad)};
}
