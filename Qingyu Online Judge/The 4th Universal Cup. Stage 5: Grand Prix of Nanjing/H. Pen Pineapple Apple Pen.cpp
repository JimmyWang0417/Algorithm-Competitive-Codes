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
    int n;
    string str;
    vector<vector<int>> a, b;
    auto solve(int beg)
    {
        string s = " " + str.substr(beg, (int)str.size() - beg);
        vector<int> p(s.length()), dep(s.length());
        dep[1] = 1;
        for (int i = 2, j = 0, k = 0; i < (int)s.length(); ++i)
        {
            while (j && s[j + 1] != s[i])
                j = p[j];
            while (k && s[k + 1] != s[i])
                k = p[k];
            if (s[j + 1] == s[i])
                ++j;
            if (s[k + 1] == s[i])
                ++k;
            while (k * 2 > i)
                k = p[k];
            dep[i] = dep[p[i] = j] + 1;
            a[beg][beg + i - 1] = dep[k];
        }
        for (int i = 1, j = 0; i < beg; ++i)
        {
            while (j && s[j + 1] != str[i])
                j = p[j];
            if (s[j + 1] == str[i])
                ++j;
            b[i][beg] = dep[j];
        }
    }
    Main()
    {
        cin >> str;
        n = (int)str.length();
        str = " " + str;
        a.assign(n + 5, vector<int>(n + 5));
        b.assign(n + 5, vector<int>(n + 5));
        for (int i = 1; i <= n; ++i)
            solve(i);
        vector<int> c(n + 5);
        i64 res = 0;
        for (int i = n; i >= 1; --i)
        {
            vector<int> d(n + 5);
            vector<i64> e(n + 5);
            for (int j = 1; j < i; ++j)
            {
                d[j] = (d[j - 1] + c[j]) % mod;
                e[j] = (e[j - 1] + (i64)j * c[j]) % mod;
            }
            for (int j = i - 1; j >= 1; --j)
            {
                (res += (i64)(j - 1) * a[j][i] * d[j - 1] -
                       (i64)a[j][i] * e[j - 1]) %= mod;
            }
            for (int j = 1; j < i; ++j)
                (c[j] += b[j][i]) %= mod;
        }
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
