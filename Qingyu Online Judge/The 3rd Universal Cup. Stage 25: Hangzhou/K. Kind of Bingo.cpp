#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef __float80 f80;
typedef __float128 f128;
constexpr int mod = 998244353;
mt19937 rnd((random_device())());
struct Main
{
    Main()
    {
        int n, m, k;
        cin >> n >> m >> k;
        vector<int> p(n * m);
        for (int &i : p)
        {
            cin >> i;
            --i;
        }
        int l = m, r = n * m;
        auto check = [&](int t)
        {
            vector<bool> vis(n * m);
            for (int i = 0; i < t; ++i)
                vis[p[i]] = true;
            int res = INT_MAX;
            for (int i = 0; i < n; ++i)
            {
                int cnt = 0;
                for (int j = i * m; j < (i + 1) * m; ++j)
                    cnt += vis[j];
                res = min(res, m - cnt);
            }
            return res <= k;
        };
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            if (check(mid))
                r = mid - 1;
            else
                l = mid + 1;
        }
        cout << l << '\n';
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        Main();
    return 0;
}