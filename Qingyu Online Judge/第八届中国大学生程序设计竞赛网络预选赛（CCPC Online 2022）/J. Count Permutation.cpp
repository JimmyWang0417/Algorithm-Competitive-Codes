#include <bits/stdc++.h>
using namespace std;
typedef long long i64;
auto _main()
{
    auto phi = [&](i64 x)
    {
        i64 ans = x;
        for (int i = 2; (i64)i * i <= x; ++i)
            if (x % i == 0)
            {
                ans = ans / i * (i - 1);
                do
                    x /= i;
                while (x % i == 0);
            }
        if (x > 1)
            ans = ans / x * (x - 1);
        return ans;
    };
    i64 n, m, s, t;
    cin >> n >> m >> s >> t;
    auto d = gcd(abs(s - t), n);
    if (gcd(m - 1, n) == d)
        cout << phi(n) / phi(n / d) << '\n';
    else
        cout << 0 << '\n';

}
signed main()
{
    // freopen("project.in", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        _main();
    return 0;
}
