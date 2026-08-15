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
template <typename T = int>
constexpr auto quickpow(i64 a, T b, int mod)
{
    a %= mod;
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
    i64 n;
    int m, mod;
    Main()
    {
        cin >> n >> m >> mod;
        set<i64> se;
        for (int i = 0; i < m; ++i)
        {
            i64 x;
            cin >> x;
            se.insert(x);
        }
        auto c = n - *se.rbegin();
        while (se.size() >= 2)
        {
            auto u = *prev(se.end());
            auto v = *prev(prev(se.end()));
            if (u >= 2 * v)
            {
                c += (u + 1) / 2 - v;
                se.erase(prev(se.end()));
            }
            else
            {
                auto w = se.size() >= 3 ? *prev(prev(prev(se.end()))) : 0;
                auto d = u - v;
                u -= (v - w) / d * d, v -= (v - w) / d * d;
                if (u >= v * 2)
                {
                    c += (u + 1) / 2 - v;
                    se.erase(prev(se.end()));
                    se.erase(prev(se.end()));
                    se.insert(v);
                }
                else
                {
                    se.erase(prev(se.end()));
                    se.erase(prev(se.end()));
                    se.insert(u - d);
                    se.insert(v - d);
                }
            }
        }
        c += (*se.begin() + 1) / 2;
        cout << quickpow(2, c, mod) << '\n';
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        Main();
    return 0;
}
