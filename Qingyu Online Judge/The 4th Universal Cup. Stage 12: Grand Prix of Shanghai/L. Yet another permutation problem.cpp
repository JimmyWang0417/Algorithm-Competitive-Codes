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
struct Main
{
    int n;
    vector<int> a, b;
    vector<vector<array<i64, 3>>> f, g;
    // 0 没变动；1 max_out->min_in; 2 min_out->max_in
    Main()
    {
        cin >> n;
        a.resize(n + 5);
        for (int i = 1; i <= n; ++i)
            cin >> a[i];
        f.assign(n + 5, vector<array<i64, 3>>(n + 5));
        g.assign(n + 5, vector<array<i64, 3>>(n + 5));
        for (int i = 1; i <= n; ++i)
        {
            f[i][i][0] = f[i][i][1] = f[i][i][2] = 1;
            g[i][i][0] = g[i][i][1] = g[i][i][2] = 1;
        }
        b = a;
        for (int len = 2; len <= n; ++len)
            for (int l = 1, r; (r = l + len - 1) <= n; ++l)
            {
                auto argmin = [&]()
                {
                    int pos = l;
                    for (int i = l + 1; i <= r; ++i)
                        if (b[pos] > b[i])
                            pos = i;
                    return pos;
                };
                auto argmax = [&]()
                {
                    int pos = l;
                    for (int i = l + 1; i <= r; ++i)
                        if (b[pos] < b[i])
                            pos = i;
                    return pos;
                };
                int p = argmin(), q = argmax();

                // f[l][r][0]
                if (p < q)
                {
                    for (int i = p; i < q; ++i)
                        (f[l][r][0] += f[l][i][1] * g[i + 1][r][2]) %= mod;
                    for (int i = q; i < r; ++i)
                        (f[l][r][0] -= f[l][i][0] * g[i + 1][r][0]) %= mod;
                }
                else
                {
                    for (int i = q; i < p; ++i)
                        (f[l][r][0] += f[l][i][2] * g[i + 1][r][1]) %= mod;
                    for (int i = p; i < r; ++i)
                        (f[l][r][0] -= f[l][i][0] * g[i + 1][r][0]) %= mod;
                }

                // f[l][r][1]
                b[p] = INT_MAX;
                int x = argmin();
                if (x < p)
                {
                    for (int i = x; i < p; ++i)
                        (f[l][r][1] += f[l][i][1] * g[i + 1][r][0]) %= mod;
                    for (int i = p; i < r; ++i)
                        (f[l][r][1] -= f[l][i][1] * g[i + 1][r][0]) %= mod;
                }
                else
                {
                    for (int i = p; i < x; ++i)
                        (f[l][r][1] += f[l][i][0] * g[i + 1][r][1]) %= mod;
                    for (int i = x; i < r; ++i)
                        (f[l][r][1] -= f[l][i][1] * g[i + 1][r][0]) %= mod;
                }
                b[p] = a[p];

                // f[l][r][2]
                b[q] = INT_MIN;
                int y = argmax();
                if (q < y)
                {
                    for (int i = q; i < y; ++i)
                        (f[l][r][2] += f[l][i][0] * g[i + 1][r][2]) %= mod;
                    for (int i = y; i < r; ++i)
                        (f[l][r][2] -= f[l][i][2] * g[i + 1][r][0]) %= mod;
                }
                else
                {
                    for (int i = y; i < q; ++i)
                        (f[l][r][2] += f[l][i][2] * g[i + 1][r][0]) %= mod;
                    for (int i = q; i < r; ++i)
                        (f[l][r][2] -= f[l][i][2] * g[i + 1][r][0]) %= mod;
                }
                b[q] = a[q];

                // g[l][r][0]
                g[l][r][0] = f[l][r][0];
                for (int i = l; i < r; ++i)
                    (g[l][r][0] += f[l][i][0] * g[i + 1][r][0]) %= mod;

                // g[l][r][1]
                g[l][r][1] = f[l][r][1];
                for (int i = l; i < p; ++i)
                    (g[l][r][1] += f[l][i][0] * g[i + 1][r][1]) %= mod;
                for (int i = p; i < r; ++i)
                    (g[l][r][1] += f[l][i][1] * g[i + 1][r][0]) %= mod;

                // g[l][r][2]
                g[l][r][2] = f[l][r][2];
                for (int i = l; i < q; ++i)
                    (g[l][r][2] += f[l][i][0] * g[i + 1][r][2]) %= mod;
                for (int i = q; i < r; ++i)
                    (g[l][r][2] += f[l][i][2] * g[i + 1][r][0]) %= mod;
            }
        cout << (g[1][n][0] + mod) % mod << '\n';
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        Main();
    return 0;
}

