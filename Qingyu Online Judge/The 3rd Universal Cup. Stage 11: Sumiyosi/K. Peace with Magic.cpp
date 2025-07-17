#include <bits/stdc++.h>
using namespace std;

#define ONLINE
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

#define N 110
#define M 200010
#define offset 100000
int a[N], sum[N];
vector<int> dp, nw;

void upd(int &x, const LL &y)
{
    if (x == -1 || y > x)
        x = y;
}

int main()
{
    FAST_IO;
    int n = read() - 1;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        sum[i] = sum[i - 1] + a[i];
    }
    dp.assign(M, -1);
    dp[offset] = offset;
    for (int i = 1; i <= n; i++)
    {
        debug("i=%d\n", i);
        nw.assign(M, -1);
        for (int j = 0; j < M; j++)
            if (dp[j] != -1)
            {
                upd(nw[j + a[i]], dp[j]);
                upd(nw[j - a[i]], min(dp[j], j - a[i]));
            }
        swap(dp, nw);
#ifndef ONLINE
        for (int j = offset - 6; j <= offset + 6; j++)
        {
            debug("\tdp[%d]=%d\n", j - offset, dp[j] - offset);
        }
#endif
    }
    LL ans = -1;
    for (int i = 0; i < M; i++)
        if (dp[i] != -1)
        {
            int res = (sum[n] + i - offset) / 2 + max(0, offset - dp[i]);
            if (ans == -1 || ans > res)
                ans = res;
        }
    cout << ans << "\n";
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */