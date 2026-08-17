#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef __float80 f80;
typedef __float128 f128;
constexpr int mod = 998244353;
template <typename T = int>
constexpr auto quickpow(i64 a, T b = mod - 2)
{
    i64 res = 1;
    while (b)
    {
        if (b & 1)
            (res *= a) %= mod;
        (a *= a) %= mod;
        b >>= 1;
    }
    return res;
}
constexpr int N = 2e6 + 5;
array<array<int, 23>, N> fa;
array<array<i64, 23>, N> f, g;
struct Main
{
    int n, q;
    struct node
    {
        int l, r;
        i64 w;
        bool d;
        int lc, rc;
    };
    vector<node> a;
    vector<int> dep;
    auto dfs(int u, int _fa) -> void
    {
        dep[u] = dep[fa[u][0] = _fa] + 1;
        for (int i = 0; i < 20; ++i)
        {
            fa[u][i + 1] = fa[fa[u][i]][i];
            f[u][i + 1] = f[u][i] + f[fa[u][i]][i];
            g[u][i + 1] = g[u][i] + g[fa[u][i]][i];
        }
        if (a[u].lc)
        {
            f[a[u].lc][0] = a[a[u].rc].w;
            dfs(a[u].lc, u);
        }
        if (a[u].rc)
        {
            g[a[u].rc][0] = a[a[u].lc].w;
            dfs(a[u].rc, u);
        }
    }
    auto LCA(int u, int v)
    {
        if (dep[u] < dep[v])
            swap(u, v);
        for (int i = 20; i >= 0; --i)
            if (dep[fa[u][i]] >= dep[v])
                u = fa[u][i];
        if (u == v)
            return u;
        for (int i = 20; i >= 0; --i)
            if (fa[u][i] != fa[v][i])
            {
                u = fa[u][i];
                v = fa[v][i];
            }
        return fa[u][0];
    }
    auto calc(int l, int r) -> pair<i64, i64>
    {
        --l, ++r;
        int u = l + 1, v = r + 1;
        int w = LCA(u, v);
        int uw = a[w].lc, vw = a[w].rc;
        i64 rL = 0, rR = 0;
        for (int i = 20; i >= 0; --i)
            if (dep[fa[u][i]] >= dep[uw])
            {
                rL += f[u][i];
                u = fa[u][i];
            }
        for (int i = 20; i >= 0; --i)
            if (dep[fa[v][i]] >= dep[vw])
            {
                rR += g[v][i];
                v = fa[v][i];
            }
        return {rL, rR};
    }
    Main()
    {
        cin >> n;
        a.resize(n + 3);
        {
            a[1].l = a[1].r = 0;
            a[1].w = LLONG_MAX / 4;
            a[1].d = true;
        }
        for (int i = 1; i <= n; ++i)
        {
            int w;
            char c;
            cin >> w >> c;
            a[i + 1].l = a[i + 1].r = i;
            a[i + 1].w = w;
            a[i + 1].d = (c == 'R');
        }
        {
            a[n + 2].l = a[n + 2].r = n + 1;
            a[n + 2].w = LLONG_MAX / 8;
            a[n + 2].d = false;
        }
        stack<int> st;
        for (int i = 1; i <= n + 2; ++i)
        {
            int v = i;
            while (!st.empty() && !a[v].d)
            {
                int u = st.top();
                st.pop();
                a.emplace_back();
                int w = (int)a.size() - 1;
                a[w].l = a[u].l, a[w].r = a[v].r;
                a[w].w = a[u].w + a[v].w;
                a[w].d = (a[u].w >= a[v].w);
                a[w].lc = u, a[w].rc = v;
                v = w;
            }
            if (a[v].d)
                st.push(v);
        }
        // for (int i = 1; i < (int)a.size(); ++i)
        //     cout << i << ": " << a[i].l << ' ' << a[i].r << ' ' << a[i].w << ' ' << a[i].lc << ' ' << a[i].rc << '\n';
        int root = st.top();
        dep.resize(a.size());
        // f.resize(a.size()), g.resize(a.size());
        dfs(root, 0);
        cin >> q;
        while (q--)
        {
            int l, r;
            cin >> l >> r;
            auto [L, R] = calc(l, r);
            cout << L << ' ' << R << '\n';
        }
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        Main();
    return 0;
}

