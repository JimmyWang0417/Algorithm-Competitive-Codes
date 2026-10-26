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
namespace interactive
{
    auto getn()
    {
        int n;
        cin >> n;
        return n;
    }
    auto query(int m, int v)
    {
        cout << "? " << m << ' ' << v << endl;
        int x;
        cin >> x;
        return x;
    }
    auto answer(const vector<int> &a)
    {
        cout << '!';
        for (auto i : a)
            cout << ' ' << i;
        cout << endl;
    }
}
namespace local
{
    int n;
    vector<int> c;
    auto init()
    {
        cin >> n;
        c.resize(n);
        for (auto &i : c)
            cin >> i;
    }
    auto getn()
    {
        return n;
    }
    auto query(int m, int v)
    {
        vector<bool> vis(n);
        cerr << m << ' ' << v << endl;
        for (int i = 0; i < n; ++i)
            if (__builtin_parity(i & m))
                vis[i] = true;
        if (v != -1)
            vis[v] = vis[v] ^ 1;
        int res = 0;
        for (int i = 0; i < n - 1; ++i)
            if (vis[c[i]] != vis[c[i + 1]])
                ++res;
        return res % 3;
    }
    auto answer(const vector<int> &a)
    {
        cerr << ((a == c) ? "YES\n" : "NO\n") << endl;
    }
}
using namespace interactive;
struct Main
{
    int n, m;
    int L, R;
    vector<int> a;
    vector<vector<int>> b;
    vector<int> c;
    Main()
    {
        n = getn();
        if (n == 1)
        {
            answer({0});
            return;
        }
        m = (int)ceil(log2(n));
        a.resize(m);
        b.resize(m, vector<int>(n));
        vector<bool> vis(n);
        for (int i = 0; i < m; ++i)
        {
            a[i] = query(1 << i, -1);
            // b[i][0] = query(1 << i, 0);
            b[i][0] = 2 * (n - 1) + (n - 4) * a[i];
            for (int j = 1; j < n; ++j)
            {
                b[i][j] = query(1 << i, j);
                b[i][0] -= b[i][j];
            }
            b[i][0] = (b[i][0] % 3 + 3) % 3;
            for (int j = 0; j < n; ++j)
                b[i][j] = (b[i][j] - a[i] + 3) % 3;
            for (int j = 0; j < n; ++j)
                if (b[i][j] == 0)
                    vis[j] = true;
        }
        L = -1, R = -1;
        for (int i = 0; i < n; ++i)
        {
            if (vis[i])
                continue;
            if (L == -1)
                L = i;
            else
                R = i;
        }
        c.resize(n);
        c[0] = L;
        for (int i = 0; i < n; ++i)
        {
            if (!i)
            {
                int x = 0;
                for (int j = 0; j < m; ++j)
                    x |= (b[j][c[i]] == 2) << j;
                c[i + 1] = c[i] ^ x;
            }
            else if (i < n - 1)
            {
                int x = 0;
                for (int j = 0; j < m; ++j)
                    x |= (b[j][c[i]] == 0) << j;
                c[i + 1] = c[i - 1] ^ x;
            }
            else
            {
                int x = 0;
                for (int j = 0; j < m; ++j)
                    x |= (b[j][c[i]] == 2) << j;
                assert((c[i - 1] ^ x) == c[i]);
            }
        }
        assert(c[n - 1] == R);
        answer(c);
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    // local::init();
    while (T--)
        Main();
    return 0;
}
