#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve()
{
    int n;
    cin >> n;
    vector<int> a(n + 1), b(n + 1), pos(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        pos[a[i]] = i;
    }
    for (int i = 1; i <= n; i++)
        cin >> b[i];
    for (int i = n; i > 1; i--)
    {
        int old = pos[b[i]];
        if (old == i)
            continue;
        for (int j = 1; j < old; j++)
            cout << 1;
        for (int j = old + 1; j <= i; j++)
            cout << 2;
        for (int j = i; j <= n; j++)
            cout << 1;
        for (int j = old; j < i; j++)
            a[j] = a[j + 1];
        a[i] = b[i];
        for (int j = 1; j <= n; j++)
            pos[a[j]] = j;
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
