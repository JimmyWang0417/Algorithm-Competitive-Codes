#include <bits/stdc++.h>
using namespace std;

// #define LOCAL
#ifdef LOCAL
#define dbg(...) fprintf(stderr, ##__VA_ARGS__)
#else
#define dbg(...) 42
#endif

#define all(x) (x).begin(), (x).end()

struct Main
{
    int n, m;
    vector<int> a, b;
    vector<int> fa, ans;
    void main()
    {
        read();
        init();
        ans.assign(m, 0);
        for (int i = 0; i < m; ++i)
        {
            ans[i] = work(b[i]);
        }
        for (auto x : ans)
            cout << x << "\n";
    }
    void read()
    {
        cin >> n >> m;
        a.assign(n + 5, 0);
        for (int i = 1; i <= n; ++i)
            cin >> a[i];
        b.assign(m, 0);
        for (auto &x : b)
            cin >> x;
    }
    void init()
    {
        fa.assign(n + 5, 0);
        iota(all(fa), 0);
        for (int i = 1; i <= n; ++i)
        {
            if (a[i] == 1)
                fa[i] = i + 1;
        }
    }
    inline int get(int x)
    {
        while (fa[x] != x)
        {
            x = fa[x] = fa[fa[x]];
        }
        return x;
    }
    int work(int x)
    {
        dbg("start = %d\n", x);
        int res = 0;
        while (x <= n)
        {
            dbg("* now %d\n", x);
            if (a[x] == 1)
            {
                const int y = get(x);
                res += y - x;
                x = y;
            }
            else
            {
                const int y = x + a[x];
                ++res;
                if (--a[x] == 1)
                    fa[x] = x + 1;
                x = y;
            }
        }
        return res;
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
