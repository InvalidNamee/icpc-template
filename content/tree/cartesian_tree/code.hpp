// 返回 {根, 儿子数组}，son[u] = {左儿子, 右儿子}
pair<int, vpii> cartesian_tree(const vi& a) {
    int n = (int)a.size() - 1;
    vpii son(n + 1, {-1, -1});
    vi st;
    for (int i = 1; i <= n; i++) {
        int last = -1;
        // 当前是小根笛卡尔树；把 > 改成 < 就是大根
        while (!st.empty() && a[st.back()] > a[i]) last = st.back(), st.pop_back();
        if (!st.empty()) son[st.back()].second = i;
        son[i].first = last;
        st.push_back(i);
    }
    return {st.front(), son};
}
