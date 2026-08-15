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
struct Main
{
    int n, c, k;
    vector<int> a;
    Main()
    {
        cin >> n >> c >> k;
        a.resize(n);
        for (auto &i : a)
            cin >> i;
        ranges::sort(a, greater<>());
        cout << fixed << setprecision(9);
        if (k == 0)
        {
            int l = 0, r = (int)a.size() - 1;
            auto calc = [&](int mid)
            {
                double res = 0;
                for (int i = 0; i <= mid; ++i)
                    res += a[i];
                res = res / n - c;
                return res / (mid + 1) * n;
            };
            while (l <= r)
            {
                int mid = (l + r) / 2;
                if (calc(mid) <= a[mid])
                    l = mid + 1;
                else
                    r = mid - 1;
            }
            cout << calc(r) << '\n';
        }
        else
        {
            vector<i64> pre(n);
            pre[0] = a[0];
            for (int i = 1; i < n; ++i)
                pre[i] = pre[i - 1] + a[i];
            double F = -1e100, G = 0;
            for (int i = 4e5, j = n - 1; i >= 1; --i)
            {
                swap(F, G);
                while (j >= 0 && a[j] < G)
                    --j;
                F = (double)(j >= 0 ? pre[j] : 0) / n + (double)(n - j - 1) / n * G - c - (double)k * (i - 1);
            }
            cout << F << '\n';
        }
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        Main();
    return 0;
}

