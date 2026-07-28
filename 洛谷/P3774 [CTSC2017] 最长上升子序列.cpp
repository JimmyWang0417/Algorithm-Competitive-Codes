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
struct Main
{
    int n, m, block;
    vector<int> a;
    vector<tuple<int, int, int>> b;
    vector<vector<int>> row, col;
    vector<int> A, B;
    struct fenwick
    {
        constexpr static auto lowbit = [](int x)
        { return x & (-x); };
        vector<int> c;
        fenwick() = default;
        fenwick(int n) : c(n + 1) {}
        auto update(int pos, int val)
        {
            for (int i = pos; i < (int)c.size(); i += lowbit(i))
                c[i] += val;
        }
        auto query(int pos)
        {
            int res = 0;
            for (int i = pos; i; i -= lowbit(i))
                res += c[i];
            return res;
        }
    };
    fenwick tree;
    auto insertR(int x)
    {
        for (auto &i : row)
        {
            auto it = ranges::lower_bound(i, x);
            if (it == i.end())
            {
                i.push_back(x);
                if ((int)i.size() > block)
                    tree.update((int)i.size(), 1);
                return;
            }
            swap(*it, x);
        }
        if ((int)row.size() <= block)
            row.push_back({x});
    }
    auto insertC(int x)
    {
        for (int i = 0; i < (int)col.size(); ++i)
        {
            auto it = ranges::upper_bound(col[i], x, greater<int>());
            if (it == col[i].end())
            {
                col[i].push_back(x);
                tree.update(i + 1, 1);
                return;
            }
            swap(*it, x);
        }
        if ((int)col.size() < block)
        {
            col.push_back({x});
            tree.update((int)col.size(), 1);
        }
    }
    auto insert(int x)
    {
        insertR(x);
        insertC(x);
    }
    Main()
    {
        cin >> n >> m;
        block = (int)sqrt(n);
        a.resize(n), b.resize(m);
        tree = fenwick(n);
        for (int &i : a)
            cin >> i;
        for (int i = 0; i < m; ++i)
        {
            auto &[u, v, w] = b[i];
            cin >> u >> v;
            w = i;
        }
        vector<int> c(m);
        ranges::sort(b);
        for (int i = 0, j = 0; i < n; ++i)
        {
            insert(a[i]);
            while (j < m && get<0>(b[j]) <= i + 1)
            {
                auto [m, k, id] = b[j++];
                c[id] = tree.query(k);
            }
        }
        for (auto i : c)
            cout << i << '\n';
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
