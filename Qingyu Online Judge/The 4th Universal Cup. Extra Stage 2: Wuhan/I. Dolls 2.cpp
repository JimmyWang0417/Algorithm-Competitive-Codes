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
    vector<int> a;
    Main()
    {
        cin >> n;
        a.resize(n + 5);
        for (int i = 1; i <= n; ++i)
            cin >> a[i];
        vector<pair<int, int>> p;
        for (int i = 1, j; i < n; i = j - 1)
        {
            j = i + 1;
            while (j <= n && (a[i] < a[i + 1]) == (a[j - 1] < a[j]))
                ++j;
            p.emplace_back(i, j - 1);
        }
        // for (auto [x, y] : p)
        //     cout << x << ' ' << y << '\n';
        vector<array<array<array<int, 2>, 2>, 2>> dp((int)p.size(), {INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN, INT_MIN});
        dp[0][0][0][0] = 1;
        dp[0][0][1][0] = 1;
        for (int i = 1; i < (int)p.size(); ++i)
        {
            for (int j = 0; j < 2; ++j)
                for (int k = 0; k < 2; ++k)
                    for (int lassk = 0; lassk < 2; ++lassk)
                    {
                        if (dp[i - 1][j][k][lassk] < 0)
                            continue;
                        int l = p[i - 1 - lassk].first + j, r = p[i - 1 - lassk].second - k;
                        int L = min(a[l], a[r]), R = max(a[l], a[r]);
                        for (int x = 0; x < 2; ++x)
                            for (int y = 0; y < 2; ++y)
                            {
                                if (p[i].second - p[i].first == 1 && x == 1 && y == 1)
                                {
                                    if (!lassk)
                                        dp[i][j][k][1] = max(dp[i][j][k][1], dp[i - 1][j][k][lassk]);
                                }
                                else
                                {
                                    int ql = p[i].first + x, qr = p[i].second - y;
                                    int qL = min(a[ql], a[qr]), qR = max(a[ql], a[qr]);
                                    if (r + 1 == ql && !(qR < L || qL > R))
                                        dp[i][x][y][0] = max(dp[i][x][y][0], dp[i - 1][j][k][lassk] + 1);
                                }
                            }
                    }
        }
        int res = max(dp[(int)p.size() - 1][0][0][0], dp[(int)p.size() - 1][1][0][0]);
        cout << n - res << '\n';
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
