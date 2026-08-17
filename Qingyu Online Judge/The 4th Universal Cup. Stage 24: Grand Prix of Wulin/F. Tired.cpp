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
    int n, r;
    vector<int> a, c;
    Main()
    {
        cin >> n >> r;
        a.resize(n + 5), c.resize(n + 5);
        for (int i = 1; i <= n; ++i)
        {
            cin >> a[i];
            (a[i] += a[i - 1]) %= r;
        }
        for (int i = 1; i <= n; ++i)
            cin >> c[i];
        map<int, int> se;
        vector<i64> dp(n + 5);
        deque<int> q;
        q.emplace_back(n + 1);
        for (int i = n, j = n; i >= 1; --i)
        {
            se[a[i]]++;
            while ((int)se.size() == r)
            {
                if (!--se[a[j]])
                    se.erase(a[j]);
                --j;
            }
            while (!q.empty() && q.front() > j + 1)
                q.pop_front();
            dp[i] = dp[q.front()] + c[i];
            while (!q.empty() && dp[q.back()] > dp[i])
                q.pop_back();
            q.emplace_back(i);
        }
        i64 res = LLONG_MAX;
        for (int i = 1; i <= n + 1; ++i)
        {
            res = min(res, dp[i]);
            if (!a[i])
                break;
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
