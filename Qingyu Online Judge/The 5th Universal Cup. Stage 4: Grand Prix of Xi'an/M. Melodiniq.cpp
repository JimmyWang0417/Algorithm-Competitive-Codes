#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef __float80 f80;
typedef __float128 f128;
constexpr int mod = 1e9 + 7;
template <typename T = int>
constexpr auto quickpow(i64 a, T b = mod - 2)
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
vector<i64> fac, ifac;
auto init(int n)
{
    fac.resize(n + 1);
    ifac.resize(n + 1);
    fac[0] = 1;
    for (int i = 1; i <= n; ++i)
        fac[i] = fac[i - 1] * i % mod;
    ifac[n] = quickpow(fac[n]);
    for (int i = n; i >= 1; --i)
        ifac[i - 1] = ifac[i] * i % mod;
}
auto C(int n, int m) -> i64
{
    if (n < 0 || n < m)
        return 0;
    return fac[n] * ifac[m] % mod * ifac[n - m] % mod;
}
struct Main
{
    int n;
    array<string, 4> a = {};
    array<int, 4> b = {2000, 2000, 2000, 2000};
    array<int, 4> c = {};
    Main()
    {
        cin >> n;
        for (int i = 0; i < 4; ++i)
            cin >> a[i];
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < 4; ++j)
            {
                if (a[j][i] == 'H')
                {
                    if (++c[j] == 100)
                    {
                        for (int k = 0; k < 4; ++k)
                        {
                            if (j == k)
                                continue;
                            b[k] += 30;
                        }
                        c[j] = 0;
                    }
                }
                else
                {
                    c[j] = 0;
                    if (a[j][i] == 'J')
                        b[j] -= 50;
                    else if (a[j][i] == 'A')
                        b[j] -= 100;
                    else if (a[j][i] == 'M')
                        b[j] -= 200;
                }
            }
            for (int j = 0; j < 4; ++j)
            {
                b[j] = min(b[j], 2000);
                if (b[j] <= 0)
                    b[j] = INT_MIN / 2;
            }
        }
        for (int j = 0; j < 4; ++j)
            cout << max(b[j], 0) << ' ';
        cout << '\n';
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    // init(100);
    int T = 1;
    cin >> T;
    while (T--)
        Main();
    return 0;
}
