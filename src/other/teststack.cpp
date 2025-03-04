#include <bits/stdc++.h>
using namespace std;
int cur = 1;
// 需要关闭O2测试
void func() {
    cout << cur << "MB" << endl;
    char arr[1024 * 1024];  // 1MB
    // 使用数组以防止优化
    // if (cur > 1024 )
    //     return;
    int sum = 0;
    cur++;
    func();
}
int main() {
    func();
    cout << "Yes" << endl;
    cout << cur << "MB" << endl;
    return 0;
}
