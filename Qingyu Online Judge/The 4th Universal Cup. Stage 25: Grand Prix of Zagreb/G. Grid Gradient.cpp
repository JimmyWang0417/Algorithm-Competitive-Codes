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
    int n, m;
    Main()
    {
        cin >> n >> m;
        vector<vector<int>> G(m + 1);
        for (int S = 0; S < (1 << m); ++S)
        {
            int p = 0;
            for (int i = 1; i < m; ++i)
                if ((S >> (i - 1) & 1) && (S >> i & 1))
                {
                    if (p == 0)
                        p = i;
                    else
                        p = -1;
                }
            for (int i = 0; i < m; ++i)
                if (!p || p == i)
                    G[i].push_back(S);
        }
        vector<int> f(1 << m), g(1 << m);
        f[0] = 1;
        for (int _ = 0; _ < n; ++_)
        {
            for (int p = 0; p < m; ++p)
            {
                for (auto S : G[p])
                {
                    (g[S & (~(1 << p))] += f[S]) %= mod;
                    if ((!p || (~S >> (p - 1) & 1)) && (~S >> p & 1))
                        (g[S | (1 << p)] += f[S]) %= mod;
                    f[S] = 0;
                }
                for (int S : G[(p + 1) % m])
                {
                    f[S] = g[S];
                    g[S] = 0;
                }
            }
        }
        i64 res = 0;
        for (int S : G[0])
            (res += f[S]) %= mod;
        cout << (res * 2) % mod << '\n';
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
