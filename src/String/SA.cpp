struct SA {
    int n;                   // 存储字符串的长度
    vector<int> sa, rk, lc;  // sa: 后缀数组, rk: 排名数组, lc: 最长公共前缀数组 (LCP)

    SA(string &s) {
        n = s.length();    // 初始化字符串的长度
        sa.resize(n + 1);  // 调整 sa 的大小为 n + 1
        lc.resize(n + 1);  // 调整 lc 的大小为 n
        rk.resize(n + 1);  // 调整 rk 的大小为 n + 1
        s = " " + s;
        iota(sa.begin(), sa.end(), 0);  // 初始化 sa 为 [1, 2, ..., n]
        sort(sa.begin() + 1, sa.end(), [&](int a, int b) {
            return s[a] < s[b];  // 按照首字符对索引进行排序
        });

        // 初始化 rk 数组
        rk[sa[1]] = 1;
        for (int i = 2; i <= n; ++i)
            rk[sa[i]] = rk[sa[i - 1]] + (s[sa[i]] != s[sa[i - 1]]);

        int k = 1;                    // 初始化 k 为 1，表示当前使用的字符串长度
        vector<int> tmp, cnt(n + 1);  // tmp: 临时数组, cnt: 计数排序的频率数组
        tmp.reserve(n + 1);           // 为 tmp 预留 n + 1 个元素的空间

        while (rk[sa[n]] < n) {  // 当排名最高的后缀排名小于 n时继续循环
            tmp.clear();
            tmp.push_back(0);  // 清空 tmp 数组

            for (int i = 1; i <= k; ++i)
                tmp.push_back(n - k + i);  // 越界部分默认为空字符

            for (auto i : sa)
                if (i >= k + 1)
                    tmp.push_back(i - k);  // 按第二关键字排序

            fill(cnt.begin(), cnt.end(), 0);  // 清空 cnt 数组
            for (int i = 1; i <= n; ++i)
                ++cnt[rk[i]];  // 统计每个排名出现的频率

            for (int i = 1; i <= n; ++i)
                cnt[i] += cnt[i - 1];  // 计算计数排序中的前缀和

            for (int i = n; i >= 1; --i) {
                int tmprk = cnt[rk[tmp[i]]];
                sa[tmprk] = tmp[i];
                cnt[rk[tmp[i]]] -= 1;
            }  // 根据 tmp 中的排名重建后缀数组

            std::swap(rk, tmp);  // tmp的功能变为之前的rk桶数组
            rk[sa[1]] = 1;       // 重新初始化排名数组，首先将 sa[1] 的排名设为 1

            for (int i = 2; i <= n; ++i)
                rk[sa[i]] = rk[sa[i - 1]] + (tmp[sa[i - 1]] < tmp[sa[i]] ||
                                             sa[i - 1] + k > n || tmp[sa[i - 1] + k] < tmp[sa[i] + k]);  // 基于前后部分进行比较
            k *= 2;                                                                                      // 将 k 翻倍，以便在下一个循环中比较更长的前缀
        }

        for (int i = 1, j = 0; i <= n; ++i) {
            if (rk[i] == 1) {  // 如果当前后缀是字典序最小的，不需要计算 LCP
                j = 0;
            } else {
                for (j -= j > 0; i + j <= n && sa[rk[i] - 1] + j <= n &&
                                 s[i + j] == s[sa[rk[i] - 1] + j];)
                    ++j;        // 计算与前一个后缀的最长公共前缀长度
                lc[rk[i]] = j;  // 排名为 i 的后缀与排名为 i-1 的 LCP
            }
        }
    }
};