#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef __float80 f80;
typedef __float128 f128;
constexpr int mod = 998244353;
constexpr auto quickpow(i64 a, int b)
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
constexpr int dx[] = {0, -1, 0, 1}, dy[] = {1, 0, -1, 0};
struct Main
{
    vector<vector<array<bool, 4>>> vis;
    vector<vector<array<int, 4>>> dp;
    vector<string> mp;
    int n, q;
    auto dfs(int x, int y, int d) -> int
    {
        if (x < 0 || x >= n || y < 0 || y >= n)
            return 0;
        if (vis[x][y][d])
            return dp[x][y][d];
        vis[x][y][d] = true;
        int dd = -1;
        int &res = dp[x][y][d] = INT_MAX / 2;
        for (int i = -1; i <= 2; i++)
        {
            int a = x + dx[(d + i + 4) % 4], b = y + dy[(d + i + 4) % 4];
            if (a < 0 || a >= n || b < 0 || b >= n || mp[a][b] == '.')
            {
                dd = (d + i + 4) % 4;
                break;
            }
        }
        if (dd == -1)
            return res;
        else
            return res = 1 + dfs(x + dx[dd], y + dy[dd], dd);
    }
    Main()
    {
        cin >> n >> q;
        vis.assign(n, vector<array<bool, 4>>(n));
        dp.assign(n, vector<array<int, 4>>(n));
        mp.resize(n);
        for (int i = 0; i < n; ++i)
            cin >> mp[i];
        auto calc = [](char c)
        {
            if (c == 'R')
                return 0;
            else if (c == 'U')
                return 1;
            else if (c == 'L')
                return 2;
            else
                return 3;
        };
        while (q--)
        {
            int r, c;
            char d;
            cin >> r >> c >> d;
            --r, --c;
            if (dfs(r, c, calc(d)) >= INT_MAX / 2)
                cout << "-1\n";
            else
                cout << dfs(r, c, calc(d)) << '\n';
        }
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        Main();
    return 0;
}
