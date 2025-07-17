#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve()
{
    int n, m, q;
    cin >> n >> m >> q;

    int flag, id, x;
    int level = -1;
    map<int, int> yes;
    map<int, int> no;
    vector<int> ans(m + 1);
    vector<int> ok;
    while (q--)
    {
        cin >> flag;
        if (flag == 1)
        {
            cin >> x;
            level = x;
            for (int i = 0; i < ok.size(); i++)
            {
                ans[ok[i]] += m - i;
            }
            ok.clear();
            yes.clear();
            no.clear();
        }
        if (flag == 2)
        {
            cin >> id >> x;
            if (x != level)
            {
                continue;
            }
            if (!yes[id] && !no[id])
            {
                yes[id] = 1;
                ok.push_back(id);
            }
        }
        if (flag == 3)
        {
            cin >> id >> x;
            if (x != level)
            {
                continue;
            }
            if (!yes[id] && !no[id])
            {
                no[id] = 1;
            }
        }
    }
    for (int i = 0; i < ok.size(); i++)
    {
        ans[ok[i]] += m - i;
    }
    vector<pair<int, int>> res;
    for (int i = 1; i <= m; i++)
    {
        res.push_back({ans[i], i});
    }
    sort(res.begin(), res.end(), [&](pair<int, int> &a, pair<int, int> &b)
         {
        if(a.first==b.first){
            return a.second<b.second;
        }
        return a.first>b.first; });
    // reverse(res.begin(),res.end());
    for (auto [a, b] : res)
    {
        cout << b << " " << a << "\n";
    }
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