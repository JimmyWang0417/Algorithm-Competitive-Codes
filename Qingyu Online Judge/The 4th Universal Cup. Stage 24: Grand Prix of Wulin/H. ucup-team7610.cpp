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
    Main()
    {
        string s;
        cin >> s;
        if (s.substr(0, 9) == "ucup-team")
        {
            string t = s.substr(9);
            auto check = [&]()
            {
                for (auto c : t)
                    if (!isdigit(c))
                        return false;
                return true;
            };
            if (!t.empty() && check() && t[0] != '0' && t.length() >= 3)
            {
                cout << "YES\n";
                return;
            }
        }
        cout << "NO\n";
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
