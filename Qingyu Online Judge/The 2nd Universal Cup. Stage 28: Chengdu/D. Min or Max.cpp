#include <bits/stdc++.h>
using namespace std;

void solve()
{
    int n, m;
    cin >> n >> m;

    vector<int> a(n + 1);
    vector<int> b(m + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
    }
    for (int i = 1; i <= m; i++)
    {
        cin >> b[i];
    }

    int pos = 1;
    for (int i = 1; i <= n; i++)
    {
        if (pos > m)
        {
            break;
        }
        if (a[i] == b[pos])
        {
            pos++;
        }
    }

    cout << (pos > m ? "Yes" : "No") << "\n";
}

int main()
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