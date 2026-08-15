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
auto &operator<<(ostream &out, i128 rhs)
{
    if (rhs == 0)
        out << 0;
    else
    {
        stack<int> st;
        while (rhs)
        {
            st.push((int)(rhs % 10));
            rhs /= 10;
        }
        while (!st.empty())
        {
            out << st.top();
            st.pop();
        }
    }
    return out;
}
auto gcd(i128 x, i128 y)
{
    if (y == 0)
        return x;
    return gcd(y, x % y);
}
struct Main
{
    i64 n, k, a, b;
    auto print(i128 x, i128 y)
    {
        auto g = gcd(x, y);
        x /= g, y /= g;
        cout << x << ' ' << y << '\n';
    }
    auto calc(i128 mid)
    {
        i128 res = 0;
        for (i64 d = 1;; ++d)
        {
            i128 now = (i128)min((i128)n - d, (mid - (i128)a * d * d - (i128)2 * b * d) / ((i128)2 * a * d));
            if (now <= 0)
                break;
            res += now;
        }
        return res;
    }
    Main()
    {
        cin >> n >> k >> a >> b;
        // am
        i128 l = 0, r = (i128)1e14 * a + 2 * b * (i128)1e7;
        while (l <= r)
        {
            auto mid = (l + r) / 2;
            if (calc(mid) < k)
                l = mid + 1;
            else
                r = mid - 1;
        }
        print(l, a);
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cerr << (i128)(2 + 1000000000000) * (2 + 1000000000000) - (i128)(1 + 1000000000000) * (1 + 1000000000000) << '\n';
    // cin >> T;
    while (T--)
        Main();
    return 0;
}
