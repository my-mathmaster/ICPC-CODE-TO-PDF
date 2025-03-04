const double eps = 1e-10;
double a, b, c, d, l, r;
//时间复杂度：O(log(n/eps))
// tips:要注意保证给的初始区间的积分是收敛的并且不要出现无定义点
// 反常积分的发散部分特判
// 1.对于初始区间，有时候显然不能直接赋值0和无穷大，
// 2.左端点复制成eps。
// 3.考虑右端点，根据题目条件的取值，
//当x=20（一个具体值）的时候代入发现已经远小于eps了故右端点设计为20.
double f(double x) {  // 积分函数
    return (c * x + d) / (a * x + b);
}
double simpson(double l, double r) {  // 辛普森公式
    return (r - l) * (f(l) + f(r) + 4 * f((l + r) / 2)) / 6;
}  // 二次函数特性

double asr(double l, double r, double ans) {  // 自适应
    // 分段simpson，如果划分足够小，低于误差就可以
    auto m = (l + r) / 2, a = simpson(l, m), b = simpson(m, r);
    if (fabs(a + b - ans) < eps)
        return ans;
    return asr(l, m, a) + asr(m, r, b);
}
int main() {
    scanf("%lf%lf%lf%lf%lf%lf", &a, &b, &c, &d, &l, &r);
    printf("%.6lf", asr(l, r, simpson(l, r)));
    return 0;
}