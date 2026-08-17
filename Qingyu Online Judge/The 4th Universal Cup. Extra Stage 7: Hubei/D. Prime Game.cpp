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
    i64 n;
    Main()
    {
        int res = 0;
        cin >> n;
        while (n > 1)
        {
            i64 m = 0;
            for (i64 x = 1; x < n * 2; x *= 2)
                for (i64 y = 1; x * y < n * 2; y *= 3)
                    if (x * y >= n)
                        m = max(m, x * y / ((y == 1) ? 2 : 3));
            n = m;
            ++res;
        }
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

