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
constexpr int base = 23;
struct Main1
{
    int n, m;
    vector<int> p, q;
    Main1()
    {
        cin >> n >> m;
        p.resize(2 * m + 5);
        for (int i = 1; i <= m; ++i)
            p[i] = p[i + m] = i;
        q = p;
        for (int i = 2; i <= m; ++i)
        {
            if (m % i == 0)
            {
                rotate(q.begin() + m - m / i + 1, q.begin() + m - m / i + 2, q.begin() + m + 1);
                break;
            }
        }
        for (int i = 1; i <= m; ++i)
            q[i + m] = q[i];

        for (int i = 1; i <= n; ++i)
        {
            int x;
            cin >> x;
            for (int j = 1; j <= m; ++j)
                cout << j << ' ';
            for (int j = 0; j < m; ++j)
                cout << p[j + x] << ' ';
            for (int j = 0; j < m; ++j)
                cout << q[j + x] << ' ';
            cout << '\n';
        }
    }
};
struct Main2
{
    int n, m;
    vector<int> p, q;
    vector<i64> hashp, hashq, power;
    Main2()
    {
        cin >> n >> m;
        while (n--)
        {
            p.resize(m * 2 + 5);
            for (int i = 1; i <= m; ++i)
            {
                cin >> p[i];
                p[i + m] = p[i];
            }
            q = p;
            for (int i = 2; i <= m; ++i)
            {
                if (m % i == 0)
                {
                    rotate(q.begin() + m - m / i + 1, q.begin() + m - m / i + 2, q.begin() + m + 1);
                    break;
                }
            }
            for (int i = 1; i <= m; ++i)
                q[i + m] = q[i];

            hashp.resize(2 * m + 5);
            hashq.resize(2 * m + 5);
            power.resize(2 * m + 5);
            power[0] = 1;
            map<pair<i64, i64>, int> mp;
            for (int i = 1; i <= 2 * m; ++i)
            {
                power[i] = power[i - 1] * base % mod;
                hashp[i] = (hashp[i - 1] * base + p[i]) % mod;
                hashq[i] = (hashq[i - 1] * base + q[i]) % mod;
            }
            for (int i = 1; i <= m; ++i)
            {
                auto x = ((hashp[i + m - 1] - hashp[i - 1] * power[m]) % mod + mod) % mod;
                auto y = ((hashq[i + m - 1] - hashq[i - 1] * power[m]) % mod + mod) % mod;
                mp[{x, y}] = i;
            }
            i64 x = 0, y = 0;
            for (int j = m + 1; j <= 2 * m; ++j)
            {
                int _;
                cin >> _;
                x = (x * base + _) % mod;
            }
            for (int j = 2 * m + 1; j <= 3 * m; ++j)
            {
                int _;
                cin >> _;
                y = (y * base + _) % mod;
            }
            cout << mp[{x, y}] << '\n';
        }
    }
};
struct Main3
{
    int n;
    Main3()
    {
        cin >> n;
        vector<int> p(n);
        iota(p.begin(), p.end(), 1);
        // p = {1, 2, 4, 3, 5, 6, 10, 9, 8, 7};
        auto check = [&]()
        {
            for (int S = 1; S < (1 << n) - 1; ++S)
            {
                set<vector<bool>> se;
                for (int i = 1; i <= n; ++i)
                {
                    vector<bool> a;
                    for (int j = 1; j <= n; ++j)
                    {
                        a.push_back((S >> (j - 1)) & 1);
                    }
                    for (int j = 1, k = i; j <= n; ++j, k = k % n + 1)
                        a.push_back((S >> (k - 1)) & 1);
                    for (int j = 1, k = i - 1; j <= n; ++j, k = (k + 1) % n)
                        a.push_back((S >> (p[k] - 1)) & 1);
                    if (se.find(a) != se.end())
                        return false;
                    se.insert(a);
                }
            }
            return true;
        };
        do
        {
            if (check())
            {
                for (auto i : p)
                    cout << i << ' ';
                cout << endl;
                break;
            }
        } while (next_permutation(p.begin(), p.end()));
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int op;
    cin >> op;
    if (op == 1)
        Main1();
    else
        Main2();
    return 0;
}
