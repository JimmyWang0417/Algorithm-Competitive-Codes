#include <bits/stdc++.h>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef __float128 f128;
constexpr int mod = 998244353;
auto _main()
{
    for (int i = 0; i < 50; ++i)
        cout << "35";
    cout << '\n';
    for (int i = 0; i < 9; ++i)
    {
        for (int j = 0; j < 100 * (1 << i); ++j)
            cout << '9';
        cout << '\n';
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
