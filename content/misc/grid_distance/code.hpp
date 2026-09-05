using ll = long long;

struct GridDistance {
    using P = pair<ll, ll>;

    static P transform(P p) {
        return {p.first + p.second, p.first - p.second};
    }

    static ll manhattan(P a, P b) {
        return llabs(a.first - b.first) +
               llabs(a.second - b.second);
    }

    static ll chebyshev(P a, P b) {
        return max(
            llabs(a.first - b.first),
            llabs(a.second - b.second)
        );
    }
};
