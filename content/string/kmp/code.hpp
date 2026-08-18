vector<int> prefix_function(const string& s) {
    int n = s.size();
    vector<int> pi(n);
    for (int i = 1; i < n; i++) {
        int j = pi[i - 1];
        while (j && s[i] != s[j]) j = pi[j - 1];
        if (s[i] == s[j]) j++;
        pi[i] = j;
    }
    return pi;
}

vector<int> kmp(const string& text, const string& pat) {
    int n = text.size(), m = pat.size();
    if (!m) return {};
    vector<int> pi = prefix_function(pat), pos;
    for (int i = 0, j = 0; i < n; i++) {
        while (j && text[i] != pat[j]) j = pi[j - 1];
        if (text[i] == pat[j]) j++;
        if (j == m) {
            pos.push_back(i - m + 1);
            j = pi[j - 1];
        }
    }
    return pos;
}
