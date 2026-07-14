#include <bits/stdc++.h>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef __float80 f80;
typedef __float128 f128;
struct Main
{
    int n;
    unordered_map<int, vector<int>> mp;
    Main()
    {
        cin >> n;
        for (int i = 1; i <= n; ++i)
        {
            int x;
            cin >> x;
            mp[x].push_back(i);
        }
        i64 res = LONG_LONG_MAX;
        for (const auto &[a, g] : mp)
        {
            int c = 0;
            {
                int las = 0;
                for (int i : g)
                {
                    if (i > las + 1)
                        ++c;
                    las = i;
                }
                if (n > las)
                    ++c;
            }
            res = min(res, (i64)a * c);
        }
        cout << res << '\n';
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