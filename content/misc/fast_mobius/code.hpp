using ll = long long;

// d 和 f 使用 0-based 数组下标；d[i] 是对应状态的实际约数值
template<class T>
void mob(const vector<ll>& d, const vector<ll>& ps, vector<T>& f) {
    int n = d.size();
    ll m = d.back();

    for (ll p : ps) {
        int j = 0;
        for (int i = 0; i < n; i++) {
            if (m / d[i] % p) continue;

            ll x = d[i] * p;
            while (d[j] < x) j++;

            f[i] -= f[j];
        }
    }
}
