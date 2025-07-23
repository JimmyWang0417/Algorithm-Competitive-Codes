#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 1e6 + 5;
constexpr int mod = 998244353;
constexpr int prime[] = {2, 3, 5, 7};
inline void _main()
{
    auto calc = [](ll x)
    {
        return x - x / 2 - x / 3 - x / 5 - x / 7
        + x / 6 + x / 10 + x / 14 + x / 15 + x / 21 + x / 35
        - x / 30 - x / 42 - x / 70 - x / 105
        + x / 210;
    };
    ll l, r;
    cin >> l >> r;
    cout << calc(r) - calc(l - 1) << '\n';
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