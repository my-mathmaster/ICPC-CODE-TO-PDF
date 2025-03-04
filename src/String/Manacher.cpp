struct PAS {
    string s = "#";
    int len = 1;
    vector<int> p;
   // vector<pair<int, int>> all;
    PAS() {}
    PAS(string t) {
        for (auto c : t) {
            s += c;
            s += '#';
            len += 2;
        }
        s = " " + s;
        p.resize(len + 1);
        getp(s);
    }
    vector<int> getp(string t) {
        int mid = 0, r = 0;
        for (int i = 1; i <= len; i++) {
            if (i > r)
                p[i] = 1;
            else
                p[i] = min(p[2 * mid - i], r - i + 1);
            while (i - p[i] > 0 && i + p[i] <= len && t[i - p[i]] == t[i + p[i]]) {
                p[i] += 1;
                // int ql, qr;
                // if ((i - p[i] + 1) % 2 == 0)
                //     ql = (i - p[i] + 1) / 2;
                // else
                //     ql = (i - p[i] + 2) / 2;
                // if ((i + p[i] - 1) % 2 == 0)
                //     qr = (i + p[i] - 1) / 2;
                // else
                //     qr = (i + p[i] - 2) / 2;
                // all.emplace_back(ql, qr);
            }
            if (i + p[i] - 1 > r)
                mid = i, r = i + p[i] - 1;
        }
        return p;
    }
    int getmax() {
        int ans = 0;
        for (int i = 1; i <= len; i++) {
            ans = max(ans, p[i]);
        }
        return (ans - 1);
    }
};