using ll = long long;
const ll FWT_MOD = 998244353;

enum FWTType { OR, AND, XOR };

ll fwt_qpow(ll a, ll b) {
    ll result = 1;
    while (b) {
        if (b & 1) result = result * a % FWT_MOD;
        a = a * a % FWT_MOD;
        b >>= 1;
    }
    return result;
}

void fwt(vector<ll>& a, FWTType type, bool invert) {
    int n = a.size();

    for (int len = 1; len < n; len <<= 1) {
        for (int i = 0; i < n; i += len << 1) {
            for (int j = 0; j < len; j++) {
                ll x = a[i + j];
                ll y = a[i + j + len];

                if (type == OR) {
                    if (!invert) y = (y + x) % FWT_MOD;
                    else y = (y - x + FWT_MOD) % FWT_MOD;
                } else if (type == AND) {
                    if (!invert) x = (x + y) % FWT_MOD;
                    else x = (x - y + FWT_MOD) % FWT_MOD;
                } else {
                    ll sum = (x + y) % FWT_MOD;
                    ll difference = (x - y + FWT_MOD) % FWT_MOD;
                    x = sum;
                    y = difference;
                }

                a[i + j] = x;
                a[i + j + len] = y;
            }
        }
    }

    if (invert && type == XOR) {
        ll inv_n = fwt_qpow(n, FWT_MOD - 2);
        for (ll& x : a) x = x * inv_n % FWT_MOD;
    }
}

int fwt_size(int n) {
    int size = 1;
    while (size < n) size <<= 1;
    return size;
}

vector<ll> fwt_mul(
    vector<ll> a, vector<ll> b, FWTType type) {
    if (a.empty() || b.empty()) return {};

    int n = fwt_size(max(a.size(), b.size()));
    a.resize(n);
    b.resize(n);
    for (ll& x : a) x = (x % FWT_MOD + FWT_MOD) % FWT_MOD;
    for (ll& x : b) x = (x % FWT_MOD + FWT_MOD) % FWT_MOD;

    fwt(a, type, false);
    fwt(b, type, false);
    for (int i = 0; i < n; i++) a[i] = a[i] * b[i] % FWT_MOD;
    fwt(a, type, true);
    return a;
}

vector<ll> fwt_pow(
    vector<ll> a, ll k, FWTType type) {
    if (a.empty()) return {};

    a.resize(fwt_size(a.size()));
    for (ll& x : a) x = (x % FWT_MOD + FWT_MOD) % FWT_MOD;

    fwt(a, type, false);
    for (ll& x : a) x = fwt_qpow(x, k);
    fwt(a, type, true);
    return a;
}
