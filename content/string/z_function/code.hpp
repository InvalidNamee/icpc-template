#include <algorithm>
#include <string>
#include <vector>

using ll = long long;

vector<int> z_function(const string& s) {
    int n = (int)s.size() - 1;
    vector<int> z(n + 1);
    z[1] = n;
    for (int i = 2, l = 1, r = 0; i <= n; i++) {
        if (i <= r) z[i] = min(r - i + 1, z[i - l + 1]);
        while (i + z[i] <= n && s[z[i] + 1] == s[i + z[i]])
            z[i]++;
        if (i + z[i] - 1 > r) {
            l = i;
            r = i + z[i] - 1;
        }
    }
    return z;
}
