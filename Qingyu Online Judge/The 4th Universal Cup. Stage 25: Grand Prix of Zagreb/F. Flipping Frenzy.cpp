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
    int n, m, k;
    vector<vector<bool>> vis;
    vector<vector<bool>> p;
    vector<vector<vector<tuple<int, int, int, int, int>>>> G;
    vector<tuple<int, int, int>> answer;
    auto dfs(int ux, int uy) -> void
    {
        vis[ux][uy] = true;
        for (auto [vx, vy, _, __, ___] : G[ux][uy])
        {
            if (vis[vx][vy])
                continue;
            dfs(vx, vy);
            if (p[vx][vy])
            {
                p[ux][uy] = p[ux][uy] ^ p[vx][vy];
                answer.emplace_back(_, __, ___);
            }
        }
    }
    Main()
    {
        cin >> n >> m >> k;
        p.resize(n + 5, vector<bool>(m + 5));
        vis.resize(n + 5, vector<bool>(m + 5));
        G.resize(n + 5, vector<vector<tuple<int, int, int, int, int>>>(m + 5));
        for (int i = 1; i <= n; ++i)
        {
            string s;
            cin >> s;
            for (int j = 1; j <= m; ++j)
                p[i][j] = (s[j - 1] - '1');
        }
        for (int i = n + 1; i >= 1; --i)
            for (int j = m + 1; j >= 1; --j)
                p[i][j] = p[i][j] ^ p[i - 1][j] ^ p[i][j - 1] ^ p[i - 1][j - 1];
        for (int _ = 1; _ <= k; ++_)
        {
            int a, b;
            cin >> a >> b;
            G[1][1].emplace_back(a + 1, b + 1, _, 1, 1);
            G[a + 1][b + 1].emplace_back(1, 1, _, 1, 1);
            for (int i = 2, j = 1; i + a - 1 <= n; ++i)
            {
                G[i][j + b].emplace_back(i + a, j + b, _, i, j);
                G[i + a][j + b].emplace_back(i, j + b, _, i, j);
            }
            for (int i = 1, j = 2; j + b - 1 <= m; ++j)
            {
                G[i + a][j].emplace_back(i + a, j + b, _, i, j);
                G[i + a][j + b].emplace_back(i + a, j, _, i, j);
            }
        }
        // for (int i = 1; i <= n + 1; ++i)
        //     for (int j = 1; j <= m + 1; ++j)
        //         for (auto [x, y, _, __, ___] : G[i][j])
        //             cout << "(" << i << ", " << j << ") (" << x << ", " << y << ")\n";
        for (int i = 1; i <= n + 1; ++i)
            for (int j = 1; j <= m + 1; ++j)
            {
                if (vis[i][j])
                    continue;
                dfs(i, j);
            }
        cout << answer.size() << '\n';
        for (auto [a, b, c] : answer)
            cout << a << ' ' << b << ' ' << c << '\n';
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

