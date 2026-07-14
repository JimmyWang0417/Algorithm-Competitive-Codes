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
constexpr int inv2 = quickpow(2);
struct Main
{
    int n, block;
    int limit, len;
    vector<int> a;
    struct node : array<int, 2>
    {
        int tag;
    };
    vector<node> tree;
    auto insert(int x, int y, int v)
    {
        int u = 0;
        for (int i = 20; i >= 0; --i)
        {
            int c = (x >> i) & 1, d = (y >> i) & 1;
            if (!d)
            {
                if (!tree[u][c])
                {
                    tree[u][c] = (int)tree.size();
                    tree.emplace_back();
                }
                u = tree[u][c];
            }
            else
            {
                if (!tree[u][c])
                {
                    tree[u][c] = (int)tree.size();
                    tree.emplace_back();
                }
                tree[tree[u][c]].tag += v;

                if (!tree[u][c ^ 1])
                {
                    tree[u][c ^ 1] = (int)tree.size();
                    tree.emplace_back();
                }
                u = tree[u][c ^ 1];
            }
        }
    }
    vector<i64> cnt;
    auto pushdown(int h, int u, int v)
    {
        if (h == -1)
        {
            if (tree[u].tag)
            {
                if (v >= (int)cnt.size())
                    cnt.resize(v + 1);
                cnt[v] += tree[u].tag;
            }
            return;
        }
        if (!tree[u][0])
        {
            tree[u][0] = (int)tree.size();
            tree.emplace_back();
        }
        tree[tree[u][0]].tag += tree[u].tag;
        pushdown(h - 1, tree[u][0], v << 1);
        if (!tree[u][1])
        {
            tree[u][1] = (int)tree.size();
            tree.emplace_back();
        }
        tree[tree[u][1]].tag += tree[u].tag;
        pushdown(h - 1, tree[u][1], v << 1 | 1);
    }
    template <typename T>
    auto FWT(vector<T> &dp)
    {
        for (int mid = 1; mid < limit; mid <<= 1)
            for (int i = 0; i < limit; i += mid << 1)
                for (int j = 0; j < mid; ++j)
                {
                    auto x = dp[i + j], y = dp[i + j + mid];
                    dp[i + j] = x + y;
                    dp[i + j + mid] = x - y;
                }
    }
    template <typename T>
    auto IFWT(vector<T> &dp)
    {
        for (int mid = 1; mid < limit; mid <<= 1)
            for (int i = 0; i < limit; i += mid << 1)
                for (int j = 0; j < mid; ++j)
                {
                    auto x = dp[i + j], y = dp[i + j + mid];
                    dp[i + j] = (x + y) / 2;
                    dp[i + j + mid] = (x - y) / 2;
                }
    }
    Main() : tree(1)
    {
        cin >> n;
        block = (int)sqrt(n);
        a.resize(block + 5);
        for (int i = 2; i <= block; ++i)
        {
            int f = (int)sqrt(i);
            a[i] = a[f] ^ (i - f * f);

            if (a[i] >= (int)cnt.size())
                cnt.resize(a[i] + 1);
        }
        for (int i = 1; i <= block; ++i)
            ++cnt[a[i]];
        for (int i = 1; i <= block; ++i)
        {
            int l = max(i * i, block + 1) - i * i, r = min((i + 1) * (i + 1) - 1, n) - i * i;
            if (l > r)
                continue;
            insert(a[i], r + 1, 1);
            insert(a[i], l, -1);
        }
        pushdown(20, 0, 0);
        limit = 1, len = 0;
        while (limit < (int)cnt.size())
        {
            limit <<= 1;
            ++len;
        }
        cnt.resize(limit);
        FWT(cnt);
        for (int i = 0; i < limit; ++i)
            cnt[i] *= cnt[i];
        IFWT(cnt);
        i64 res = 1;
        for (int i = 2; i < limit; ++i)
            if (cnt[i])
                (res *= quickpow(i, cnt[i] / 2)) %= mod;
        cout << res << '\n';
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