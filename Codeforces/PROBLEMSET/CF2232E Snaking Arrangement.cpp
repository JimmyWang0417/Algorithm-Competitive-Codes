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
constexpr int mod = 1e9 + 7;
template <typename T = int>
constexpr auto quickpow(i64 a, T b = mod - 2)
{
    a %= mod;
    i64 res = 1;
    while (b)
    {
        if (b & 1)
            (res *= a) %= mod;
        (a *= a) %= mod;
        b >>= 1;
    }
    return res;
}
struct Main
{
    int n, m;
    vector<bool> mark;
    vector<int> L, R;
    Main()
    {
        cin >> n >> m;
        mark.resize(2 * n);
        L.resize(2 * n + 5), R.resize(2 * n + 5);
        for (int i = 1; i <= 2 * n; ++i)
            L[i] = 1;
        for (int i = 1; i <= n; ++i)
            R[i] = i;
        for (int i = n + 1; i < 2 * n; ++i)
            R[i] = 2 * n - i;
        for (int i = 0; i < m; ++i)
        {
            int l;
            cin >> l;
            mark[l] = true;
            int sx, sy;
            cin >> sx >> sy;
            if (l == 1)
                continue;
            string s;
            cin >> s;
            int x = sx, y = sy;
            for (int j = 0; j < l - 1; ++j)
            {
                if (s[j] == 'D')
                    ++x;
                else
                    ++y;
                if (x + y - 1 <= n)
                {
                    if (s[j] == 'D')
                        L[x + y - 1] = max(L[x + y - 1], y + 1);
                    else
                        R[x + y - 1] = min(R[x + y - 1], y - 1);
                }
                else
                {
                    if (s[j] == 'D')
                        L[x + y - 1] = max(L[x + y - 1], n - x + 2);
                    else
                        R[x + y - 1] = min(R[x + y - 1], n - x);
                }
            }
        }
        i64 ans = 1;
        for (int i = 1; i <= n; ++i)
        {
            if (mark[2 * n - 2 * i + 1])
                continue;
            (ans *= R[i] - L[i] + 1) %= mod;
        }
        cout << ans << '\n';
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        Main();
    return 0;
}