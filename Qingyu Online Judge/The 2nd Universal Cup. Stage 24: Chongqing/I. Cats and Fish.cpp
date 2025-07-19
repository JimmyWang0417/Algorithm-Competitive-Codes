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
    int m = read(), n = read(), X = read();
    //[tim,prio]
    auto cmp = [&](const PII &A, const PII &B) -> bool
    {
        if (A.first == B.first)
            return A.second < B.second;
        return A.first > B.first;
    };
    priority_queue<PII, vector<PII>, greater<>> q;
    for (int i = 0, x; i < n; i++)
    {
        cin >> x;
        q.push({0, x});
    }
    int nw = 0, tmp = 0;
    while (q.size())
    {
        auto [t, p] = q.top();
        q.pop();
        //		debug("top={%d,%d}\n",t,p);
        if (t > X)
            break;
        if (t)
            nw--;
        if (m > 0)
        {
            q.push({t + p, p});
            --m;
            if (t != X)
                nw++;
            else
                tmp++;
        }
    }
    cout << (m + tmp) << ' ' << nw;
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */