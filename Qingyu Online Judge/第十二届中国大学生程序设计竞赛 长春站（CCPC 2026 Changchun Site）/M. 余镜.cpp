#include <bits/stdc++.h>
using namespace std;

// #define LOCAL
#ifdef LOCAL
#define dbg(...) fprintf(stderr, ##__VA_ARGS__)
#else
#define dbg(...) 42
#endif

using LL = long long;

struct Main
{
    int n, M;
    vector<int> a;
    vector<int> ds;
    LL ans = 0;
    void main()
    {
        read();
        init();
        work();
        cout << ans << "\n";
    }
    void read()
    {
        cin >> n >> M;
        a.assign(n, 0);
        for (auto &x : a)
            cin >> x;
    }
    void init()
    {
        ds.assign(M + 1, 0);
        for (int x = 2; x <= M; ++x)
        {
            for (int y = 0; y <= M; y += x)
                ++ds[y];
        }
    }
    inline void fuck(int &l, int &r, int &g)
    {
        g = gcd(g, abs(a[l] - a[r]));
        ans += ds[g];
        dbg("l=%d r=%d g=%d add=%d\n", l, r, g, ds[g]);
        --l, ++r;
    }
    void work()
    {
        for (int i = 0; i < n; ++i)
        {
            int l = i - 1, r = i + 1, g = 0;
            while (l >= 0 && r < n)
                fuck(l, r, g);
        }
        for (int i = 1; i < n; ++i)
        {
            int l = i - 1, r = i, g = 0;
            while (l >= 0 && r < n)
                fuck(l, r, g);
        }
    }
};
signed main()
{
#ifndef LOCAL
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
#endif
    Main{}.main();
    return 0;
}
