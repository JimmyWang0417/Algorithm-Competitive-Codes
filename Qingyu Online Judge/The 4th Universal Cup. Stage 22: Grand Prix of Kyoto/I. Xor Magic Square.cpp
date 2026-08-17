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
    int n;
    vector<vector<int>> a;
    constexpr static int b[5][5] = {{1, 2, 3, 1, 1},
                                    {1, 1, 1, 2, 3},
                                    {2, 3, 1, 1, 1},
                                    {1, 1, 2, 3, 1},
                                    {3, 1, 1, 1, 2}};
    Main()
    {
        cin >> n;
        a.resize(n, vector<int>(n));
        if (n % 2 == 0)
        {
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    a[i][j] = 1;
        }
        else
        {
            if (n <= 3)
            {
                cout << "-1\n";
                return;
            }
            for (int i = 0; i < 5; ++i)
                for (int j = 0; j < 5; ++j)
                    a[i + (n - 5) / 2][j + (n - 5) / 2] = b[i][j];
            for (int i = 0; i < (n - 5) / 2; ++i)
            {
                a[i][i] = 2;
                a[n - i - 1][n - i - 1] = 2;
                a[n - i - 1][i] = 3;
                a[i][n - i - 1] = 3;
            }
            for (int i = 0; i < n; ++i)
                for (int j = 0; j < n; ++j)
                    if (!a[i][j])
                        a[i][j] = 1;
        }
        int sum = 0;
        for (const auto &i : a)
            for (auto j : i)
                sum += j;
        cout << sum << '\n';
        for (const auto &i : a)
        {
            for (auto j : i)
                cout << j << ' ';
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
