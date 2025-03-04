// 需要开同步流！！！
__int128 read() {
    __int128 X = 0, f = 1;
    char c = getchar();
    while (!isdigit(c) && c != '-') c = getchar();
    if (c == '-')
        c = getchar(), f = -1;
    while (isdigit(c)) X = X * 10 + (c ^ 48), c = getchar();
    return X * f;
}
void write(__int128 x) {
    if (x < 0)
        x = -x, putchar('-');
    if (x > 9)
        write(x / 10);
    putchar(x % 10 + '0');
}