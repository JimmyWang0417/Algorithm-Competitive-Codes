#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    int sum = 0;
    int ma = 0;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        ma = max(ma, a[i]);
        sum += a[i];
    }
    cout << sum - ma << "\n";
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}