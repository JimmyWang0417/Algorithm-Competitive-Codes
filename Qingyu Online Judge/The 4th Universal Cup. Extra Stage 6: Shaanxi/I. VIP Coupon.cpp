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
    a %= mod;
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
    int n, m;
    vector<int> a, b, c;
    vector<pair<int, int>> p;
    Main()
    {
        cin >> n >> m;
        a.resize(n), b.resize(m), c.resize(m);
        for (auto &i : a)
            cin >> i;
        for (auto &i : b)
            cin >> i;
        for (auto &i : c)
            cin >> i;
        for (int i = 0; i < n; ++i)
            p.emplace_back(a[i], INT_MAX);
        for (int i = 0; i < m; ++i)
            if (b[i] < c[i])
                p.emplace_back(b[i], c[i]);
        ranges::sort(p, [](auto x, auto y)
                     { return x.first < y.first; });
        priority_queue<int, vector<int>, greater<>> q;
        for (int i = 0; i < n; ++i)
            q.push(0);
        i64 res = 0;
        for (auto [l, r] : p)
        {
            int u = q.top();
            q.pop();
            if (r == INT_MAX)
            {
                res += max(u, l);
                if (q.empty())
                    break;
            }
            else
            {
                res -= max(r - max(l, u), 0);
                q.push(max(r, u));
            }
        }
        cout << res << '\n';
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
