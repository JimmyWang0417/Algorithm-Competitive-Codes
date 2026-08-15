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
    vector<int> a;
    Main()
    {
        cin >> n;
        a.resize(2 * n);
        for (auto &i : a)
            cin >> i;
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q;
        int m = 0;
        for (int i = 2 * n - 1; i >= 0; --i)
        {
            if (!m)
            {
                if (!q.empty() && q.top().first < a[i])
                {
                    q.pop();
                    q.emplace(a[i], i);
                }
                ++m;
            }
            else
            {
                q.emplace(a[i], i);
                --m;
            }
        }
        vector<int> p;
        while (!q.empty())
        {
            p.push_back(q.top().second);
            q.pop();
        }
        ranges::sort(p);
        for (int i : p)
            cout << i + 1 << ' ';
        cout << '\n';
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
