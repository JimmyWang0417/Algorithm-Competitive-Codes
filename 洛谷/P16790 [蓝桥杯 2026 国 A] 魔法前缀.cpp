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
    vector<array<int, 26>> ch;
    auto insert(const string &s)
    {
        int u = 0;
        for (auto _c : s)
        {
            int c = _c - 'a';
            if (!ch[u][c])
            {
                ch.emplace_back();
                ch[u][c] = (int)ch.size() - 1;
            }
            u = ch[u][c];
        }
    }
    auto dfs(int u) -> int
    {
        int res = 0;
        for (int v : ch[u])
        {
            if (!v)
                continue;
            res ^= dfs(v) + 1;
        }
        return res;
    }
    Main() : ch(1)
    {
        cin >> n;
        for (int i = 0; i < n; ++i)
        {
            string s;
            cin >> s;
            insert(s);
        }
        if (dfs(0))
            cout << "XiaoLan\n";
        else
            cout << "XiaoQiao\n";
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