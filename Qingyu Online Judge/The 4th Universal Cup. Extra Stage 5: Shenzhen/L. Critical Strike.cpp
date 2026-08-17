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
    int n, m;
    Main()
    {
        cin >> n >> m;
        vector<tuple<int, int, int>> a(n);
        for (auto &[p, v, w] : a)
            cin >> p >> v >> w;
        ranges::sort(a, [](auto x, auto y)
                     { return get<1>(x) < get<1>(y); });
        vector<double> dp(m + 1);
        for (int i = 1; i <= n; ++i)
        {
            auto [p, v, w] = a[i - 1];
            for (int j = m; j >= w; --j)
                dp[j] = max(dp[j], p / 100.0 * v + (1 - p / 100.0) * dp[j - w]);
        }
        cout << fixed << setprecision(9) << dp[m] << '\n';
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

