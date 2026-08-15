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
    int n;
    i64 sum;
    vector<int> a;
    auto calc(i64 x) -> int
    {
        i64 cur = 0;
        bool flag = true;
        for (int i = 1; i <= n; ++i)
        {
            if (cur + a[i] >= x)
            {
                cur += a[i] - x;
                if ((!flag && cur) || cur > x || (cur == x && i < n))
                    return INT_MAX;
                flag = false;
            }
            else
            {
                cur += a[i];
                flag = true;
            }
        }
        return n - (int)(sum / x) + (a[1] > x) + (a[n] > x);
    }
    Main()
    {
        cin >> n;
        a.resize(n + 5);
        for (int i = 1; i <= n; ++i)
            cin >> a[i];
        sum = accumulate(a.begin() + 1, a.begin() + 1 + n, 0ll);
        i64 maxa = *max_element(a.begin() + 1, a.begin() + 1 + n);
        vector<i64> p;
        for (i64 i = 1; i * i <= sum; ++i)
            if (sum % i == 0)
            {
                if (i >= maxa / 2 && i <= sum / 2)
                    p.push_back(i);
                if (i * i < sum)
                {
                    i64 j = sum / i;
                    if (j >= maxa / 2 && j <= sum / 2)
                        p.push_back(j);
                }
            }
        sort(p.begin(), p.end());
        int ans = n - 1;
        i64 cap = sum;
        for (i64 x : p)
        {
            if (x > cap)
                break;
            int v = calc(x);
            if (v < ans)
            {
                ans = v;
                if (n - ans > 0)
                    cap = min(cap, sum / (n - ans));
            }
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

