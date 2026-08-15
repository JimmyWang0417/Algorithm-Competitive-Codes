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
        int n;
        cin >> n;
        vector<int> a(n + 5), b(n + 5), c(n + 5);
        for (int i = 1; i <= n; ++i)
        {
            cin >> a[i];
            ++b[a[i]];
        }
        vector<int> p, q;
        vector<int> used(n + 5);
        for (int i = 1; i <= n; ++i)
            if (b[i] == 0)
                p.push_back(i);
        for (int i = 1; i <= n; ++i)
            if (b[a[i]] == 1)
                q.push_back(a[i]);
        if (b[a[1]] == 2)
        {
            q.insert(q.begin(), {p.back(), p.back()});
            p.pop_back();
        }
        for (int i = 2; i <= n; ++i)
        {
            if (b[a[i]] == 2)
            {
                if (a[i] == a[1])
                    continue;
                if (!used[a[i]])
                {
                    used[a[i]] = p.back();
                    p.pop_back();
                }
                c[i - 1] = used[a[i]];
            }
        }
        for (int i = n; i >= 1; --i)
        {
            if (!c[i])
            {
                c[i] = q.back();
                q.pop_back();
            }
        }
        cout << (b[a[1]] == 2) << '\n';
        for (int i = 1; i <= n; ++i)
            cout << c[i] << ' ';
        cout << '\n';
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
