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
    int n;
    string s;
    struct matrix : array<array<bool, 2>, 2>
    {
        auto friend operator*(const matrix &lhs, const matrix &rhs)
        {
            matrix res{};
            for (int i = 0; i < 2; ++i)
                for (int k = 0; k < 2; ++k)
                    for (int j = 0; j < 2; ++j)
                        res[i][j] |= lhs[i][k] & rhs[k][j];
            return res;
        }
    };
    vector<int> a;
    vector<matrix> b;
    vector<vector<int>> G;
    vector<matrix> tree;
#define lc (rt << 1)
#define rc (rt << 1 | 1)
    auto pushup(int rt)
    {
        tree[rt] = tree[lc] * tree[rc];
    }
    auto build(int rt, int l, int r)
    {
        if (l == r)
        {
            tree[rt] = b[l];
            return;
        }
        int mid = (l + r) >> 1;
        build(lc, l, mid);
        build(rc, mid + 1, r);
        pushup(rt);
    }
    auto update(int rt, int l, int r, int pos)
    {
        if (l == r)
        {
            tree[rt] = b[l];
            return;
        }
        int mid = (l + r) >> 1;
        if (pos <= mid)
            update(lc, l, mid, pos);
        else
            update(rc, mid + 1, r, pos);
        pushup(rt);
    }
    auto calc(int p, int k)
    {
        matrix res;
        res[0][1] = 1;
        res[0][0] = (p - 1 >= 0 && (s[p] == 'R' ? k - a[p] : a[p]) == (s[p - 1] == 'R' ? k - a[p - 1] : a[p - 1]));
        res[1][0] = (p - 2 >= 0 && (s[p] == 'R' ? k - a[p] : a[p]) == (s[p - 2] == 'R' ? k - a[p - 2] : a[p - 2]) + 1);
        return res;
    }
    Main()
    {
        cin >> n >> s;
        s.insert(s.begin(), 'L');
        s.push_back('R');
        a.resize(n + 5);
        for (int i = 1; i <= n; ++i)
            cin >> a[i];
        G.resize(n + 5);
        for (int i = 1; i <= n + 1; ++i)
        {
            if (i - 1 >= 0 && s[i] == 'R' && s[i - 1] == 'L')
            {
                if (a[i - 1] + a[i] <= n)
                    G[a[i - 1] + a[i]].emplace_back(i);
                if (a[i - 1] + a[i] + 1 <= n)
                    G[a[i - 1] + a[i] + 1].emplace_back(i);
            }
            if (i - 1 >= 0 && s[i] == 'L' && s[i - 1] == 'R')
            {
                // cout << i << ' ' << a[i - 1] + a[i] << '\n';
                if (a[i - 1] + a[i] <= n)
                    G[a[i - 1] + a[i]].emplace_back(i);
                if (a[i - 1] + a[i] + 1 <= n)
                    G[a[i - 1] + a[i] + 1].emplace_back(i);
            }
            if (i - 2 >= 0 && s[i] == 'R' && s[i - 2] == 'L')
            {
                if (a[i - 2] + 1 + a[i] <= n)
                    G[a[i - 2] + a[i] + 1].emplace_back(i);
                if (a[i - 2] + 1 + a[i] + 1 <= n)
                    G[a[i - 2] + 1 + a[i] + 1].emplace_back(i);
            }
            if (i - 2 >= 0 && s[i] == 'L' && s[i - 2] == 'R')
            {
                if (0 <= a[i - 2] + a[i] - 1 && a[i - 2] + a[i] - 1 <= n)
                    G[a[i - 2] + a[i] - 1].emplace_back(i);
                if (a[i - 2] + a[i] <= n)
                    G[a[i - 2] + a[i]].emplace_back(i);
            }
        }
        tree.resize(4 * (n + 1));
        b.resize(n + 5);
        for (int i = 1; i <= n + 1; ++i)
            b[i] = calc(i, 0);
        build(1, 1, n + 1);
        for (int k = 0; k <= n; ++k)
        {
            for (auto p : G[k])
            {
                b[p] = calc(p, k);
                update(1, 1, n + 1, p);
            }
            if (tree[1][0][0])
            {
                vector<int> f(n + 5), g(n + 5);
                f[0] = true;
                for (int i = 1; i <= n + 1; ++i)
                {
                    if (i - 1 >= 0 && (s[i] == 'R' ? k - a[i] : a[i]) == (s[i - 1] == 'R' ? k - a[i - 1] : a[i - 1]) && f[i - 1])
                    {
                        f[i] = true;
                        g[i] = i - 1;
                    }
                    else if (i - 2 >= 0 && (s[i] == 'R' ? k - a[i] : a[i]) == (s[i - 2] == 'R' ? k - a[i - 2] : a[i - 2]) + 1 && f[i - 2])
                    {
                        f[i] = true;
                        g[i] = i - 2;
                    }
                }
                vector<int> c(n + 5, 1);
                for (int i = n + 1; i; i = g[i])
                    c[i] = 0;
                for (int i = 1; i <= n; ++i)
                    cout << c[i];
                cout << '\n';
                return;
            }
        }
        cout << -1 << '\n';
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        Main();
    return 0;
}