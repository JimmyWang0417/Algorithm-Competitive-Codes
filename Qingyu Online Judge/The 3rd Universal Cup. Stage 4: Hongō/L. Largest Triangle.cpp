#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    sort(a.begin() + 1, a.end());
    reverse(a.begin() + 1, a.end());
    int ans = -1;
    auto cul = [&](int x, int y, int z) -> int
    {
        int p = (x + y + z) / 2;
        return p * (p - x) * (p - y) * (p - z);
    };
    for (int i = 1; i + 2 <= n; i++)
    {
        if (a[i] < a[i + 1] + a[i + 2])
        {
            ans = max(ans, cul(a[i], a[i + 1], a[i + 2]));
        }
    }
    cout << ans << "\n";
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
