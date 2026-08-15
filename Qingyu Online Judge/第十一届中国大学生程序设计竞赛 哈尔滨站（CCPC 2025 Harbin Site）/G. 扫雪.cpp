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
    vector<vector<int>> a;
    auto check(i64 mid)
    {
        vector<i64> c(m + 5);
        c[1] = mid;
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
                c[j] += a[i][j];
            for (int j = m; j >= 1; --j)
                if (c[j] < 0)
                {
                    c[j - 1] += c[j];
                    c[j] = 0;
                }
            if (c[0] < 0)
                return false;
        }
        return true;
    }
    auto calc(i64 mid)
    {
        vector<i64> c(m + 5);
        c[1] = mid;
        for (int i = 1; i <= n; ++i)
        {
            for (int j = 1; j <= m; ++j)
                c[j] += a[i][j];
            for (int j = m; j >= 1; --j)
                if (c[j] < 0)
                {
                    c[j - 1] += c[j];
                    c[j] = 0;
                }
        }
        i64 res = mid;
        for (int j = 1; j <= m; ++j)
            res += c[j];
        return res;
    }
    Main()
    {
        cin >> n >> m;
        a.assign(n + 5, vector<int>(m + 5));
        for (int i = 1; i <= n; ++i)
            for (int j = 1; j <= m; ++j)
                cin >> a[i][j];
        i64 l = 0, r = 1e18;
        while (l <= r)
        {
            auto mid = (l + r) / 2;
            if (check(mid))
                r = mid - 1;
            else
                l = mid + 1;
        }
        cout << calc(l) << '\n';
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
