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
    vector<int> p;
    vector<int> f, g;
    i64 answer = 0;
    auto insertF(int x)
    {
        auto it = ranges::lower_bound(f, x);
        if (it == f.end())
        {
            f.push_back(x);
            answer += g.end() - ranges::upper_bound(g, x, greater<>());
        }
        else if (*it != x)
        {
            answer -= g.end() - ranges::upper_bound(g, *it, greater<>());
            *it = x;
            answer += g.end() - ranges::upper_bound(g, *it, greater<>());
        }
    }
    auto insertG(int x)
    {
        auto it = ranges::lower_bound(g, x, greater<>());
        if (it == g.end())
        {
            g.push_back(x);
            answer += f.end() - ranges::upper_bound(f, x);
        }
        else if (*it != x)
        {
            answer -= f.end() - ranges::upper_bound(f, *it);
            *it = x;
            answer += f.end() - ranges::upper_bound(f, *it);
        }
    }
    Main()
    {
        cin >> n;
        p.resize(n);
        for (int &i : p)
            cin >> i;
        for (int x : p)
        {
            insertF(x);
            insertG(x);
            cout << answer << ' ';
        }
        cout << '\n';
    }
};
signed main()
{
    // freopen("project.in", "r", stdin);
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        Main();
    return 0;
}
