#include <bits/stdc++.h>
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
    static inline i64 mod;
    static inline vector<i64> f, g;
    static inline vector<i64> p;
    static constexpr auto F(i64 n)
    {
        return f[ranges::upper_bound(p, n) - p.begin() - 1];
    }
    static constexpr auto G(i64 n)
    {
        return g[ranges::upper_bound(p, n) - p.begin() - 1];
    }
    static constexpr auto init(int f0, int g0, i64 M)
    {
        mod = M;
        constexpr static int border = 13;
        constexpr static i64 limit = 1e15;
        f.resize(border + 1), g.resize(border + 1);
        f[0] = f0, g[0] = g0;
        for (int i = 1; i <= border; ++i)
        {
            f[i] = max((i64)i, g[i / 2] + g[i / 3] + g[i / 5] + g[i / 7]);
            g[i] = max((i64)i, f[i / 2] + f[i / 3] + f[i / 4] + f[i / 5]);
        }
        for (int i = 0; i <= border; ++i)
            f[i] %= mod, g[i] %= mod;
        p = {0};
        for (int i = 1; i <= border; ++i)
            for (i64 j = i; j <= limit; j *= 2)
                for (i64 k = j; k <= limit; k *= 3)
                    for (i64 l = k; l <= limit; l *= 5)
                        for (i64 m = l; m <= limit; m *= 7)
                            p.emplace_back(m);
        ranges::sort(p);
        p.erase(unique(p.begin(), p.end()), p.end());
        f.resize(p.size()), g.resize(p.size());
        for (int i = border + 1; i < (int)p.size(); ++i)
        {
            f[i] = (G(p[i] / 2) + G(p[i] / 3) + G(p[i] / 5) + G(p[i] / 7)) % mod;
            g[i] = (F(p[i] / 2) + F(p[i] / 3) + F(p[i] / 4) + F(p[i] / 5)) % mod;
        }
    }
    Main()
    {
        i64 m;
        cin >> m;
        cout << F(m) << ' ' << G(m) << '\n';
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int f0, g0;
    i64 M;
    int T = 1;
    // cin >> T;
    cin >> f0 >> g0 >> T >> M;
    Main::init(f0, g0, M);
    while (T--)
        Main();
    return 0;
}
