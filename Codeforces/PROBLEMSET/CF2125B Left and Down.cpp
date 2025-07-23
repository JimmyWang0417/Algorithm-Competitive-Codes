#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 1e6 + 5;
constexpr int mod = 998244353;
inline void _main()
{
    ll a, b, k;
    cin >> a >> b >> k;
    if (max(a, b) / __gcd(a, b) <= k)
        cout << 1 << '\n';
    else
        cout << 2 << '\n';
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