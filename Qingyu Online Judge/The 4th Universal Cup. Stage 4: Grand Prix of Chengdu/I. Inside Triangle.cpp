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
namespace std
{
    template <typename T>
    auto operator<(const complex<T> &x, const complex<T> &y)
    {
        return make_pair(x.real(), x.imag()) < make_pair(y.real(), y.imag());
    }
}
typedef complex<i64> p2;
auto dot(p2 x, p2 y) { return (conj(x) * y).real(); }
auto cross(p2 x, p2 y) { return (conj(x) * y).imag(); }
struct fenwick
{
    fenwick() = default;
    fenwick(int n) : c1(n + 1), c2(n + 1) {}
    constexpr static auto lowbit = [](int x)
    {
        return x & (-x);
    };
    vector<int> c1;
    vector<i64> c2;
    auto update(int pos, int val)
    {
        for (int i = pos; i < (int)c1.size(); i += lowbit(i))
        {
            c1[i] += val;
            c2[i] += (i64)pos * val;
        }
    }
    auto query(int pos)
    {
        int res1 = 0;
        i64 res2 = 0;
        for (int i = pos; i; i -= lowbit(i))
        {
            res1 += c1[i];
            res2 += c2[i];
        }
        return (i64)res1 * (pos + 1) - res2;
    }
    auto update(int l, int r, int val)
    {
        update(l + 1, val);
        update(r + 2, -val);
    }
    auto query(int l, int r) -> i64
    {
        return query(r + 1) - query(l);
    }
};
struct Main
{
    int n, m;
    vector<p2> a, b;
    vector<int> L, R;
    Main()
    {
        cin >> n;
        a.resize(n);
        for (int i = 0; i < n; ++i)
        {
            i64 x, y;
            cin >> x >> y;
            a[i] = p2(x, y);
        }
        cin >> m;
        b.resize(m);
        for (int i = 0; i < m; ++i)
        {
            i64 x, y;
            cin >> x >> y;
            b[i] = p2(x, y);
        }
        L.resize(n), R.resize(n);
        for (int i = n - 1, j = n - 1, k = 0; i >= 0; --i)
        {
            if (i == 0)
            {
                while (cross(b[(k + 1) % m] - a[i], b[k] - a[i]) < 0)
                    k = (k + 1) % m;
            }
            while (cross(b[k] - a[i], b[(k + m - 1) % m] - a[i]) > 0)
                k = (k + m - 1) % m;
            while (cross(a[(j + n - 1) % n] - a[i], b[k] - a[i]) <= 0)
                j = (j + n - 1) % n;
            L[i] = j;
        }
        for (int i = 0, j = 0, k = 0; i < n; ++i)
        {
            if (i == 0)
            {
                while (cross(b[k] - a[i], b[(k + m - 1) % m] - a[i]) < 0)
                    k = (k + m - 1) % m;
            }
            while (cross(b[(k + 1) % m] - a[i], b[k] - a[i]) > 0)
                k = (k + 1) % m;
            while (cross(a[(j + 1) % n] - a[i], b[k] - a[i]) >= 0)
                j = (j + 1) % n;
            R[i] = j;
            if (j == i)
                j = (j + 1) % n;
        }
        fenwick tree(n);
        auto update = [&](int p, int v)
        {
            if (p == R[p])
                return;
            tree.update(p + 1, p > R[p] ? n - 1 : R[p], v);
        };
        i64 res = 0;
        for (int i = 0, j = 0; i < n; ++i)
        {
            update(i, -1);
            while (j < n && j <= R[i])
                update(j++, 1);
            if (L[i] > i)
                res += tree.query(L[i], n - 1);
        }
        cout << res << '\n';
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        Main();
    return 0;
}
