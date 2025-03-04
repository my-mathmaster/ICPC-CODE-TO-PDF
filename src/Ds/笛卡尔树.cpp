struct DKR {
    int n;
    vector<int> l, r;
    int root;
    stack<int> st;

    DKR(int nn) : n(nn), l(nn + 1), r(nn + 1), root(0) {}
    // 默认为小根堆，维护最小值所在区间
    // dkr.built(a,less<int>());大根堆
    int built(const vector<int>& a, function<bool(int, int)> cmp = greater<int>()) {
        while (!st.empty()) st.pop();  // 清空栈
        for (int i = 1; i <= n; i++) {
            int last = 0;

            while (!st.empty() && cmp(a[st.top()], a[i])) {
                last = st.top();
                st.pop();
            }
            if (!st.empty()) {
                r[st.top()] = i;
            } else {
                root = i;
            }
            l[i] = last;
            st.push(i);
        }
        return root;
    }
};