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
constexpr int N = 1e7;
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
constexpr int inv2 = quickpow(2);
vector<int> prime, low;
vector<int> miu, miu2;
vector<int> premiu, premiu2;
vector<bool> vis;
auto init(int n)
{
    vis.resize(n + 5);
    low.resize(n + 5);
    miu.resize(n + 5);
    miu2.resize(n + 5);
    miu[1] = miu2[1] = 1;
    for (int i = 2; i <= n; ++i)
    {
        if (!low[i])
        {
            prime.push_back(i);
            // for (int j = 1, k = i; k <= n; ++j, k *= i)
            // {
            //     if (j == 1)
            //     {
            //         miu[k] = -1;
            //         miu2[k] = 1;
            //     }
            // }
            miu[i] = -1;
            miu2[i] = 1;
            low[i] = i;
        }
        for (int j = 0; j < (int)prime.size(); ++j)
        {
            if (i * prime[j] > n)
                break;

            if (i % prime[j] == 0)
                low[i * prime[j]] = low[i] * prime[j];
            else
                low[i * prime[j]] = prime[j];

            int x = i * prime[j];
            miu[x] = miu[x / low[x]] * miu[low[x]];
            miu2[x] = miu2[x / low[x]] * miu2[low[x]];

            if (i % prime[j] == 0)
                break;
        }
    }
    premiu.resize(miu.size()), premiu2.resize(miu2.size());
    partial_sum(miu.begin(), miu.end(), premiu.begin());
    partial_sum(miu2.begin(), miu2.end(), premiu2.begin());
}
struct Main
{
    auto F(u64 n, u64 m) -> u64
    {
        u64 res = 0;
        for (u64 l = 1, r; l <= n && l <= m; l = r + 1)
        {
            auto t1 = (u64)sqrtl(n / l), t2 = (u64)sqrtl(m / l);
            r = min(n / (t1 * t1), m / (t2 * t2));
            res += (G(r) - G(l - 1)) * t1 * t2;
        }
        return res;
    }
    auto G(u64 n) -> u64
    {
        if (n <= N)
            return premiu2[n];
        static unordered_map<u64, u64> mp;
        if (mp.find(n) != mp.end())
            return mp[n];
        u64 res = 0;
        for (u64 l = 1, r; l <= n; l = r + 1)
        {
            u64 t = n / (l * l);
            if (t == 0)
                break;
            r = (u64)sqrtl(n / t);
            res += (H(r) - H(l - 1)) * t;
        }
        return mp[n] = res;
    }
    auto H(u64 n) -> u64
    {
        if (n <= N)
            return premiu[n];
        static unordered_map<u64, u64> mp;
        if (mp.find(n) != mp.end())
            return mp[n];
        u64 res = 1;
        for (u64 l = 2, r; l <= n; l = r + 1)
        {
            r = n / (n / l);
            res -= (r - l + 1) * H(n / l);
        }
        return mp[n] = res;
    }
    Main()
    {
        u64 n, m;
        cin >> n >> m;
        cout << F(n, m) << '\n';
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    init(N);
    int T = 1;
    // cin >> T;
    while (T--)
        Main();
    return 0;
}