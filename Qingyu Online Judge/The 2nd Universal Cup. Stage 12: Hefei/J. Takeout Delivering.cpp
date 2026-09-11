#include <bits/stdc++.h>
using namespace std;

// #define LOCAL
#ifdef LOCAL
#define dbg(...) fprintf(stderr, ##__VA_ARGS__)
#else
#define dbg(...) 42
#endif

#define all(x) (x).begin(), (x).end()
using LL = long long;
using ai3 = array<int, 3>;

struct Main
{
    int n, m;
    vector<ai3> edges;
    int ans = int(2e9);
    vector<int> fa, siz;
    void main()
    {
        cin >> n >> m;
        edges.assign(m, {});
        for (auto &[w, u, v] : edges)
        {
            cin >> u >> v >> w;
            if ((u == 1 && v == n) || (u == n && v == 1))
            {
                ans = w;
            }
        }
        sort(all(edges));
#ifdef LOCAL
        for (int i = 0; auto [w, u, v] : edges)
        {
            dbg("i=%d u=%d v=%d w=%d\n", i, u, v, w);
            ++i;
        }
#endif
        fa.assign(n + 1, 0);
        int l = 1, r = ans;
        while (l <= r)
        {
            const int mid = (1ll * l + r) >> 1;
            if (check(mid))
            {
                ans = mid;
                r = mid - 1;
            }
            else
                l = mid + 1;
        }
        cout << ans << "\n";
    }
    int get(int x)
    {
        while (fa[x] != x)
        {
            x = fa[x] = fa[fa[x]];
        }
        return x;
    }
    bool check(const int lim)
    {
        dbg("lim=%d\n", lim);
        iota(all(fa), 0);
        siz.assign(n + 1, 1);
        int i = 0, j = m - 1;
        for (; j >= 0 && edges[j][0] > lim; --j)
            ;
        for (; j >= i; --j)
        {
            while (i < j && edges[j][0] + edges[i][0] <= lim)
            {
                const auto [w, u, v] = edges[i];
                int fau = get(u);
                int fav = get(v);
                if (fau == fav)
                {
                    ++i;
                    continue;
                }
                if (siz[fav] > siz[fau])
                    swap(fau, fav);
                fa[fav] = fau;
                siz[fau] += siz[fav];
                ++i;
            }
            const int fa1 = get(1);
            const int fan = get(n);
            const auto [w, u, v] = edges[j];
            const int fau = get(u);
            const int fav = get(v);
            dbg("j=%d i=%d fa1=%d fan=%d fau=%d fav=%d\n", j, i, fa1, fan, fau, fav);
            if (fa1 == fan)
                return 1;
            if (fa1 == fau && fav == fan)
                return 1;
            if (fa1 == fav && fau == fan)
                return 1;
        }
        return 0;
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