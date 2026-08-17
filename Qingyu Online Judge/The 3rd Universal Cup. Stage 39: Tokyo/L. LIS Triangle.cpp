#include <bits/stdc++.h>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef __float128 f128;
constexpr int N = 2e5 + 5;
auto _main()
{
    int n, k, l;
    cin >> n >> k >> l;
    if (k == 1)
        cout << "No\n";
    else
    {
        vector<int> p, q;
        for (int i = n - 1; i >= 1;)
        {
            if ((int)p.size() < l - 1)
                p.push_back(k + --i);
            if ((int)q.size() < n - l)
                q.push_back(k + --i);
        }
        if (k == 2 && n % 2 == 1 && (n + 1) / 2 == l && n >= 5)
        {
            if (n == 5)
            {
                p.pop_back(), p.pop_back();
                q.pop_back(), q.pop_back();
                p.push_back(5), p.push_back(2);
                q.push_back(4), q.push_back(3);
            }
            else
            {
                p.pop_back(), p.pop_back(), p.pop_back();
                q.pop_back(), q.pop_back(), q.pop_back();
                p.push_back(7), p.push_back(6), p.push_back(2);
                q.push_back(5), q.push_back(4), q.push_back(3);
            }
        }
        else if (k == 2 && n % 2 == 0 && n / 2 == l && n >= 4)
        {
            if (n == 4)
            {
                p.pop_back();
                q.pop_back(), q.pop_back();
                p.push_back(3);
                q.push_back(4), q.push_back(2);
            }
            else
            {
                p.pop_back(), p.pop_back();
                q.pop_back(), q.pop_back();
                p.push_back(6), p.push_back(3);
                q.push_back(4), q.push_back(2);
            }
        }
        else if (k == 2 && n % 2 == 1 && (n + 1) / 2 == l - 1 && n >= 5)
        {
                p.pop_back(), p.pop_back();
                q.pop_back();
                p.push_back(4), p.push_back(2);
                q.push_back(3);
        }
        else if (k == 2 && n % 2 == 0 && n / 2 == l - 1 && n >= 6)
        {
            p.pop_back(), p.pop_back(), p.pop_back();
            q.pop_back(), q.pop_back();
            p.push_back(5), p.push_back(4), p.push_back(2);
            q.push_back(6), q.push_back(3);
        }
        reverse(p.begin(), p.end());
        cout << "Yes\n";
        for (auto i : p)
            cout << i << ' ';
        cout << n + k - 1 << ' ';
        for (auto i : q)
            cout << i << ' ';
        cout << '\n';
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        _main();
    return 0;
}
