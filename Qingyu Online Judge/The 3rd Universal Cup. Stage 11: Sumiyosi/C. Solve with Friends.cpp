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

#define N 200010
void solve()
{
    int n = read();
    vector<array<LL, 2>> a(n + 1);
    vector<LL> c(n + 1), d(n + 1);
    for (int i = 1; i <= n; i++)
        cin >> a[i][0];
    for (int i = 1; i <= n; i++)
        cin >> a[i][1];
    sort(a.begin() + 1, a.end(), [&](const auto &A, const auto &B) -> bool
         { return A[0] - A[1] < B[0] - B[1]; });
    for (int i = 1; i <= n; i++)
        cin >> c[i];
    for (int i = 1; i <= n; i++)
        cin >> d[i];
    vector<LL> sum_a(n + 1), sum_b(n + 1), sum_c(n + 1), sum_d(n + 1);
    for (int i = 1; i <= n; i++)
    {
        debug("\t%lld %lld\n", a[i][0], a[i][1]);
        sum_a[i] = sum_a[i - 1] + a[i][0];
    }
    for (int i = 1; i <= n; i++)
    {
        sum_b[i] = sum_b[i - 1] + a[i][1];
    }
    for (int i = 1; i <= n; i++)
    {
        sum_c[i] = sum_c[i - 1] + c[i];
    }
    for (int i = 1; i <= n; i++)
    {
        sum_d[i] = sum_d[i - 1] + d[i];
        debug("%lld %lld %lld %lld\n", sum_a[i], sum_b[i], sum_c[i], sum_d[i]);
    }
    LL ans = 1e18;
    for (int i = 0; i <= n; i++)
    {
        debug("i=%d|a=%lld c=%lld b=%lld d=%lld\n", i, sum_a[i], sum_c[i], sum_b[n] - sum_b[i], sum_d[n - i]);
        LL res = sum_a[i] + sum_c[i] + sum_b[n] - sum_b[i] + sum_d[n - i];
        ans = min(ans, res);
    }
    cout << ans << "\n";
}

// #define __MULTI_TEST
int main()
{
    FAST_IO;
#ifdef __MULTI_TEST
    for (int T = read(); T--;)
        solve();
#else
    solve();
#endif
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */