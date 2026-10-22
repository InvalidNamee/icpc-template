using ll = long long;

struct Date {
    ll y;
    int m, d;

    // 合法公历日期 -> 自 1970-01-01 起的天数
    static ll encode(ll y, int m, int d) {
        y -= m <= 2;
        ll e = (y >= 0 ? y : y - 399) / 400;
        int a = y - e * 400;
        int b = (153 * (m > 2 ? m - 3 : m + 9)
                 + 2) / 5 + d - 1;
        int c = a * 365 + a / 4 - a / 100 + b;
        return e * 146097 + c - 719468;
    }

    // 连续天数 -> 公历日期
    static Date decode(ll z) {
        z += 719468;
        ll e = (z >= 0 ? z : z - 146096) / 146097;
        int c = z - e * 146097;
        int a = (c - c / 1460 + c / 36524
                 - c / 146096) / 365;
        ll y = e * 400 + a;
        int b = c - (365 * a + a / 4 - a / 100);
        int t = (5 * b + 2) / 153;
        int d = b - (153 * t + 2) / 5 + 1;
        int m = t < 10 ? t + 3 : t - 9;
        return {y + (m <= 2), m, d};
    }
};
