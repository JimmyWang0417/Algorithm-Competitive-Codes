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
struct Main
{
    Main()
    {
        int n;
        cin >> n;
        vector<tuple<i64, int, int, int>> a(n);
        {
            map<int, i64> mp;
            mp[-1e9] = mp[1e9] = 0;
            for (auto &[y, l, r, h] : a)
            {
                cin >> l >> r >> h;
                {
                    auto it = prev(mp.upper_bound(l));
                    while (it->first < r)
                    {
                        y = max(y, it->second);
                        ++it;
                    }
                    it = mp.lower_bound(l);
                    i64 las = prev(it)->second;
                    while (it->first <= r)
                    {
                        las = it->second;
                        it = mp.erase(it);
                    }
                    mp[l] = y + h, mp[r] = las;
                }
            }
        }
        sort(a.begin(), a.end());
        int ans = 0;
        {
            map<int, i64> mp;
            mp[-1e9] = mp[1e9] = 0;
            for (auto [y, l, r, h] : a)
            {
                --ans;
                auto it = prev(mp.lower_bound(l));
                bool stick = false;
                while (it->first <= r)
                {
                    if (it->second >= y)
                    {
                        if (!stick)
                            ++ans;
                        stick = 1;
                    }
                    else
                        stick = 0;
                    ++it;
                }
                it = mp.lower_bound(l);
                i64 las = prev(it)->second;
                while (it->first <= r)
                {
                    las = it->second;
                    it = mp.erase(it);
                }
                mp[l] = y + h, mp[r] = las;
            }
        }
        cout << ans << '\n';
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
