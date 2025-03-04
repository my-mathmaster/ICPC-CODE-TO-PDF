#include <bits/stdc++.h>
using namespace std;
using LL = long long;
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
mt19937_64 rnd_64(chrono::system_clock::now().time_since_epoch().count());
void gen() {
    ofstream fout("in.txt");
    /// 添加对应的输入——gen文件寻找
    fout.close();
}
int main() {
    system("g++ std.cpp  -std=c++20 -o std");
    system("g++ test.cpp -std=c++20 -o test");
    double TL = 5000.0;
    for (int i = 1; i <= 100; i++) {
        printf("iteration: %d\n", i);
        gen();
        system("std.exe < in.txt > ans.txt");
        double begin = clock();
        system("test.exe < in.txt > out.txt");
        double end = clock();
        double t = (double)(begin - end) / CLOCKS_PER_SEC * 1000;
        // cout << "Time Used: " << t << " ms" << endl;
        if (system("fc ans.txt out.txt")) {
            printf("test#%d WA\n", i);
            break;
        } else if (t > TL) {
            printf("test#%d TLE timeused  %.0lfms\n", i, t);
            break;
        } else {
            printf("test#%d AC  timeused  %.0lfms\n", i, t);
        }
    }
    return 0;
}