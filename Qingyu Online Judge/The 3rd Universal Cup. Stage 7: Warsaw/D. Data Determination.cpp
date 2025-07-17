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

void solve()
{
    int n = read(), m = read(), x = read();
    vector<int> a(n);
    for (auto &x : a)
        cin >> x;
    sort(all(a));
    string ans = "NIE";
    if (m & 1)
    {
        if (binary_search(all(a), x))
        {
            int small = 0, big = 0, same = 0;
            for (auto u : a)
            {
                if (u < x)
                    small++;
                else if (u == x)
                    same++;
                else
                    big++;
            }
            same--;
            (m -= 1) /= 2;
            if (small < m)
            {
                same -= (m - small);
            }
            if (big < m)
            {
                same -= (m - big);
            }
            if (same >= 0)
            {
                ans = "TAK";
            }
        }
    }
    else
    {
        vector<int> b, c;
        int ori_same = 0, same = 0;
        for (auto u : a)
        {
            if (u < x)
                b.push_back(u);
            else if (u > x)
                c.push_back(u);
            else
                same++;
        }
        ori_same = same;
        reverse(all(c));
        (m /= 2) -= 1;
        debug("m=%d\n", m);
        if (same >= 2)
        {
            same -= 2;
            if (b.size() < m)
            {
                same -= (m - b.size());
            }
            if (c.size() < m)
            {
                same -= (m - c.size());
            }
            if (same >= 0)
            {
                ans = "TAK";
            }
        }
        while (b.size() && c.size())
        {
            debug("b|%d c|%d x|%d\n", b.back(), c.back(), x);
            if (b.back() + c.back() == x * 2)
            {
                if (b.size() > m && c.size() > m)
                {
                    ans = "TAK";
                }
                b.pop_back();
                c.pop_back();
            }
            else
            {
                if (x - b.back() < c.back() - x)
                    b.pop_back();
                else
                    c.pop_back();
            }
        }
    }
    cout << ans << "\n";
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