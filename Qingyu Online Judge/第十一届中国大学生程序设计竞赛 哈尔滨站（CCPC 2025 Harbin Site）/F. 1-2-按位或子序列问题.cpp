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
struct Main
{
    int n, a1;
    vector<int> a;
    vector<array<i64, 2>> f, g;
    vector<i64> h;
    Main()
    {
        cin >> n >> a1;
        a.resize(n + 5);
        f.resize(n + 5), g.resize(n + 5);
        h.resize(n + 5);
        for (int i = 1; i <= n; ++i)
            cin >> a[i];
        f[0][1] = 1;
        i64 ans = 0;
        for (int i = 1; i <= n; ++i)
        {
            (f[i][0] += (f[i - 1][0] + f[i - 1][1]) * (a[i] - 1)) %= mod;
            (f[i][1] += f[i - 1][0] + f[i - 1][1]) %= mod;

            (g[i][0] += (g[i - 1][0] + g[i - 1][1]) * (a[i] - 1)) %= mod;
            (g[i][1] += g[i - 1][0] + g[i - 1][1]) %= mod;

            if (i >= 3)
            {
                (h[i] += h[i - 2] + g[i - 3][0] + g[i - 3][1]) %= mod;
                if (a[i] > a[i - 2])
                {
                    (g[i][0] += h[i] * (a[i] - a[i - 2] - 1)) %= mod;
                    (g[i][1] += h[i]) %= mod;
                }
            }

            if (i < n)
            {
                auto res = (f[i - 1][1] + g[i - 1][1] + f[i][0] + g[i][0]) % mod;

                if (a[i + 1] == 1)
                    (g[i + 1][1] += res) %= mod;
                else
                {
                    (g[i + 1][0] += res * (a[i + 1] - 1)) %= mod;
                    (g[i + 1][1] += res) %= mod;
                }

                if (i + 3 <= n)
                {
                    (g[i + 3][0] += res * (a[i + 3] - a[i + 1])) %= mod;
                    (g[i + 3][1] += res) %= mod;

                    if (i + 5 <= n)
                        (h[i + 5] += res) %= mod;
                }
                if ((n & 1) != ((i + 1) & 1))
                    (ans += res) %= mod;
            }
            
            if ((n & 1) == (i & 1))
                (ans += g[i][0] + g[i][1]) %= mod;
        }
        cout << (ans + f[n][0] + f[n][1]) % mod << '\n';
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        Main();
    return 0;
}
