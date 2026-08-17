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
constexpr int mod = 1e9 + 7;
struct Main
{
    int n, m;
    vector<bool> root;
    vector<int> p, q;
    vector<vector<bool>> ban;
    vector<vector<i64>> f, g;
    Main()
    {
        cin >> n >> m;
        root.assign(n + 5, true);
        ban.assign(n + 5, vector<bool>(n + 5));
        p.resize(n + 5), q.resize(n + 5);
        for (int i = 1; i <= n; ++i)
        {
            int x;
            cin >> x;
            p[x] = i;
        }
        for (int i = 1; i < m; ++i)
        {
            for (int j = 1; j <= n; ++j)
            {
                int x;
                cin >> x;
                q[p[x]] = j;
            }
            for (int j = 1; j <= n; ++j)
            {
                int minn = INT_MAX, maxx = INT_MIN;
                for (int k = j; k <= n; ++k)
                {
                    minn = min(minn, q[k]);
                    maxx = max(maxx, q[k]);
                    ban[j][k] = ban[j][k] | (maxx - minn != k - j || q[j] != minn);
                }
            }
        }
        f.assign(n + 5, vector<i64>(n + 5));
        g.assign(n + 5, vector<i64>(n + 5));
        for (int i = 0; i <= n; ++i)
            g[i + 1][i] = 1;
        for (int len = 1; len <= n; ++len)
            for (int i = 1, j; (j = i + len - 1) <= n; ++i)
            {
                if (!ban[i][j])
                    f[i][j] = g[i + 1][j];
                for (int k = i; k <= j; ++k)
                    (g[i][j] += g[i][k - 1] * f[k][j]) %= mod;
            }
        cout << f[1][n] << '\n';
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

