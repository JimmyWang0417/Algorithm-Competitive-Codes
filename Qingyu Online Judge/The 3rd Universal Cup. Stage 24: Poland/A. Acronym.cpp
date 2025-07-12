#include <bits/stdc++.h>
using namespace std;
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    vector<string> a(n + 5);
    array<string, 26> cnt;
    for (int i = 1; i <= n; ++i)
    {
        cin >> a[i];
        cnt[a[i][0] - 'A'] = a[i];
    }
    for (int i = 1; i <= n; ++i)
    {
        bool flag = true;
        for (auto c : a[i])
        {
            if (cnt[c - 'A'] == "")
            {
                flag = false;
                break;
            }
        }
        if (flag)
        {
            cout << a[i].size() << '\n';
            for (auto c : a[i])
                cout << cnt[c - 'A'] << ' ';
            cout << '\n';
            cout.flush();
            return 0;
        }
    }
    cout << "-1\n";
    return 0;
}