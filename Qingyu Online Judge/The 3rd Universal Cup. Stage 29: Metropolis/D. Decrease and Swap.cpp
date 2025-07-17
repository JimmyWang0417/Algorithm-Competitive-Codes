#include <bits/stdc++.h>
using namespace std;
int need[32] = {0, 0, 0, 0, 0, 0, 0, 0, 3, 1, 0, 0, 2, 0, 0, 0, 4, 2, 2, 0, 2, 0, 0, 0, 3, 1, 0, 0, 2, 0, 0, 0};
void solve()
{
    int n;
    cin >> n;
    string s;
    cin >> s;
    while (s.size() < 5)
    {
        s = '0' + s;
    }
    n = max(n, 5);
    s = ' ' + s;
    // cout<<s<<"\n";
    int cnt = 0;
    for (int i = 1; i <= n - 5; i++)
    {
        if (s[i] == '1')
        {
            cnt++;
        }
        else
        {
            cnt--;
            cnt = max(0, cnt);
        }
    }
    int o = 0;
    for (int i = n; i >= n - 4; i--)
    {
        // cout<<s[i]-'0'<<"\n";
        o = o * 2 + (s[i] - '0');
    }
    // cout<<o<<endl;
    if (need[o] > cnt)
    {
        cout << "No" << "\n";
    }
    else
    {
        cout << "Yes" << "\n";
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T;
    cin >> T;
    while (T--)
        solve();
    return 0;
}