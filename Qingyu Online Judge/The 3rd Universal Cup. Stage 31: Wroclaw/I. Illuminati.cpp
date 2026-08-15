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
    int n, m;
    vector<string> str;
    map<string, list<int>> mp;
    Main()
    {
        cin >> n >> m;
        str.resize(n);
        for (int i = 0; i < m; ++i)
        {
            string s;
            cin >> s;
            for (int j = 0; j < n; ++j)
                str[j] += s[j];
        }
        for (int i = 0; i < n; ++i)
            mp[str[i].substr(1, m - 1)].push_back(i);
        vector<int> p(n);
        for (int i = 0; i < n; ++i)
        {
            auto &vec = mp[str[i].substr(0, m - 1)];
            if (vec.empty())
            {
                cout << "NO\n";
                return;
            }
            p[i] = vec.front();
            vec.pop_front();
        }
        cout << "YES\n";
        for (auto i : p)
            cout << i + 1 << ' ';
        cout << '\n';
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
