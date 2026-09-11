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
constexpr double eps = 1e-12;
struct Main
{
    int m;
    string s;
    string p;
    Main()
    {
        cin >> m >> s;
        if (m == 2)
        {
            i64 x = 0;
            for (auto c : s)
                x = x * m + (c == s.front());
            cout << x << '\n';
            return;
        }
        p = s;
        sort(p.begin(), p.end());
        p.erase(unique(p.begin(), p.end()), p.end());
        vector<i64> a;

        for (auto c : p)
        {
            i64 x = 0;
            for (auto d : s)
                x = x * m + (d == c);
            a.emplace_back(x);
        }
        i64 g = 0;
        {
            i64 y = 0;
            array<int, 26> vis;
            vis.fill(-1);
            int d = 0;
            for (auto c : s)
            {
                if (vis[c - 'a'] == -1)
                    vis[c - 'a'] = d++;
                y = y * m + vis[c - 'a'];
            }
            g = y;
        }
        sort(a.begin(), a.end());
        for (int i = 0; i + 1 < (int)a.size(); ++i)
            g = gcd(g, a[i + 1] - a[i]);
        if ((int)p.size() < m)
        {
            for (auto i : a)
                g = gcd(g, i);
        }
        cout << g << '\n';
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