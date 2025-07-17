#include <bits/stdc++.h>
using namespace std;

#define int long long
#define mod 998244353

int ksm(int x, int y)
{
    int base = x;
    int res = 1;
    while (y)
    {
        if (y & 1)
        {
            res = res * base % mod;
        }
        base = base * base % mod;
        y >>= 1;
    }
    return res;
}

void solve()
{
    int n, m;
    cin >> n >> m;
    vector<int> ni(n + 1);
    int oo = 1;
    for (int i = 1; i <= n; i++)
    {
        oo *= i;
        oo %= mod;
    }
    ni[n] = ksm(oo, mod - 2);
    for (int i = n - 1; i >= 1; i--)
    {
        ni[i] = ni[i + 1] * (i + 1) % mod;
    }
    vector<vector<int>> use(n + 1);
    for (int i = 1; i <= n; i++)
    {
        for (int j = 2; j * j <= i; j++)
        {
            if (i % j == 0)
            {
                use[i].push_back(j);
                if (j * j == i)
                {
                    continue;
                }
                use[i].push_back(i / j);
            }
        }
        use[i].push_back(1);
    }

    vector<vector<int>> dp(n + 1);
    for (int i = 1; i <= n; i++)
    {
        dp[i].resize(log2(i) + 2, -1);
    }
    auto dfs = [&](auto &&dfs, int x, int num) -> void
    {
        if (num == 1)
        {
            dp[x][num] = 1;
            return;
        }
        if (num > log2(x) + 1)
        {
            return;
        }
        if (dp[x][num] != -1)
        {
            return;
        }
        dp[x][num] = 0;
        for (auto &i : use[x])
        {
            if (num - 1 > log2(i) + 1)
            {
                continue;
            }
            dfs(dfs, i, num - 1);
            dp[x][num] += dp[i][num - 1];
            dp[x][num] %= mod;
        }
    };
    int tot = m * ni[m] % mod;
    for (int k = 0; k < m; k++)
    {
        tot = tot * (n - k) % mod;
    }
    for (int i = 1; i <= n; i++)
    {
        for (int j = 1; j <= log2(i) + 1; j++)
        {
            dfs(dfs, i, j);
            if (m < j)
            {
                continue;
            }
            if (n / i - 1 >= m - j && dp[i][j] > 0)
            {
                // cout<<i<<" "<<j<<" "<<dp[i][j]<<" ";
                int now = 1;
                if (n / i - 1 > m - j)
                {
                    for (int k = 0; k < m - j; k++)
                    {
                        now *= (n / i - 1 - k);
                        now %= mod;
                    }
                    now *= ni[m - j];
                    now %= mod;
                }
                if (m - j == 0)
                {
                    now = 1;
                }
                // cout<<now<<"\n";
                now *= dp[i][j];
                now %= mod;
                tot -= now;
                tot = (tot % mod + mod) % mod;
            }
        }
    }
    cout << tot << "\n";
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1;
    while (t--)
    {
        solve();
    }
}