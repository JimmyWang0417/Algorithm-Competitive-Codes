#include <bits/stdc++.h>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef __float128 f128;
constexpr int N = 2e5 + 5;
auto _main()
{
    int n;
    cin >> n;
    vector<int> a(n);
    vector<vector<int>> g(n + 1);
    bitset<N * 2> bits, b;
    bits.set();
    for (int i = 0; i < n; ++i)
    {
        cin >> a[i];
        if (a[i] == -1)
            b[i] = true;
        else
            g[a[i]].push_back(i);
    }
    for (int i = n; i < 2 * n; ++i)
        b[i] = true;
    for (int i = 1; i <= n; ++i)
    {
        for (auto j : g[i])
            b[j] = true;
        for (auto j : g[i])
            bits &= b >> j;
        for (auto j : g[i])
            b[j] = false;
    }
    for (int i = 1; i <= n; ++i)
        for (int j = 2 * i; j <= n; j += i)
            bits[i] = bits[i] & bits[j];
    for (int i = 1; i <= n; ++i)
        cout << bits[i];
    cout << '\n';
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
