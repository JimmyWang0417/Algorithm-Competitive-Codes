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
    string s;
    cin >> s;
    int n = s.size(), last = -1, last2;
    bool ok = 1;
    if (s[0] != '>')
        ok = 0;
    for (int i = n - 1; i >= 0; i--)
    {
        if (s[i] == '-')
        {
            last = i;
            break;
        }
    }
    if (!ok || last == -1 || n - last <= 3)
    {
        cout << "No\n";
        return;
    }
    for (int i = last - 1; i >= 0; i--)
    {
        if (s[i] == '>')
        {
            last2 = i;
            break;
        }
    }
    int cnt = 0;
    stringstream ans;
    for (int i = 0; i < last; i++)
    {
        if (s[i] == '>')
        {
            ++cnt;
            ans << (i + 1) << ' ' << (n - i) << "\n";
        }
    }
    for (int i = n - 2; i >= last + 3; i--)
    {
        ++cnt;
        ans << (last2 + 1) << ' ' << (i - last2 + 1) << "\n";
    }
    cout << "Yes " << cnt << "\n"
         << ans.str();
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