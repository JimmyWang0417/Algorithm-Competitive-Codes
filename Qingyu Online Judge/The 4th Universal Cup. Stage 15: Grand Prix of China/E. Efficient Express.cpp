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
    int n, m, K;
    vector<int> L, R, cnt;
    vector<int> suf;
    vector<vector<int>> pre;
    vector<bool> canbad;
    vector<pair<int, int>> p;
    vector<i64> base;
    vector<vector<i64>> power;
    auto calc(int h, int b) -> i64
    {
        if (b > K)
            return 0;
        vector<int> pos = {1};
        vector<i64> dp = {1};
        for (int i = h - 1; i >= 1; --i)
        {
            if (!canbad[i])
                continue;
            int z = 0;
            i64 sum = 0;
            while (z < (int)pos.size() && pos[z] < L[i])
            {
                const int c = pre[b][L[i] - 1] - pre[b][pos[z] - 1];
                (sum += dp[z] * power[i][c]) %= mod;
                z++;
            }
            pos.resize(z);
            dp.resize(z);
            pos.emplace_back(L[i]);
            dp.emplace_back(-sum);
        }
        i64 res = 0;
        for (auto i : dp)
            (res += i) %= mod;
        return res * base[b] % mod;
    }
    Main()
    {
        cin >> n >> m >> K;
        cnt.resize(K + 5);
        L.resize(K + 5, n + 1), R.resize(K + 5, 0);
        for (int i = 1; i <= n; ++i)
        {
            int x;
            cin >> x;
            L[x] = min(L[x], i);
            R[x] = max(R[x], i);
            cnt[x]++;
        }
        canbad.resize(K + 1);
        suf.resize(n + 2, K + 1);
        p.resize(m);
        for (auto &[x, y] : p)
        {
            cin >> x >> y;
            suf[x] = min(suf[x], y);
        }
        for (int i = n; i >= 1; --i)
            suf[i] = min(suf[i], suf[i + 1]);
        for (int i = 1; i <= K; ++i)
            if (cnt[i] >= 2 && suf[R[i]] > i)
                canbad[i] = true;
        pre.resize(K + 1, vector<int>(n + 5));
        for (auto [x, y] : p)
            for (int i = 1; i <= y; ++i)
                pre[i][x]++;
        for (int i = 1; i <= K; ++i)
            for (int j = 1; j <= n; ++j)
                pre[i][j] += pre[i][j - 1];
        base.resize(K + 1);
        for (int b = 1; b <= K; b++)
        {
            i64 cur = 1;
            for (auto [x, y] : p)
            {
                if (y >= b)
                    cur = cur * K % mod;
                else
                    cur = cur * (K - b + 1) % mod;
            }
            base[b] = cur;
        }
        power.resize(K + 1, vector<i64>(m + 1));
        const auto invK = quickpow(K);
        for (int i = 1; i <= K; i++)
        {
            const auto v = (K - i) * invK % mod;
            power[i][0] = 1;
            for (int j = 1; j <= m; j++)
                power[i][j] = power[i][j - 1] * v % mod;
        }
        i64 res = 0;
        for (int h = 1; h <= K; ++h)
            (res += calc(h, h) - calc(h, h + 1)) %= mod;
        cout << (res + mod) % mod << '\n';
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
