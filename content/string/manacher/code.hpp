using ll = long long;

struct Manacher {
    int n;
    string s;
    vector<int> odd, even;

    Manacher(const string& s) : n((int)s.size() - 1), s(s),
                                odd(n + 1), even(n + 1) {
        for (int i = 1, l = 1, r = 0; i <= n; i++) {
            int k = i > r ? 1 : min(odd[l + r - i], r - i + 1);
            while (i - k >= 1 && i + k <= n && s[i - k] == s[i + k]) k++;
            odd[i] = k;
            if (i + k - 1 > r) l = i - k + 1, r = i + k - 1;
        }
        for (int i = 1, l = 1, r = 0; i <= n; i++) {
            int k = i > r ? 0 : min(even[l + r - i + 1], r - i + 1);
            while (i - k - 1 >= 1 && i + k <= n &&
                   s[i - k - 1] == s[i + k]) k++;
            even[i] = k;
            if (i + k - 1 > r) l = i - k, r = i + k - 1;
        }
    }

    bool is_pal(int l, int r) {
        int len = r - l + 1;
        if (len & 1) return odd[(l + r) / 2] >= len / 2 + 1;
        return even[(l + r + 1) / 2] >= len / 2;
    }
};
