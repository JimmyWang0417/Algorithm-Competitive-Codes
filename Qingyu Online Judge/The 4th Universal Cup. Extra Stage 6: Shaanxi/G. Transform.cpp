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
    int n, m;
    vector<int> a;
    Main()
    {
        cin >> n >> m;
        a.resize(n);
        for (auto &i : a)
            cin >> i;
        ranges::sort(a);
        if (n == 1 && a.front() == m)
        {
            cout << "0\n";
            return;
        }
        a.erase(ranges::upper_bound(a, m), a.end());
        auto check = [&]()
        {
            for (int i = 0, j = 0, k = 0; i <= m; j = k, ++i)
            {
                while (k < n && i == a[k])
                    ++k;
                if (j == k)
                    return false;
            }
            return true;
        };
        if (check())
        {
            cout << "2\n";
            return;
        }
        while (!a.empty() && a.back() == m)
            a.pop_back();
        ranges::reverse(a);
        {
            n = (int)a.size();
            i64 res = quickpow(2, m);
            int i = m - 1, j = 0, k = 0;
            int lea = 1;
            for (; i >= 0; --i, j = k)
            {
                if (lea > n)
                    break;
                while (k < n && i == a[k])
                    ++k;
                int c = min(lea, k - j);
                (res -= c * quickpow(2, i)) %= mod;
                lea += lea - c;
            }
            for (i = j; i < n; ++i)
                (res -= quickpow(2, a[i])) %= mod;
            cout << (res + mod) % mod << '\n';
        }
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
