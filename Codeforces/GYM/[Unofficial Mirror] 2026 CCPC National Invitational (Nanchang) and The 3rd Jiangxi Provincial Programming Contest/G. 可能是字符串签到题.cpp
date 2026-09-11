#include <bits/stdc++.h>
using namespace std;
struct Main
{
    int n, q;
    string s;
    vector<array<int, 26>> cnt;
    Main()
    {
        cin >> n >> q >> s;
        cnt.resize(n + 5);
        for (int i = 1; i <= n; ++i)
        {
            cnt[i] = cnt[i - 1];
            cnt[i][s[i - 1] - 'a']++;
        }
        while (q--)
        {
            int l, r;
            cin >> l >> r;
            int res = 0;
            for (int i = 0; i < 26; ++i)
                res = max(res, cnt[r][i] - cnt[l - 1][i]);
            cout << res << '\n';
        }
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    while (T--)
        Main();
    return 0;
}