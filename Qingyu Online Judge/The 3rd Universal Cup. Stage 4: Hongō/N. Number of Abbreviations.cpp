#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    s = ' ' + s;
    if (n == 1)
    {
        cout << 1 << "\n";
        return;
    }
    int ans = 0;
    vector<vector<int>> tsum(26, vector<int>(n + 1));
    for (int i = 1; i <= n; i++)
    {
        for (int j = 0; j < 26; j++)
        {
            tsum[j][i] = tsum[j][i - 1];
        }
        tsum[s[i] - 'a'][i]++;
    }
    for (int i = 1; i < n; i++)
    {
        if (i == 1)
        {
            ans += n - 2;
        }
        else
        {
            ans += n - i - 1 - (tsum[s[i] - 'a'][n - 1] - tsum[s[i] - 'a'][i]);
        }
    }
    for (int i = 1; i <= n; i++)
    {
        if (s[i] != s[n])
        {
            ans++;
        }
        if (s[i] != s[1])
        {
            ans++;
        }
    }
    if (s[1] == s[n])
    {
        ans++;
    }
    cout << ans + 1 << '\n';
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t = 1; // cin>>t;
    while (t--)
    {
        solve();
    }
}
