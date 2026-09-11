#include <bits/stdc++.h>
#include <cassert>
using namespace std;
using i64 = int64_t;
constexpr int mod1 = 1e9 + 7;
constexpr int mod2 = 1e9 + 9;
template <int mod>
struct Hash : vector<i64>
{
    constexpr static auto base = 998244353;
    static inline vector<i64> power = {1};
    static auto ensure(int n)
    {
        while ((int)power.size() <= n)
            power.emplace_back(power.back() * base % mod);
    }
    Hash() = default;
    Hash(const vector<int> &s)
    {
        resize(s.size());
        for (int i = 0; i < (int)s.size(); ++i)
            at(i) = ((i ? at(i - 1) * base : 0) + s[i]) % mod;
    }
    auto calc(int l, int r)
    {
        ensure(r - l + 1);
        return ((at(r) - (l ? at(l - 1) : 0) * power[r - l + 1]) % mod + mod) % mod;
    }
};
struct Main
{
    int n;
    auto calc(const string &s)
    {
        int x = 0;
        for (auto c : s)
        {
            int y = 0;
            if (c >= '0' && c <= '9')
                y = c - '0';
            else if (c >= 'a' && c <= 'z')
                y = c - 'a' + 10;
            else if (c >= 'A' && c <= 'Z')
                y = c - 'A' + 36;
            x = x * 62 + y;
        }
        return x;
    }
    vector<int> a;
    vector<int> answer;
    Main()
    {
        cin >> n;
        a.resize(n);
        for (int i = 0; i < n; ++i)
        {
            string s;
            cin >> s;
            a[i] = calc(s);
        }
        Hash<mod1> A(a);
        Hash<mod2> B(a);
        auto check = [&](int k, int l)
        {
            return (A.calc(0, l - 2 * k - 1) + A.calc(2 * k, l - 1)) % mod1 == 2 * A.calc(k, l - 1 - k) % mod1 &&
                   (B.calc(0, l - 2 * k - 1) + B.calc(2 * k, l - 1)) % mod2 == 2 * B.calc(k, l - 1 - k) % mod2;
        };
        answer.resize(n + 1);
        // for (int i = 0; i < n; ++i)
        //     cout << a[i] << ' ';
        // cout << '\n';
        for (int k = 1; k <= (n - 1) / 2; ++k)
        {
            int l = 2 * k + 1, r = n;
            while (l <= r)
            {
                int mid = (l + r) >> 1;
                if (check(k, mid))
                    l = mid + 1;
                else
                    r = mid - 1;
            }
            answer[2 * k]++;
            answer[r]--;
        }
        for (int i = 1; i < n; ++i)
            answer[i] += answer[i - 1];
        for (int i = 0; i < n; ++i)
            cout << !!answer[i];
        cout << '\n';
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