#include <bits/stdc++.h>
using namespace std;

#define mod 998244353
#define int long long

int ksm(int n, int k)
{
    int base = n;
    int res = 1;

    while (k)
    {
        if (k & 1)
        {
            res = res * base % mod;
        }
        base = base * base % mod;
        k >>= 1;
    }

    return res;
}

void solve()
{
    int n, k;
    cin >> n >> k;
    if (k % 2)
    {
        cout << (n + 1) * ksm(2, mod - 2) % mod * ksm(n, k) % mod << "\n";
    }
    else
    {
        int ans = (n + 1) * ksm(2, mod - 2) % mod * ksm(n, k) % mod;
        // cout<<ans<<"\n";
        int o = 1;
        for (int i = k; i >= k - k / 2 + 1; i--)
        {
            o *= i;
            o %= mod;
        }
        int oo = 1;
        for (int i = 1; i <= k / 2; i++)
        {
            oo *= i;
            oo %= mod;
        }
        o = o * ksm(oo, mod - 2) % mod;
        // cout<<o<<"\n";
        int sum = 0;
        for (int i = 1; i <= n - 1; i++)
        {
            sum += ksm(i, k / 2) * ksm(n - i, k / 2) % mod;
            sum %= mod;
        }
        sum = sum * o % mod;
        sum = sum * ksm(2, mod - 2) % mod;
        cout << ((ans - sum) % mod + mod) % mod << "\n";
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    // int t;cin>>t;
    int t = 1;
    while (t--)
    {
        solve();
    }
}