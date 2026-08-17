#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
constexpr int N = 4e5 + 5;
constexpr int mod = 998244353;
auto _main()
{
    i64 a, b, c, d;
    cin >> a >> b;
    c = min(a, b);
    for (int i = 60; i >= 0; --i)
        if ((c >> i) & 1)
            d = i;
    if (a < b)
        cout << d / 2 + 1 << ' ' << 1 << '\n';
    else
        cout << (d + 1) / 2 + 1 << ' ' << 0 << '\n';
}
signed main()
{
    // freopen("project.in", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        _main();
    return 0;
}
