#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef __float80 f80;
typedef __float128 f128;
constexpr int mod = 998244353;
struct Main
{
    Main()
    {
        string s;
        cin >> s;
        int n = (int)s.length(), q;
        vector<array<int, 2>> nxt(n + 2);
        nxt[n + 1][0] = nxt[n + 1][1] = n + 1;
        nxt[n] = nxt[n + 1];
        for (int i = n - 1; i >= 0; --i)
        {
            nxt[i] = nxt[i + 1];
            nxt[i][s[i] == 'R'] = i + 1;
        }
        cin >> q;
        while (q--)
        {
            string t;
            cin >> t;
            int u = 0;
            for (int i = 0; i < (int)t.size(); ++i)
                u = nxt[u][t[i] == 'R'];
            if (u == n + 1)
                cout << "NO\n";
            else if (t.front() == 'R' && s.front() != 'R')
                cout << "NO\n";
            else if (t.back() == 'L' && s.back() != 'L')
                cout << "NO\n";
            else
                cout << "YES\n";
        }
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        Main();
    return 0;
}
