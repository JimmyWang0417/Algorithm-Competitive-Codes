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
    int n, s, d, m;
    Main()
    {
        cin >> n >> s >> d >> m;
        for (int i = 0; i < n; ++i)
        {
            int a, k;
            cin >> a >> k;
            int need = (k + d - 1) / d;
            if (min(a, 3) * s >= m)
            {
                cout << "Yes\n"
                     << i + 1 << '\n';
                return;
            }
            else if (need > min(3, 5 - a))
            {
                cout << "No\n";
                return;
            }
            else
                m -= min(a, 3 - need) * s;
        }
        cout << "No\n";
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
