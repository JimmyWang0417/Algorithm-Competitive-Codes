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
constexpr int N = 2e6 + 5;
array<array<int, 23>, N> fa;
array<array<i64, 23>, N> f, g;
struct Main
{
    int n;
    vector<int> a;
    vector<int> L, R;
    Main()
    {
        cin >> n;
        a.resize(n + 5);
        L.resize(n + 5), R.resize(n + 5);
        for (int i = 1; i < n; ++i)
            cin >> a[i];
        for (int k = 0; k <= 1; ++k)
        {
            int l = 0, r = (n - k) >> 1;
            for (int i = 1; i < n; ++i)
            {
                if (a[i] > 0)
                {
                    L[i] = (a[i] + i - n + k + 1) >> 1;
                    R[i] = INT_MAX / 2;
                }
                else
                {
                    L[i] = INT_MIN / 2;
                    R[i] = (a[i] + i + k) >> 1;
                }
            }
            L[n] = INT_MIN, R[n] = INT_MAX;
            for (int i = 2; i <= n; ++i)
            {
                L[i] = max(L[i], L[i - 1]);
                R[i] = min(R[i], R[i - 1] + 1);
            }
            for (int i = 1; i < n; ++i)
            {
                l = max(l, -R[i]);
                r = min(r, i - L[i]);
                if (l > r)
                    break;
            }
            l = max(l, L[n] - k);
            r = min(r, R[n] - k);
            if (l > r)
                continue;
            bool flag = false;
            // 令s=l
            L[n] = R[n] = k + l;
            for (int i = n - 1; i >= 1; --i)
            {
                L[i] = max(L[i], L[i + 1] - 1);
                R[i] = min(R[i], R[i + 1]);
            }
            for (int i = 1; i <= n; ++i)
                if (L[i] > R[i])
                {
                    flag = true;
                    break;
                }
            if (flag)
                continue;
            
            for (int i = 1, j = -l; i <= n; ++i)
            {
                if (L[i] <= j && j <= R[i])
                    cout << '<';
                else
                {
                    cout << '>';
                    ++j;
                }
            }
            cout << '\n';
            return;
        }
        assert(false);
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

