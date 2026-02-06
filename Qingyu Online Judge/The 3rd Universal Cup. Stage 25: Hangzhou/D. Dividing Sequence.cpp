#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef __float80 f80;
typedef __float128 f128;
constexpr int mod = 1e9 + 7;
mt19937 rnd((random_device())());
struct lyndon
{
    auto duval(const basic_string<int> &s)
    {
        vector<basic_string<int>> ans;
        for (int i = 0, j, k; i < (int)s.size();)
        {
            j = i, k = i + 1;
            while (k < (int)s.size() && s[j] <= s[k])
            {
                if (s[j] < s[k])
                    j = i;
                else
                    ++j;
                ++k;
            }
            while (i <= j)
            {
                ans.emplace_back(s.substr(i, k - j));
                i += k - j;
            }
        }
        return ans;
    }
};
struct Main
{
    Main()
    {
        int n;
        cin >> n;
        basic_string<int> s;
        s.resize(n);
        for (int &i : s)
            cin >> i;
        auto t = lyndon().duval(s);
        basic_string<int> b, c;
        for (int i = 0; i < (int)t.size(); i += 2)
        {
            if (i + 1 < (int)t.size())
            {
                if (t[i] == t[i + 1])
                {
                    c += t[i];
                    b += t[i + 1];
                }
                else
                {
                    c += t[i];
                    for (int j = i + 1; j < (int)t.size(); ++j)
                        b += t[j];
                    break;
                }
            }
            else
                c += t[i];
        }
        cout << c.size() << '\n';
        for (int i : c)
            cout << i << ' ';
        cout << '\n';
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        Main();
    return 0;
}