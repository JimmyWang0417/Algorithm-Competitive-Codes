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
    int n, m;
    vector<int> a, b, c;
    Main()
    {
        cin >> n >> m;
        a.resize(n);
        b.resize(m);
        c.resize(m);
        for (int i = 0; i < n; ++i)
            cin >> a[i];
        ranges::sort(a);
        a.erase(ranges::unique(a).begin(), a.end());
        for (int i = 0; i < m; ++i)
            cin >> b[i] >> c[i];
        for (int i = 0; i < m - 1; ++i)
            if (b[i] != 1 && b[i + 1] != 2)
            {
                cout << "Yes\n";
                return;
            }
        int pos = -1;
        for (int i = 0; i < m; ++i)
            if (!b[i])
            {
                pos = i;
                break;
            }
        auto mex = [&](int X, int Y)
        {
            int r = 0;
            while (r == X || r == Y)
                ++r;
            return r;
        };
        auto check = [&]()
        {
            if (b.front() == 2)
            {
                int g = 0;
                for (auto x : c)
                    g = __gcd(g, x);
                for (auto x : a)
                    if (__gcd(g, a.front()) != __gcd(g, x))
                        return false;
                return true;
            }

            vector<int> f = a;
            for (int i = 0; i < m; ++i)
            {
                vector<int> g;
                for (auto x : f)
                {
                    if (b[i] == 1)
                        x = mex(x, c[i]);
                    else
                        x = __gcd(x, c[i]);
                    if (!ranges::count(g, x))
                        g.push_back(x);
                }
                f.swap(g);
            }
            return f.size() == 1;
        };
        if (pos == -1)
        {
            if (check())
                cout << "Yes\n";
            else
                cout << "No\n";
        }
        else
        {
            b[pos] = 1;
            if (check())
                cout << "Yes\n";
            else
            {
                b[pos] = 2;
                if (check())
                    cout << "Yes\n";
                else
                    cout << "No\n";
            }
        }
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

