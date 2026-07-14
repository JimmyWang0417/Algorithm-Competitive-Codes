#include <bits/stdc++.h>
#include <cassert>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef __float80 f80;
typedef __float128 f128;
struct Main
{
    int n;
    vector<int> a;
    constexpr bool check(const vector<int> &p)
    {
        for (int i = 1; i < n; ++i)
            if (p[i] != i)
                return false;
        return true;
    }
    Main()
    {
        cin >> n;
        a.resize(n + 5);
        for (int i = 1; i < n; ++i)
            cin >> a[i];
        if (check(a))
        {
            cout << 0 << '\n';
            return;
        }
        for (int i = 1; i < n; ++i)
        {
            if (i != a[i])
            {
                map<int, int> mp;
                int j = i;
                while (j < n && j != a[j])
                {
                    mp[a[j]] = j;
                    ++j;
                }
                if (mp.find(i) != mp.end())
                {
                    rotate(a.begin() + i, a.begin() + mp[i], a.begin() + j);
                    if (check(a))
                    {
                        cout << 1 << '\n';
                        return;
                    }
                }
                break;
            }
        }
        cout << 2 << '\n';
    }
};
signed main()
{
    // freopen("project.in", "r", stdin);
    // freopen("project.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        Main();
    return 0;
}