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
constexpr double eps = 1e-7;
struct Main
{
    Main()
    {
        int n, k;
        cin >> n >> k;
        vector<int> a(n);
        for (int &i : a)
            cin >> i;
        auto calc = [&](auto mid)
        {
            i64 res = 0;
            for (int &x : a)
            {
                // (x / (1 + x * t)) >= mid
                // (x / mid - 1) / x >= t
                res += max((int)floor(mid - 100.0 / x), 0);
            }
            return res;
        };
        double l = 0, r = k + 200;
        while (abs(r - l) > eps)
        {
            auto mid = (l + r) / 2;
            if (calc(mid) <= k)
                l = mid;
            else
                r = mid;
        }
        vector<int> fuck(n);
        for (int i = 0; i < n; ++i)
        {
            int x = a[i];
            int y = max((int)floor(l - 100.0 / x), 0);
            k -= y;
            fuck[i] = y;
        }
        assert(k >= 0);
        while (k--)
        {
            int id = 0;
            double now = 0;
            for (int i = 0; i < n; ++i)
            {
                int x = a[i], y = fuck[i];
                double nxt = (100.0 + (x * y + x)) / (100.0 + (x * y));
                if (nxt > now)
                {
                    id = i;
                    now = nxt;
                }
            }
            ++fuck[id];
        }
        double res = 1;
        for (int i = 0; i < n; ++i)
            res *= 1 + (a[i] * fuck[i]) / 100.0;
        cout << res << '\n';
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        Main();
    return 0;
}

