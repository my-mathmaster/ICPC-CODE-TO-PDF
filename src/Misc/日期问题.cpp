// Mon = 0, ... % 7
// days since 1/1/1
// 从公元1年1月1日到给定日期（年 y、月 m、日 d）的天数
int getday(int y, int m, int d) {
    if (m < 3)
        --y, m += 12;
    return (365 * y + y / 4 - y / 100 + y / 400 + (153 * (m - 3) + 2) / 5 + d - 307);
}
// 自（公元1年1月1日）以来的n天数转换为y年m月d号
void date(int n, int& y, int& m, int& d) {
    n += 429 + ((4 * n + 1227) / 146097 + 1) * 3 / 4;
    y = (4 * n - 489) / 1461;
    n -= y * 1461 / 4;
    m = (5 * n - 1) / 153;
    d = n - m * 153 / 5;
    if (--m > 12)
        m -= 12, ++y;
}
// 已知年月日，求星期数。
int week(int y, int m, int d) {
    if (m <= 2)
        m += 12, y--;
    return (d + 2 * m + 3 * (m + 1) / 5 + y + y / 4 - y / 100 + y / 400) % 7 + 1;
}
//-----------------------------------------------
//记忆版本
int months[13] = {
    0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31
};

int is_leap(int year)//闰年判断
{
    if (year % 4 == 0 && year % 100 || year % 400 == 0)
        return 1;
    return 0;
}

int get_days(int y, int m)//给年月，输出日
{
    int s = months[m];
    if (m == 2) return s + is_leap(y);
    return s;
}