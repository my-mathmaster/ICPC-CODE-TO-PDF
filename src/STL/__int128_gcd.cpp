using i128 = __int128;
i128 gcd(i128 a, i128 b) {
    return b ? gcd(b, a % b) : a;
}