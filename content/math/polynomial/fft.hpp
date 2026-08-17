using ll = long long;
using cd = complex<double>;
const double PI = acos(-1.0);

void fft(vector<cd>& a, bool invert) {
    int n = a.size();

    for (int i = 1, j = 0; i < n; i++) {
        int bit = n >> 1;
        while (j & bit) {
            j ^= bit;
            bit >>= 1;
        }
        j ^= bit;
        if (i < j) swap(a[i], a[j]);
    }

    for (int len = 2; len <= n; len <<= 1) {
        double angle = 2 * PI / len * (invert ? -1 : 1);
        cd root(cos(angle), sin(angle));

        for (int i = 0; i < n; i += len) {
            cd w = 1;
            for (int j = 0; j < len / 2; j++) {
                cd x = a[i + j];
                cd y = a[i + j + len / 2] * w;
                a[i + j] = x + y;
                a[i + j + len / 2] = x - y;
                w *= root;
            }
        }
    }

    if (invert) {
        for (cd& x : a) x /= n;
    }
}

vector<ll> fft_mul(
    vector<ll> a, vector<ll> b) {
    if (a.empty() || b.empty()) return {};

    int size = a.size() + b.size() - 1;
    int n = 1;
    while (n < size) n <<= 1;

    vector<cd> fa(a.begin(), a.end());
    vector<cd> fb(b.begin(), b.end());
    fa.resize(n);
    fb.resize(n);

    fft(fa, false);
    fft(fb, false);
    for (int i = 0; i < n; i++) fa[i] *= fb[i];
    fft(fa, true);

    vector<ll> result(size);
    for (int i = 0; i < size; i++) {
        result[i] = llround(fa[i].real());
    }
    return result;
}
