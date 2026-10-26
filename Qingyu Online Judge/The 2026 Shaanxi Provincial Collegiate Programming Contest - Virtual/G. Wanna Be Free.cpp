#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
struct Main
{
    string s;
    vector<int> a;
    auto check()
    {
        for (auto c : s)
            if (c != 'W' && c != 'B')
                return false;
        return true;
    }
    Main()
    {
        cin >> s;
        int l = -1, r = -1;
        for (int i = 0; i < (int)s.length(); ++i)
            if (s[i] != 'W' && s[i] != 'B')
            {
                if (l == -1)
                    l = i;
                r = i;
            }
        a.resize(s.length());
        for (int i = 0; i < (int)a.size(); ++i)
            a[i] = (s[i] == 'W') ^ (i & 1);
        int L = 0, R = (int)a.size() - 1;
        while (L < (int)a.size() && a[L] == a.front())
            ++L;
        while (R >= 0 && a[R] == a.back())
            --R;
        int ans = INT_MAX;
        {
            if (L == (int)a.size())
            {
                if (l == -1)
                    cout << "0\n";
                else
                    cout << (r - l + 1) << '\n';
                return;
            }
        }
        {
            int x = 0, y = R;
            if (l != -1)
            {
                x = min(x, l);
                y = max(y, r);
            }
            ans = min(ans, y - x + 1);
        }
        {
            int x = L, y = (int)a.size() - 1;
            if (l != -1)
            {
                x = min(x, l);
                y = max(y, r);
            }
            ans = min(ans, y - x + 1);
        }
        if (L <= R && (a.back() == a.front()))
        {
            int x = L, y = R;
            if (l != -1)
            {
                x = min(x, l);
                y = max(y, r);
            }
            ans = min(ans, y - x + 1);
        }
        cout << ans << '\n';
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
