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
    constexpr static int LIMIT = 100;
    auto dfs(i64 n) -> i64
    {
        if (n == 0)
            return 0;
        static unordered_map<i64, i64> mp;
        if (mp.find(n) != mp.end())
            return mp[n];
        i64 res = n;
        for (int i = 2; i <= 100 && i <= n; ++i)
            res = min(res, dfs(n / i) + n % i + 2 + i);
        return mp[n] = res;
    }
    Main()
    {
        i64 n;
        cin >> n;
        cout << dfs(n) << '\n';
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
