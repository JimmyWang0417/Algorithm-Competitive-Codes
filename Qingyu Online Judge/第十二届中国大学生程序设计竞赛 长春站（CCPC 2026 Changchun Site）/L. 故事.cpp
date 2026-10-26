#include <bits/stdc++.h>
using namespace std;
using i64 = int64_t;
struct Main
{
    auto solve(string s)
    {
        vector<tuple<int, int, int>> p;
        int m = (int)s.length();
        for (int l = 0, r; l < m; l = r)
        {
            r = l + 1;
            while (r < m && s[r] != s[r - 1])
                ++r;
            int cnt = 0;
            for (int i = l; i < r; ++i)
                cnt += (s[i] == '1');
            p.emplace_back(cnt, l, r);
        }
        sort(p.begin(), p.end(), greater<>());
        int A = 0, B = 2 * get<0>(p.front());
        for (int i = 0; i < (int)p.size(); ++i)
            A += get<0>(p[i]);
        for (int i = 0; i < (int)p.size(); ++i)
            B -= get<0>(p[i]);
        A %= 2;
        return max(A, B);
    }
    Main()
    {
        int n;
        string s;
        cin >> s;
        n = (int)s.length();
        if (n == 1)
        {
            cout << 1 << '\n';
            return;
        }
        if (n == 2)
        {
            cout << 2 - (s.front() == s.back()) << '\n';
            return;
        }
        int cnt = solve(s),
            cntl = solve(s.substr(1, n - 1)),
            cntr = solve(s.substr(0, n - 1)),
            cntlr = solve(s.substr(1, n - 2));
        int res = solve(s) * 2 + 1;
        if (cnt == cntl + 1)
        {
            cout << res - 1 - (cntlr + 2 == cnt) << '\n';
            return;
        }
        if (cnt == cntr + 1)
        {
            cout << res - 1 << '\n';
            return;
        }
        cout << res << '\n';
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        Main();
    return 0;
}
