struct GridDistance {
    using P = pair<long long, long long>;

    static P transform(P p) {
        return {p.first + p.second, p.first - p.second};
    }

    static long long manhattan(P a, P b) {
        return llabs(a.first - b.first) + llabs(a.second - b.second);
    }

    static long long chebyshev(P a, P b) {
        return max(llabs(a.first - b.first), llabs(a.second - b.second));
    }
};
