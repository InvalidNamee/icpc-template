using ll = long long;

const int NTT_MOD = 998244353;
const int NTT_ROOT = 3;

int ntt_qpow(int a, int b) {
    int result = 1;
    while (b) {
        if (b & 1) result = 1LL * result * a % NTT_MOD;
        a = 1LL * a * a % NTT_MOD;
        b >>= 1;
    }
    return result;
}

void ntt(vector<int>& a, bool invert) {
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
        int root = ntt_qpow(NTT_ROOT, (NTT_MOD - 1) / len);
        if (invert) root = ntt_qpow(root, NTT_MOD - 2);

        for (int i = 0; i < n; i += len) {
            int w = 1;
            for (int j = 0; j < len / 2; j++) {
                int x = a[i + j];
                int y = 1LL * a[i + j + len / 2] * w % NTT_MOD;

                a[i + j] = x + y;
                if (a[i + j] >= NTT_MOD) a[i + j] -= NTT_MOD;

                a[i + j + len / 2] = x - y;
                if (a[i + j + len / 2] < 0) {
                    a[i + j + len / 2] += NTT_MOD;
                }
                w = 1LL * w * root % NTT_MOD;
            }
        }
    }

    if (invert) {
        int inv_n = ntt_qpow(n, NTT_MOD - 2);
        for (int& x : a) x = 1LL * x * inv_n % NTT_MOD;
    }
}

vector<int> ntt_mul(vector<int> a, vector<int> b) {
    if (a.empty() || b.empty()) return {};

    int size = a.size() + b.size() - 1;
    int n = 1;
    while (n < size) n <<= 1;

    a.resize(n);
    b.resize(n);

    ntt(a, false);
    ntt(b, false);
    for (int i = 0; i < n; i++) {
        a[i] = 1LL * a[i] * b[i] % NTT_MOD;
    }
    ntt(a, true);

    a.resize(size);
    return a;
}
