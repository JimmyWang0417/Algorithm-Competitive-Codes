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
constexpr int mod = 998244353;
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
struct Main
{
    static inline int q;
    static inline array<array<array<pair<int, int>, 2>, 2>, 32> a;
    Main()
    {
        cin >> q;
        for (int i = 0; i < 32; ++i)
            a[i][0][0] = a[i][0][1] = a[i][1][0] = a[i][1][1] = {INT_MIN, INT_MIN};
        int lastans = 0;
        while (q--)
        {
            int o, x, y, w;
            cin >> o >> x >> y;
            x ^= lastans, y ^= lastans;
            if (o == 1)
            {
                cin >> w;
                w ^= lastans;
                for (int i = 0; i < 32; ++i)
                {
                    pair<int, int> z = {w, y};
                    if (a[i][(x >> i) & 1][0] < z)
                        swap(a[i][(x >> i) & 1][0], z);
                    if (a[i][(x >> i) & 1][0].second != z.second)
                        a[i][(x >> i) & 1][1] = max(a[i][(x >> i) & 1][1], z);
                }
            }
            else
            {
                int ans = 0;
                for (int i = 0; i < 32; ++i)
                {
                    if (a[i][((x >> i) & 1) ^ 1][0].second != y)
                        ans = max(ans, a[i][((x >> i) & 1) ^ 1][0].first);
                    else
                        ans = max(ans, a[i][((x >> i) & 1) ^ 1][1].first);
                }
                cout << (lastans = ans) << '\n';
            }
        }
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