#include <bits/stdc++.h>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef __float128 f128;
auto _main()
{
    int n, m;
    cin >> n >> m;
    for (int i = 0, x = 4, y = 1, z = 0; i < n;)
    {
        cout << z << '\n';
        z = (z * (i + 3ll) + y) % m;
        y = (y * (i + 4ll) + i % 2 * x) % m;
        if (++i % 2)
            x = x * (i + 3ll * (i > 1)) * i % m;
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        _main();
    return 0;
}
