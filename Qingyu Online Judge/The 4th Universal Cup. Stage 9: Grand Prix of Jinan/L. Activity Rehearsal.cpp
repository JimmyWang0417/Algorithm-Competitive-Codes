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
template <typename T>
struct fenwick
{
    vector<i64> c;
    fenwick() = default;
    fenwick(int n) : c(n + 1) {}
    constexpr static auto lowbit = [](int x)
    {
        return x & (-x);
    };
    auto update(int pos, T val)
    {
        for (int i = pos; i < (int)c.size(); i += lowbit(i))
            c[i] += val;
    }
    auto query(int pos)
    {
        T res = 0;
        for (int i = pos; i; i -= lowbit(i))
            res += c[i];
        return res;
    }
    auto query(int l, int r)
    {
        return query(r) - query(l - 1);
    }
};
struct Main
{
    int n, m;
    vector<int> a, b, c, fa;
    Main()
    {
        cin >> n >> m;
        a.resize(n);
        for (int i = 0; i < n; ++i)
            cin >> a[i];
        b.reserve(2 * n), fa.resize(2 * n + 5);
        c.resize(n + 5);
        for (int i = 0; i < n; ++i)
            b.emplace_back(a[i]);
        for (int i = 0; i + 1 < (int)b.size(); i += 2)
        {
            fa[i] = fa[i + 1] = (int)b.size();
            b.emplace_back(min(b[i], b[i + 1]));
        }
        fa[b.size() - 1] = -1;
        fenwick<i64> tree(n - 1);
        {
            for (int i = 0; i < n; ++i)
            {
                c[i] = max(b[i * 2], b[i * 2 + 1]);
                tree.update(i + 1, c[i]);
            }
        }
        while (m--)
        {
            char C;
            int x, y;
            cin >> C >> x >> y;
            if (C == 'C')
            {
                auto update = [&](int u)
                {
                    while (fa[u] != -1)
                    {
                        auto now = max(b[u], b[u ^ 1]);
                        b[fa[u]] = min(b[u], b[u ^ 1]); 
                        tree.update(u / 2 + 1, now - c[u / 2]);
                        c[u / 2] = now;
                        u = fa[u];
                    }
                };
                --x, --y;
                swap(b[x], b[y]);
                update(x), update(y);
            }
            else
                cout << tree.query(x, y) << '\n';
            // for (int i = 0; i < n - 1; ++i)
            //     cout << c[i] << ' ';
            // cout << '\n';
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
