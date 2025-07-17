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

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int n;
    cin >> n;
    vector<array<int, 3>> tip(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> tip[i][0] >> tip[i][1] >> tip[i][2];
    }

    auto cul = [&](array<int, 3> &x, array<int, 3> &y) -> double
    {
        return 1.0 * x[0] * x[2] * y[2] / x[1] / y[1] + 1.0 * y[0] * y[2] / y[1];
    };
    sort(tip.begin() + 1, tip.end(), [&](array<int, 3> &x, array<int, 3> &y)
         { return cul(x, y) < cul(y, x); });

    vector<int> dp(n + 1);
    for (int i = 1; i <= n; i++)
    {
        dp[i] = (dp[i - 1] + tip[i][0]) % mod * tip[i][2] % mod * ksm(tip[i][1], mod - 2) % mod;
    }

    cout << dp[n] << "\n";
}