#include <bits/stdc++.h>
using namespace std;

// #define ONLINE
#ifndef ONLINE
char DEBUG_BUFFER[1000];
#define debug(...)                                                        \
    {                                                                     \
        sprintf(DEBUG_BUFFER, ##__VA_ARGS__);                             \
        cerr << "\033[1;36m" << DEBUG_BUFFER << "\033[0;2m" << "\033[0m"; \
    }
#else
#define debug(...) ;
#endif

using LL = long long;
using PII = pair<int, int>;

#define all(x) (x).begin(), (x).end()
#define allr(x) (x).rbegin(), (x).rend()

#define FAST_IO                      \
    {                                \
        ios::sync_with_stdio(false); \
        cin.tie(nullptr);            \
    }
inline int read()
{
    static int x;
    cin >> x;
    return x;
}
inline LL readLL()
{
    static LL x;
    cin >> x;
    return x;
}
mt19937_64 rng(chrono::system_clock::now().time_since_epoch().count());

int main()
{
    FAST_IO;
    int n = read(), m = read();
    vector<LL> w(n + 1), sum(n + 1), s(m + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> w[i];
        sum[i] = sum[i - 1] + w[i];
    }
    auto get = [&](int l, int r) -> LL
    {
        return sum[r] - sum[l - 1];
    };
    for (int i = 1; i <= m; i++)
        cin >> s[i];
    vector<int> dp(n + 1), new_dp; //[i,dp[i]]
    iota(all(dp), 0);
    for (int k = 1; k <= m; k++)
    {
        s[k];
        new_dp = dp;
        for (int i = 1; i <= n; i++)
        {
            int L = i, R = dp[i];

            // expand left
            int l = 1, r = L - 1, mid, opt = -1;
            while (l <= r)
            {
                mid = l + r >> 1;
                if (get(mid, i - 1) <= s[k])
                {
                    opt = mid;
                    r = mid - 1;
                }
                else
                    l = mid + 1;
            }
            if (opt != -1)
            {
                new_dp[opt] = max(new_dp[opt], R);
            }

            // expand right
            l = R + 1, r = n, mid, opt = -1;
            while (l <= r)
            {
                mid = l + r >> 1;
                if (get(R + 1, mid) <= s[k])
                {
                    opt = mid;
                    l = mid + 1;
                }
                else
                    r = mid - 1;
            }
            if (opt != -1)
            {
                new_dp[L] = max(new_dp[L], opt);
            }
        }
        dp = new_dp;
    }
    cout << (dp[1] == n ? "Yes" : "No");
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */