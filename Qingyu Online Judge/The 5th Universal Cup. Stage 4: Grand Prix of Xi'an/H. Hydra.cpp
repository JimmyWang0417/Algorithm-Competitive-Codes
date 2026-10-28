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
template <typename T = int>
constexpr auto quickpow(i64 a, T b = mod - 2)
{
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
    int n, X, Y;
    vector<pair<int, int>> p;
    Main()
    {
        cin >> n >> X >> Y;
        p.resize(n);
        for (auto &[a, b] : p)
            cin >> a >> b;
        int pre = 0;
        map<int, int> mp;
        i64 cost = 0;
        for (auto [a, b] : p)
        {
            int h = max<i64>(0, pre - a);
            if (b > h)
            {
                mp[h]++;
                mp[b]--;
                cost += (i64)Y * (b - h);
            }
            pre = max(pre, a + b);
        }
        int now = 0, cnt = 0;
        i64 ans = cost;
        for (auto [nxt, v] : mp)
        {
            cost += (nxt - now) * (X - (i64)Y * cnt);
            ans = min(ans, cost);
            now = nxt;
            cnt += v;
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
