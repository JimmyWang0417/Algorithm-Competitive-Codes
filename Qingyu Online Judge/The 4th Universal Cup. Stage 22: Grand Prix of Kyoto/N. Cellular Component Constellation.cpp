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
constexpr int mod = 1e6 + 3;
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
        if (n <= m)
        {
            cout << "-1\n";
            return;
        }
        vector<vector<int>> a(n + 5, vector<int>(n + 5, -1));
        if (m == 2)
        {
            for (int i = 1; i <= n; ++i)
                for (int j = 1; j <= n; ++j)
                    a[i][j] = (i + j) & 1;
            for (int i = 1; i <= n; ++i)
                a[n][i] ^= 1;
        }
        else if (m & 1)
        {
            for (int i = 1; i * 2 - 1 <= m; ++i)
            {
                // 左上角
                for (int j = 1; j <= i; ++j)
                    a[i][j] = a[j][i] = (i & 1);
                // 右上角
                for (int j = 1; j <= i; ++j)
                    a[i][m + 2 - j] = a[j][m + 2 - i] = (i & 1) ^ 1;
                // 左下角
                for (int j = 1; j <= i; ++j)
                    a[m + 2 - i][j] = a[m + 2 - j][i] = (i & 1) ^ 1;
                // 右下角
                for (int j = 1; j <= i; ++j)
                    a[m + 2 - i][m + 2 - j] = a[m + 2 - j][m + 2 - i] = i & 1;
                for (int j = 1; j <= m; ++j)
                    a[m + 1][j] = -1;
            }
            for (int i = 1; i <= n; ++i)
                for (int j = 1; j <= n; ++j)
                {
                    if (a[i][j] == -1)
                        a[i][j] = i > 1 ? a[i - 1][j] ^ 1 : a[i][j - 1] ^ 1;
                }
        }
        else
        {
            for (int i = 1; i * 2 <= m; ++i)
            {
                // 左上角
                for (int j = 1; j <= i; ++j)
                    a[i][j] = a[j][i] = (i & 1);
                // 右上角
                for (int j = 1; j <= i; ++j)
                    a[i][m + 1 - j] = a[j][m + 1 - i] = (i & 1) ^ 1;
                // 左下角
                for (int j = 1; j <= i; ++j)
                    a[m + 1 - i][j] = a[m + 1 - j][i] = (i & 1) ^ 1;
                // 右下角
                for (int j = 1; j <= i; ++j)
                    a[m + 1 - i][m + 1 - j] = a[m + 1 - j][m + 1 - i] = i & 1;
                for (int j = 1; j <= m; ++j)
                    a[m + 1][j] = a[m][j];
            }
            for (int i = 1; i <= n; ++i)
                for (int j = 1; j <= n; ++j)
                {
                    if (a[i][j] == -1)
                        a[i][j] = j > 1 ? a[i][j - 1] ^ 1 : a[i - 1][j] ^ 1;
                }
        }
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                assert(a[i][j] != -1);
                cout << (a[i][j] == 1 ? '.' : '#');
            }
            cout << '\n';
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

