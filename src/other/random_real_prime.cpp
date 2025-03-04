//随机素数
979345007 986854057502126921
935359631 949054338673679153
931936021 989518940305146613
984974633 972090414870546877
984858209 956380060632801307
static int findprime() {//随机生成质数
    random_device rd;
    mt19937 gen(rd());

    int n = gen() % 900000000 + 100000000;
    if (n % 2 == 0)
        n++;
    while (true) {
        bool ok = 1;
        for (int i = 3; i * i <= n; i += 2) {
            if (n % i == 0) {
                ok = 0;
                n += 2;
                break;
            }
        }
        if (ok)
            return n;
    }
}
//---------------------------------------------------------//
//伪随机数生成
#define u64 unsigned long long
#define u32 unsigned int
u64 xorshift(u64 x) { x ^= x << 13; x ^= x >> 7; x ^= x << 17; return x; }
u32 xorshift(u32 x) { x ^= x << 13; x ^= x >> 17; x ^= x << 5; return x; }
//真随机
#include <random>
#include <chrono>
mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
mt19937_64 rnd_64(chrono::system_clock::now().time_since_epoch().count());