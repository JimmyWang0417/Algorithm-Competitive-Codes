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
constexpr int mod = 1e9 + 7;
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
struct Main
{
    int n, m, tim;
    vector<vector<int>> G;
    vector<int> p, q, vis, id;
    auto solve(const vector<int> &arr)
    {
        vector<int> a, b;
        for (int i = 0; i < (int)arr.size() / 2; ++i)
            a.emplace_back(arr[i]);
        for (int i = (int)arr.size() / 2; i < (int)arr.size(); ++i)
            b.emplace_back(arr[i]);

        ++tim;
        for (int i = 0; i < (int)arr.size(); ++i)
            vis[arr[i]] = tim, id[arr[i]] = i;

        vector<int> X(a.size()), Y(a.size()), Z(b.size());
        for (int i = 0; i < (int)a.size(); ++i)
        {
            int u = a[i];
            X[i] |= 1 << i;
            for (auto v : G[u])
                if (vis[v] == tim)
                    if (id[v] < (int)a.size())
                        X[i] |= 1 << id[v];
                    else
                        Y[i] |= 1 << (id[v] - a.size());
        }
        for (int i = 0; i < (int)b.size(); ++i)
        {
            int u = b[i];
            Z[i] |= 1 << i;
            for (auto v : G[u])
                if (vis[v] == tim && id[v] >= (int)a.size())
                    Z[i] |= 1 << (id[v] - a.size());
        }

        int A = 1 << a.size(), B = 1 << b.size();
        vector<int> xx(A), yy(A), zz(B), dp(B);
        xx[0] = A - 1, yy[0] = B - 1, zz[0] = B - 1;
        dp[B - 1] = 1;
        for (int S = 1; S < A; ++S)
        {
            int k = S & -S, i = __lg(k), T = S ^ k;
            xx[S] = xx[T] & X[i];
            yy[S] = yy[T] & Y[i];
            if ((S & xx[S]) == S)
                (++dp[yy[S]]) %= mod;
        }
        for (int i = 0; i < (int)b.size(); ++i)
            for (int S = 0; S < B; ++S)
                if (!(S >> i & 1))
                    (dp[S] += dp[S | (1 << i)]) %= mod;
        int res = dp[0];
        for (int S = 1; S < B; ++S)
        {
            int k = S & -S, i = __lg(k), T = S ^ k;
            zz[S] = zz[T] & Z[i];
            if ((S & zz[S]) == S)
                (res += dp[S]) %= mod;
        }
        return res;
    }
    Main()
    {
        cin >> n >> m;
        G.resize(n);
        p.resize(n), q.resize(n), vis.resize(n), id.resize(n);
        iota(p.begin(), p.end(), 0);
        for (int i = 0; i < m; ++i)
        {
            int u, v;
            cin >> u >> v;
            --u, --v;
            G[u].emplace_back(v);
            G[v].emplace_back(u);
        }
        ranges::sort(p, {}, [&](auto x)
                     { return G[x].size(); });
        for (int i = 0; i < n; ++i)
            q[p[i]] = i;
        int ans = 0;
        for (auto u : p)
        {
            vector<int> a;
            for (auto v : G[u])
                if (q[u] < q[v])
                    a.emplace_back(v);
            (ans += solve(a)) %= mod;
        }
        cout << ans << '\n';
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