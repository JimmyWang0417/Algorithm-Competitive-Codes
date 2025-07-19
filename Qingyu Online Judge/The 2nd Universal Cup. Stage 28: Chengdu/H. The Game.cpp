#include <bits/stdc++.h>
using namespace std;

#define int long long

void solve()
{
    int n;
    cin >> n;
    n *= 2;
    vector<int> tip(n);
    unordered_map<int, int> use;
    for (int i = 0; i < n; i++)
    {
        cin >> tip[i];
        use[tip[i]]++;
    }
    vector<int> n_tip(tip);
    reverse(n_tip.begin(), n_tip.end());
    if (n_tip == tip)
    {
        cout << "Qingyu" << "\n";
        return;
    }
    int tot = 0;
    for (auto &[a, b] : use)
    {
        tot += b - 1;
    }
    // cout<<tot<<"\n";
    cout << (tot >= use.size() ? "Qingyu" : "Kevin") << "\n";
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
// 1 3 6 11 19 33
// 1 2 3 4  5  6