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

void solve()
{
    int n = read(), m = read(), last = -1;
    vector<int> a(n);
    for (auto &x : a)
        cin >> x;
    vector<tuple<char, int, int>> qry(m);
    for (int i = 0; i < m; i++)
    {
        auto &[c, l, r] = qry[i];
        cin >> c;
        if (c == 'E')
        {
            cin >> l >> r;
        }
        else
        {
            l = r = -1;
            last = i;
        }
    }
    vector<int> flag(n + 1); // 1:left
    for (int i = 0; i < n / 2; i++)
    {
        flag[a[i]] = 1;
    }
    for (int i = 0; i < last; i++)
    {
        auto [c, l, r] = qry[i];
        if (c == 'E')
        {
            if (flag[l] != flag[r])
            {
                flag[l] ^= 1;
                flag[r] ^= 1;
            }
        }
    }
    if (last != -1)
    {
        vector<int> b;
        for (int i = n; i > 0; i--)
        {
            if (flag[i])
                b.push_back(i);
        }
        for (int i = 1; i <= n; i++)
        {
            if (!flag[i])
                b.push_back(i);
        }
        assert(b.size() == n);
        swap(a, b);
    }
    vector<int> pos(n + 1);
    for (int i = 0; i < n; i++)
    {
        pos[a[i]] = i;
    }
    for (int i = last + 1; i < m; i++)
    {
        auto [c, l, r] = qry[i];
        assert(c == 'E');
        swap(a[pos[l]], a[pos[r]]);
        swap(pos[l], pos[r]);
    }
    for (auto x : a)
        cout << x << ' ';
    cout << "\n";
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