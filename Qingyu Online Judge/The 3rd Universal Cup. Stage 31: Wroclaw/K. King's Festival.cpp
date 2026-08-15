#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef __float80 f80;
typedef __float128 f128;
constexpr int mod = 998244353;
constexpr auto quickpow(i64 a, int b)
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
constexpr int dx[] = {0, -1, 0, 1}, dy[] = {1, 0, -1, 0};
struct Main
{
    vector<string> str;
    map<string, list<int>> mp;
    int ans = 0;
    string s, t;
    auto dfs(int u, int k)
    {
        if (ans <= k)
            return;
        if (u == (int)s.size())
        {
            ans = k;
            t = s;
            return;
        }
        if (s[u] == '#')
            dfs(u + 1, k + 1);
        else
        {
            s[u] = '#';
            dfs(u + 1, k + 1);
            s[u] = '.';
            for (int i = u - 1; i >= 0; i--)
                if ((i + u) % 2 == 1)
                {
                    if (s[i] != '#')
                        return;
                }
                else
                {
                    if (s[i] != '#' && s[(i + u) / 2] != '#')
                        return;
                }
            dfs(u + 1, k);
        }
    }
    Main()
    {
        cin >> s;
        if (s.length() == 1)
        {
            cout << "1\n#\n";
            return;
        }
        ans = (int)s.length();
        t = s;
        dfs(0, 0);
        cout << ans << '\n'
             << t << '\n';
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        Main();
    return 0;
}
