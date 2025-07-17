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

int lim;
int dfs(int a, LL b, int nw)
{
    debug("a=%d b=%lld\n", a, b);
    int g = gcd(a, b);
    a /= g, b /= g;
    if (a == 1 || b == 1)
        return 2;
    if (nw >= lim)
        return 114514;
    return min(dfs(a - 1, b, nw + 1), dfs(a, b - 1, nw + 1)) + 1;
}
void solve()
{
    int a = read();
    LL b = readLL();
    lim = (__lg(a) + 1) * 2;
    cout << dfs(a, b, 0) << '\n';
}
int main()
{
    //	freopen("G.txt","r",stdin);
    FAST_IO;
    for (int T = read(); T--;)
        solve();
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */