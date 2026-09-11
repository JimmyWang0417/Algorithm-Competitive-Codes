#include <bits/stdc++.h>
using namespace std;
struct Main
{
    int n;
    map<string, int> mp;
    Main()
    {
        cin >> n;
        for (int i = 0; i < n; ++i)
        {
            string s;
            cin >> s;
            mp[s]++;
        }
        for (auto [x, y] : mp)
            if (y > n / 2)
            {
                cout << x << '\n';
                return;
            }
        cout << "uh-oh\n";
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        Main();
    return 0;
}