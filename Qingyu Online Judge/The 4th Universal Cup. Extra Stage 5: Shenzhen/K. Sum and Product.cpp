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
struct Main
{
    i64 n, m;
    vector<pair<i64, int>> p;
    i64 answer;
    auto dfs(int u, i64 d, i64 phi, i64 r)
    {
        if (u == (int)p.size())
        {
            (answer += (d % mod) * (phi % mod) % mod * ((m / r + 1) % mod)) %= mod;
            return;
        }
        i64 all = 1;
        for (int i = 1; i <= p[u].second; ++i)
            all *= p[u].first;
        i64 t = 1, s = 1;
        for (int i = 0; i <= p[u].second; ++i, t *= p[u].first)
        {
            if (i & 1)
                s *= p[u].first;
            dfs(u + 1, d * t, phi * ((all / t) == 1 ? 1 : (all / t) / p[u].first * (p[u].first - 1)), r * s);
        }
    }
    Main() : answer(0)
    {
        cin >> n >> m;
        {
            i64 x = n;
            for (int i = 2; (i64)i * i <= x; ++i)
                if (x % i == 0)
                {
                    p.emplace_back(i, 0);
                    while (x % i == 0)
                    {
                        ++p.back().second;
                        x /= i;
                    }
                }
            if (x > 1)
                p.emplace_back(x, 1);
        }
        dfs(0, 1, 1, 1);
        cout << answer << '\n';
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

