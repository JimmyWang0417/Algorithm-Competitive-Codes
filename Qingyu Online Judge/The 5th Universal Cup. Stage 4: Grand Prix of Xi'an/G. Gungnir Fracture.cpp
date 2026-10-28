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
    int n;
    vector<int> a;
    struct node
    {
        i64 ans, lea;
        int min;
        auto friend operator+(const node &lhs, const node &rhs)
        {
            node res;
            auto [lans, llea, lmin] = lhs;
            auto [rans, rlea, rmin] = rhs;
            auto &[ans, lea, min] = res;
            min = ::min(lmin, rmin);
            ans = lans + rans;
            auto L = llea + rans, R = rlea + lans;
            if (lmin >= rmin)
            {
                auto c = ::min<i64>(lmin - rmin, L);
                L -= c;
                if (!L)
                    ans += lmin - rmin - c;
            }
            else
            {
                auto c = ::min<i64>(rmin - lmin, R);
                R -= c;
                if (!R)
                    ans += rmin - lmin - c;
            }
            lea = ::min(L, R);
            return res;
        }
    };
    auto solve(int l, int r)
    {
        if (l == r)
            return node{0, 0, a[l]};
        int mid = (l + r) >> 1;
        return solve(l, mid) + solve(mid + 1, r);
    }
    Main()
    {
        cin >> n;
        a.resize(1 << n);
        for (auto &i : a)
            cin >> i;
        auto ans = solve(0, (1 << n) - 1);
        cout << ans.ans + max<i64>(ans.min - ans.lea, 0) << '\n';
        // cout << max<i64>(ans.ans, ans.max) << '\n';
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
