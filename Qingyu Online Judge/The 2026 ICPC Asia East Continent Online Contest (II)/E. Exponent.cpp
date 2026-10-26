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
vector<int> primes;
struct Main
{
    auto get(int x)
    {
        vector<pair<int, int>> p;
        for (auto i : primes)
        {
            if ((i64)i * i > x)
                break;
            if (x % i == 0)
            {
                p.emplace_back(i, 0);
                while (x % i == 0)
                {
                    x /= i;
                    p.back().second++;
                }
            }
        }
        if (x > 1)
            p.emplace_back(x, 1);
        return p;
    }
    int n;
    vector<vector<pair<int, int>>> q;
    auto solve(int pr, int e, int pe)
    {
        q.emplace_back();
        auto phi = pe / pr * (pr - 1);
        for (int i = 1; (i64)i * i <= phi; ++i)
            if (phi % i == 0)
            {
                if (pr == 2 && e >= 3)
                    q.back().emplace_back(i, i == 1 ? 1 : (i == 2 ? 4 : (i == phi ? 0 : i * 2)));
                else
                    q.back().emplace_back(i, i);
                if (i * i < phi)
                {
                    if (pr == 2 && e >= 3)
                        q.back().emplace_back(phi / i, phi / i == 1 ? 1 : (phi / i == 2 ? 4 : (phi / i == phi ? 0 : phi / i * 2)));
                    else
                        q.back().emplace_back(phi / i, phi / i);
                }
            }
    }
    map<int, int> mp;
    vector<int> pm;
    vector<int> F, G;
    vector<unordered_map<int, int>> vis;
    static auto lcm(int x, int y)
    {
        return x / __gcd(x, y) * y;
    }
    auto dfs(int u, int A, int B)
    {
        if (u == (int)q.size())
        {
            auto [it, ok] = mp.emplace(A, (int)pm.size());
            if (ok)
            {
                pm.emplace_back(A);
                F.emplace_back();
            }
            F[it->second] = max(F[it->second], B);
            return;
        }
        for (auto [x, y] : q[u])
            if (y)
                dfs(u + 1, lcm(A, x), B * y);
    }
    Main()
    {
        cin >> n;
        auto p = get(n);
        for (auto [x, y] : p)
        {
            int pe = 1;
            for (int i = 1; i <= y; ++i)
                pe *= x;
            solve(x, y, pe);
        }
        vis.resize(q.size());
        dfs(0, 1, 1);
        G = F;
        for (auto [pr, _] : get(mp.rbegin()->first))
            for (auto it = mp.rbegin(); it != mp.rend(); ++it)
            {
                auto [x, y] = *it;
                if (x % pr == 0)
                    G[y] -= G[mp.find(x / pr)->second];
            }
        i64 ans = 0;
        for (int i = 0; i < (int)pm.size(); ++i)
            ans += (i64)pm[i] * G[i];
        cout << ans << '\n';
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    vector<bool> vis(31623);
    for (int i = 2; i < (int)vis.size(); ++i)
    {
        if (vis[i])
            continue;
        primes.emplace_back(i);
        for (int j = i * i; j < (int)vis.size(); j += i)
            vis[j] = true;
    }
    int T = 1;
    cin >> T;
    while (T--)
        Main();
    return 0;
}
