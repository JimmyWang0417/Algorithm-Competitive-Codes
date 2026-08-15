#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef __float80 f80;
typedef __float128 f128;
constexpr int mod = 998244353;
constexpr auto quickpow(i64 a, int b)
{
    i64 res = 1;
    while (b)
    {
        if (b & 1)
            (res *= a) %= mod;
        (a *= a) %= mod;
        b >>= 1;
    }
    return res;
}
struct Main
{
    Main()
    {
        i64 n;
        cin >> n;
        auto calc = [](auto x)
        {
            array<int, 10> cnt({});
            while (x)
            {
                ++cnt[x % 10];
                x /= 10;
            }
            return cnt;
        };
        auto origin = calc(n);
        int res = 0;
        for (int i = 2; i <= 9; i++)
        {
            if (n % i)
                continue;
            i64 div = n / i;
            if (div <= i)
                continue;
            if (origin == calc(div))
                ++res;
        }
        cout << res << '\n';
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        Main();
    return 0;
}
