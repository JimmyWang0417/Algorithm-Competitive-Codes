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

const int mod = 1e9 + 7;
void add(LL &x, const LL &y)
{
    (x += y) %= mod;
}

#define N 305
LL dp[N][N][3], nw[N][N][3];
LL sum[N][N];

int c2d(const char &c)
{
    if (c == 'a')
        return 0;
    else if (c == 'b')
        return 1;
    else
        return 2;
}

int main()
{
    FAST_IO;
    int n = read(), T = read();
    string s;
    cin >> s;
    {
        if (s[0] == '?')
        {
            dp[1][0][0] = 1;
            dp[0][1][1] = 1;
            dp[0][0][2] = 1;
        }
        else
        {
            dp[0][0][c2d(s[0])] = 1;
        }
    }
    int need = (s[0] == '?');
    for (int i = 2; i <= n; i++)
    {
        memset(nw, 0, sizeof(nw));
        if (s[i - 1] == '?')
            ++need;
        for (int x = 0; x <= need; x++)
        {
            for (int y = 0; x + y <= need; y++)
            {
                int z = need - x - y;
                if (s[i - 1] == '?')
                {
                    if (x)
                        add(nw[x][y][0], (dp[x - 1][y][1] + dp[x - 1][y][2]) % mod);
                    if (y)
                        add(nw[x][y][1], (dp[x][y - 1][0] + dp[x][y - 1][2]) % mod);
                    if (z)
                        add(nw[x][y][2], (dp[x][y][0] + dp[x][y][1]) % mod);
                }
                else
                {
                    add(nw[x][y][c2d(s[i - 1])],
                        (dp[x][y][0] + dp[x][y][1] + dp[x][y][2] - dp[x][y][c2d(s[i - 1])]) % mod);
                }
            }
        }
        memcpy(dp, nw, sizeof(dp));
#ifndef ONLINE
        debug("after i=%d\n", i);
        debug("\tneed=%d\n", need);
        for (int x = 0; x <= need; x++)
        {
            for (int y = 0; x + y <= need; y++)
            {
                int z = need - x - y;
                debug("\tdp{x=%d,y=%d,z=%d}={%lld,%lld,%lld}\n",
                      x, y, z, dp[x][y][0], dp[x][y][1], dp[x][y][2]);
            }
        }
#endif
    }
    for (int x = 0; x <= need; x++)
    {
        for (int y = 0; x + y <= need; y++)
        {
            add(sum[x][y], dp[x][y][0]);
            add(sum[x][y], dp[x][y][1]);
            add(sum[x][y], dp[x][y][2]);
        }
    }
    for (int x = 0; x < N; x++)
    {
        for (int y = 1; y < N; y++)
        {
            add(sum[x][y], sum[x][y - 1]);
        }
    }
    debug("need=%d\n", need);
    for (int a, b, c; T--;)
    {
        cin >> a >> b >> c;
        LL res = 0, opt;
        for (int x = 0; x <= a; x++)
        {
            int mn = max(0, need - x - c);
            int mx = min(b, need - x);
            if (mn > mx)
                continue;
            debug("x=%d mn_y=%d mx_y=%d\n", x, mn, mx);
            opt = sum[x][mx];
            if (mn)
            {
                (((opt -= sum[x][mn - 1]) %= mod) += mod) %= mod;
            }
            add(res, opt);
        }
        debug("res=%d\n", res);
        cout << res << "\n";
    }
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */