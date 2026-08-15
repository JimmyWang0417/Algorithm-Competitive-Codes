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
    int n;
    string s, t;
    vector<int> p, q;
    Main()
    {
        cin >> n;
        cin >> s >> t;
        {
            int j = -1;
            for (int i = 0; i < n - 1; ++i)
            {
                if (s[i] == '1')
                {
                    p.push_back(i - j);
                    j = i;
                }
            }
            p.push_back(n - j - 1);
        }
        {
            ranges::sort(p);
            vector<int> _;
            for (int i = 0, j; i < (int)p.size(); i = j)
            {
                j = i + 1;
                while (j < (int)p.size() && p[i] == p[j])
                    ++j;
                if ((j - i) & 1)
                    _.push_back(p[i]);
            }
            p.swap(_);
        }
        {
            int j = -1;
            for (int i = 0; i < n - 1; ++i)
            {
                if (t[i] == '1')
                {
                    q.push_back(i - j);
                    j = i;
                }
            }
            q.push_back(n - j - 1);
        }
        {
            ranges::sort(q);
            vector<int> _;
            for (int i = 0, j; i < (int)q.size(); i = j)
            {
                j = i + 1;
                while (j < (int)q.size() && q[i] == q[j])
                    ++j;
                if ((j - i) & 1)
                    _.push_back(q[i]);
            }
            q.swap(_);
        }
        i64 res = 0;
        for (int x : p)
            for (int y : q)
                res ^= (i64)x * y;
        cout << res << '\n';
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
