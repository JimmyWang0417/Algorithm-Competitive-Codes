#include <bits/stdc++.h>
#include <cassert>
using namespace std;

// #define LOCAL
#ifdef LOCAL
#define dbg(...) fprintf(stderr, ##__VA_ARGS__)
#else
#define dbg(...) 42
#endif

template <class S>
inline bool updmn(S &x, const S y)
{
    if (y < x)
    {
        x = y;
        return 1;
    }
    return 0;
}

template <class S>
inline bool updmx(S &x, const S y)
{
    if (x < y)
    {
        x = y;
        return 1;
    }
    return 0;
}

struct Main
{
    int n;
    vector<int> a, b;
    void main()
    {
        cin >> n;
        a.assign(n, 0);
        b.assign(n, 0);
        for (int i = 0; i < n; ++i)
            cin >> a[i] >> b[i];
        int l = 1, r = int(1e9), ans = -1;
        while (l <= r)
        {
            const int mid = (l + r) >> 1;
            if (check(mid))
            {
                ans = mid;
                l = mid + 1;
            }
            else
                r = mid - 1;
        }
        assert(ans != -1);
        cout << ans << "\n";
    }
    bool check(const int x)
    {
        int base = 0;
        for (int i = 0; i < n; ++i)
        {
            if (a[i] < x)
                ++base;
        }
        int sub = 0, cur = 0, mx = 0;
        for (int i = 0; i < n; ++i)
        {
            const int aa = a[i] < x;
            const int bb = b[i] < x;
            cur += (bb - aa);
            updmn(sub, cur - mx);
            updmx(mx, cur);
        }
        dbg("mid = %2d base = %2d sub = %2d | %2d\n", x, base, sub, (base + sub) <= (n / 2));
        return (base + sub) <= (n / 2);
    }
};

signed main()
{
#ifndef LOCAL
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    Main{}.main();
    return 0;
}
