#include <string>
#include <vector>

using ll = long long;

vector<int> prefix_function(const string& s) {
    int n = (int)s.size() - 1;
    vector<int> pi(n + 1);
    for (int i = 2; i <= n; i++) {
        int j = pi[i - 1];
        while (j && s[i] != s[j + 1]) j = pi[j];
        if (s[i] == s[j + 1]) j++;
        pi[i] = j;
    }
    return pi;
}

vector<int> kmp(const string& text, const string& pat) {
    int n = (int)text.size() - 1;
    int m = (int)pat.size() - 1;
    vector<int> pi = prefix_function(pat), pos;
    for (int i = 1, j = 0; i <= n; i++) {
        while (j && text[i] != pat[j + 1]) j = pi[j];
        if (text[i] == pat[j + 1]) j++;
        if (j == m) {
            pos.push_back(i - m + 1);
            j = pi[j];
        }
    }
    return pos;
}
