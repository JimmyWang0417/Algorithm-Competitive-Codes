#include <bits/stdc++.h>
using namespace std;

map<char, int> use;

void solve()
{
    int n;
    cin >> n;
    vector<pair<char, int>> tip(n + 1);
    for (int i = 1; i <= n; i++)
    {
        cin >> tip[i].first >> tip[i].second;
    }
    char fir = tip[1].first;
    vector<pair<char, int>> ans;
    int las = tip[1].first;
    for (int i = 1; i <= n; i++)
    {
        pair<char, int> o;
        if (tip[i].first == las)
        {
            o.first = 'Z';
        }
        if (use[tip[i].first] - use[las] == 1 || use[tip[i].first] - use[las] == -3)
        {
            o.first = 'R';
        }
        if (use[tip[i].first] - use[las] == -1 || use[tip[i].first] - use[las] == 3)
        {
            o.first = 'L';
        }
        if (o.first != 'Z')
        {
            ans.push_back({o.first, 1e9});
        }
        o.first = 'Z';
        o.second = tip[i].second;
        ans.push_back(o);
        las = tip[i].first;
    }
    cout << ans.size() << " " << fir << "\n";
    for (auto [a, b] : ans)
    {
        if (b < 1e9)
            cout << a << " " << b << "\n";
        else
            cout << a << "\n";
    }
}

signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    use['N'] = 1;
    use['E'] = 2;
    use['S'] = 3;
    use['W'] = 4;
    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}