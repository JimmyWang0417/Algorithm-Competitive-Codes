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

map<PII, int> flag;
stringstream ans;
int cnt = 0;
void f(int a, int b, int c, int d, int e, int f)
{
    assert(a != b || c != d);
    assert(c == e);
    int x = flag[PII{a, b}];
    assert(x > 0);
    int y = flag[PII{c, d}];
    assert(y > 0);
    flag[{a, b}]--;
    flag[{c, d}]--;
    flag[{e, f}]++;
#ifndef ONLINE
    for (int x = 4; x >= -6; x--)
    {
        for (int y = -6; y <= 6; y++)
        {
            debug("%2d", flag[{x, y}]);
        }
        debug("\n");
    }
    debug("\n");
#endif
    ++cnt;
    ans << a << ' ' << b << ' ' << c << ' ' << d << ' ' << e << ' ' << f << "\n";
}
void func1(int x, int y)
{
    f(x + 2, y - 1, x + 1, y - 1, x + 1, y);
    f(x + 3, y - 1, x + 4, y - 1, x + 4, y);
    f(x, y, x + 1, y, x + 1, y + 1);
    f(x + 1, y, x + 2, y, x + 2, y + 1);
    f(x + 5, y, x + 4, y, x + 4, y + 1);
    f(x + 4, y, x + 3, y, x + 3, y + 1);
    f(x + 1, y + 1, x + 2, y + 1, x + 2, y + 2);
    f(x + 4, y + 1, x + 3, y + 1, x + 3, y + 2);
}
void solve()
{
    flag.clear();
    for (int x = -100; x <= 100; x++)
    {
        for (int y = -100; y <= 0; y++)
        {
            flag[{x, y}] = 1;
        }
    }
    cnt = 0;
    ans.str("");
    int n = read();
    if (n >= 5)
    {
        cout << -1 << "\n";
        return;
    }
    func1(-6, -3);
    f(-4, -1, -3, -1, -3, 0);
    f(-4, -1, -3, -1, -3, 0);
    func1(0, -3);
    f(3, -1, 2, -1, 2, 0);
    f(3, -1, 2, -1, 2, 0);

    f(-4, -2, -3, -2, -3, -1);
    f(-3, -1, -2, -1, -2, 0);

    f(-1, -2, -2, -2, -2, -1);
    f(-2, -1, -1, -1, -1, 0);

    f(0, -2, 1, -2, 1, -1);
    f(1, -1, 0, -1, 0, 0);

    f(3, -2, 2, -2, 2, -1);
    f(2, -1, 1, -1, 1, 0);

    f(3, 0, 2, 0, 2, 1);
    f(2, 0, 1, 0, 1, 1);
    f(2, 0, 1, 0, 1, 1);

    f(0, 0, -1, 0, -1, 1);
    f(-1, 0, 0, 0, 0, 1);

    f(-4, 0, -3, 0, -3, 1);
    f(-3, 0, -2, 0, -2, 1);
    f(-3, 0, -2, 0, -2, 1);

    f(-3, 1, -2, 1, -2, 2);
    f(-2, 1, -1, 1, -1, 2);
    f(2, 1, 1, 1, 1, 2);
    f(1, 1, 0, 1, 0, 2);

    f(-2, 2, -1, 2, -1, 3);
    f(1, 2, 0, 2, 0, 3);

    f(-1, 3, 0, 3, 0, 4);
    cout << cnt << "\n"
         << ans.str() << "\n";
}

#define __MULTI_TEST
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