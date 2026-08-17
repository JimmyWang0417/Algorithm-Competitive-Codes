#include <bits/stdc++.h>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef __float128 f128;
auto _main()
{
    i64 n;
    int m;
    cin >> n >> m;
    i64 sum = 0;
    bool flag = true;
    for (int i = 1; i <= 2 * m; ++i)
    {
        i64 a;
        cin >> a;
        sum += a;
        if (i % 2 && sum < (i + 1) / 2 * n)
            flag = false;
    }
    if (sum != n * m || !flag)
    {
        cout << "No\n";
        return;
    }
    cout << "Yes\n";
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        _main();
    return 0;
}
