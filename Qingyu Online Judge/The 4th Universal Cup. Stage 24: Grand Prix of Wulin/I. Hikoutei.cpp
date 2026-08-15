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
        vector<vector<int>> a(n, vector<int>(m));
        for (auto &i : a)
        {
            for (auto &j : i)
                cin >> j;
            ranges::sort(i);
        }
        i64 res = 0;
        for (int j = 0; j < m; ++j)
        {
            int minn = a[0][j];
            for (int i = 1; i < n; ++i)
                minn = min(minn, a[i][j]);
            res += minn;
        }
        cout << res << '\n';
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
