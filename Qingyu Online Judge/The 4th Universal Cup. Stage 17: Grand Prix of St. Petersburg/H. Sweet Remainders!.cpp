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
constexpr int mod = 1e6 + 3;
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
    vector<int> a;
    auto build()
    {
        vector<pair<int, int>> p;
        multiset<pair<int, int>> se;
        for (int i = 0; i < n; ++i)
            se.emplace(a[i], i + 1);
        for (int i = 1; i < n; ++i)
        {
            int u = se.begin()->second;
            se.erase(se.begin());
            auto [d, v] = *se.rbegin();
            se.erase(prev(se.end()));
            p.emplace_back(u, v);
            se.emplace(d - 1, v);
        }
        return p;
    }
    Main()
    {
        cin >> n >> m;
        a.resize(n);
        for (auto &i : a)
            cin >> i;
        if (n == 1)
        {
            if (a.front() == -1 || a.front() == 0)
            {
                cout << "YES\n";
                return;
            }
            cout << "NO\n";
            return;
        }
        i64 sum = 0;
        int p = -1;
        for (int i = 0; i < n; ++i)
        {
            if (a[i] == 0)
                a[i] += m;
            if (a[i] == -1)
            {
                ++sum;
                p = i;
            }
            else
                sum += a[i];
        }
        if (sum > 2 * (n - 1))
        {
            cout << "NO\n";
            return;
        }
        if (sum % m != 2 * (n - 1) % m && p == -1)
        {
            cout << "NO\n";
            return;
        }
        if (p != -1)
        {
            a[p] = 1 + 2 * (n - 1) - (int)sum;
            for (int i = 0; i < n; ++i)
                if (i == p && a[i] == -1)
                    a[i] = 1;
        }
        else
            a.front() += 2 * (n - 1) - (int)sum;
        cout << "YES\n";
        for (auto [x, y] : build())
            cout << x << ' ' << y << '\n';
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