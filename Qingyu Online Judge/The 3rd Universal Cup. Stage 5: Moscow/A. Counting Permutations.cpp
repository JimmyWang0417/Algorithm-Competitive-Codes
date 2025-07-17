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

const int mod = 998244353;
#define N 100010
LL fac[N];

void solve()
{
    int n = read(), m1 = read(), m2 = read();
    vector<PII> a(n);
    map<PII, int> flag;
    for (auto &[x, y] : a)
    {
        int b = read();
        x = b % m1, y = b % m2;
        ++flag[{x, y}];
    }
    sort(all(a), [&](const PII &A, const PII &B) -> bool
         {
		if(A.first==B.first) return A.second>B.second;
		return A.first<B.first; });
    bool ok = 1;
    for (int i = 1; i < n; i++)
    {
        if (a[i].second <= a[i - 1].second)
            ;
        else
            ok = 0;
    }
    if (!ok)
    {
        cout << "0\n";
        return;
    }
    LL res = 1;
    for (auto [_, x] : flag)
    {
        (res *= fac[x]) %= mod;
    }
    cout << res << "\n";
}

#define __MULTI_TEST
int main()
{
    fac[0] = 1;
    for (int i = 1; i < N; i++)
    {
        fac[i] = fac[i - 1] * i % mod;
    }
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