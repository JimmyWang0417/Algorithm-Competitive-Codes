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
struct exkmp
{
    string s;
    vector<int> z;
    exkmp() = default;
    exkmp(const string &_s) : s(_s), z(s.size())
    {
        z[0] = (int)s.size();
        for (int i = 1, l = 0, r = -1; i < (int)s.size(); ++i)
        {
            if (i <= r)
                z[i] = min(z[i - l], r - i + 1);
            while (i + z[i] < (int)s.size() && s[z[i]] == s[i + z[i]])
                ++z[i];
            if (i + z[i] - 1 > r)
            {
                l = i;
                r = i + z[i] - 1;
            }
        }
    }
    auto match(const string &t)
    {
        vector<int> p(t.size());
        for (int i = 0, l = 0, r = -1; i < (int)p.size(); ++i)
        {
            if (i <= r)
                p[i] = min(z[i - l], r - i + 1);
            while (i + p[i] < (int)t.size() && s[p[i]] == t[i + p[i]])
                ++p[i];
            if (i + p[i] - 1 > r)
            {
                l = i;
                r = i + p[i] - 1;
            }
        }
        return p;
    }
};
struct Main
{
    int n, m;
    vector<string> a;
    vector<string> dp;
    auto merge(const string &S, const string &T)
    {
        auto Z = exkmp(T);
        auto z = Z.z;
        auto p = Z.match(S);
        auto calc = [&](int x, int y)
        {
            if (x > y)
                swap(x, y);
            if (p[x] < y - x)
            {
                if (T[p[x]] < S[x + p[x]])
                    return x;
                else if (T[p[x]] > S[x + p[x]])
                    return y;
            }
            else if (z[y - x] < m - y)
            {
                if (T[y - x + z[y - x]] < T[z[y - x]])
                    return x;
                else
                    return y;
            }
            return x;
        };
        int minn = -1;
        for (int j = max(0, m - (int)T.size()); j <= (int)S.size(); ++j)
            minn = minn == -1 ? j : calc(minn, j);
        return S.substr(0, minn) + T.substr(0, m - minn);
    }
    auto minsuffix(const string &s)
    {
        int i = 0, j = 1, k = 0;
        while (i < (int)s.length() && j < (int)s.length() && k < (int)s.length())
        {
            char c = i + k == (int)s.length() ? CHAR_MAX : s[i + k];
            char d = j + k == (int)s.length() ? CHAR_MAX : s[j + k];
            if (c == d)
                ++k;
            else
            {
                if (c > d)
                    i += k + 1;
                else
                    j += k + 1;
                if (i == j)
                    ++j;
                k = 0;
            }
        }
        return s.substr(min(i, j));
    }
    Main()
    {
        cin >> n >> m;
        a.resize(n);
        dp.resize(n);
        for (auto &s : a)
            cin >> s;
        dp[n - 1] = a[n - 1];
        for (int i = n - 2; i >= 0; --i)
            dp[i] = merge(a[i], dp[i + 1]);
        string answer = a[n - 1];
        for (int i = 1; i + 1 < n; ++i)
            answer = min(answer, merge(minsuffix(a[i]), dp[i + 1]));
        for (int i = 0; i < (int)a.front().size(); ++i)
            answer = min(answer, a.front().substr(i) + dp[1].substr(0, i));
        cout << answer << '\n';
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

