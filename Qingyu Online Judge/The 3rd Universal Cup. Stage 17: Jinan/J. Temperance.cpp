#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve()
{
    int n;
    cin >> n;
    map<int, int> x, y, z;
    int a, b, c;
    vector<array<int, 3>> tip(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a >> b >> c;
        tip[i] = {a, b, c};
        x[a]++;
        y[b]++;
        z[c]++;
    }
    vector<int> num(n + 1);
    for (int i = 1; i <= n; i++)
    {
        num[i] = max({x[tip[i][0]], y[tip[i][1]], z[tip[i][2]]});
    }
    sort(num.begin() + 1, num.end());
    for (int i = 0; i < n; i++)
    {
        int pos = upper_bound(num.begin() + 1, num.end(), i) - num.begin();
        cout << pos - 1 << " ";
    }
    cout << "\n";
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