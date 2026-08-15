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
    constexpr static i64 limit = 1e16;
    int A, B;
    int q;
    unordered_map<i64, i64> fa, af;
    auto find(i64 x)
    {
        if (!fa[x])
            return x;
        return fa[x] = find(fa[x]);
    }
    auto unionn(i64 x, i64 y)
    {
        if (x > limit || y > limit)
            return;
        if (fa.find(x) == fa.end())
            af[x] = x;
        if (fa.find(y) == fa.end())
            af[y] = y;
        x = find(x), y = find(y);
        if (x != y)
            af[fa[x] = y] ^= af[x];
    }
    auto query(i64 x)
    {
        if (fa.find(x) == fa.end())
            return x;
        else
            return af[find(x)];
    }
    Main()
    {
        cin >> A >> B >> q;
        auto calc = [&](int d)
        {
            int X = A + B / d;
            for (int i = 1; i * i <= X; ++i)
                if (X % i == 0)
                {
                    if (__gcd(i, X / i) == 1)
                        unionn((i64)i * d, (i64)X / i * d);
                }
        };
        for (int d = 1; d * d <= B; ++d)
            if (B % d == 0)
            {
                calc(d);
                if (d * d < B)
                    calc(B / d);
            }
        while (q--)
        {
            i64 x;
            cin >> x;
            cout << query(x) << '\n';
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
