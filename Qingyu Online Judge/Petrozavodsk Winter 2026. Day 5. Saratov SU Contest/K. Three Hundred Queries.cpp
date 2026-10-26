#include <bits/stdc++.h>
using namespace std;

// #define LOCAL
#ifdef LOCAL
#define dbg(...) fprintf(stderr, ##__VA_ARGS__)
#else
#define dbg(...) 42
#endif

using LL = long long;

template <class S>
inline bool updmn(S &x, const S y)
{
    if (y < x)
    {
        x = y;
        return 1;
    }
    return 0;
}
template <class S>
inline bool updmx(S &x, const S y)
{
    if (x < y)
    {
        x = y;
        return 1;
    }
    return 0;
}

mt19937 rnd(114514);
struct Main
{
    constexpr static int mod = 1e9;
    auto query(int x)
    {
        cout << "? " << x << endl;
        int y;
        cin >> y;
        return y;
    }
    auto answer(int a, int b, int c)
    {
        cout << "! " << a << ' ' << b << ' ' << c << endl;
    }
    set<int> se;
    auto solve(int x)
    {
        int d = query(x);
        int d1 = query((x + 1) % mod);
        if (d1 == d - 1)
        {
            (x += d) %= mod;
            se.insert(query(x));
        }
        else if (d1 == d + 1)
        {
            (x += mod - d) %= mod;
            se.insert(query(x));
        }
        else
            query(x);
    }
    void main()
    {
        for (int i = 1; i <= 100; ++i)
        {
            int x = uniform_int_distribution<int>(0, mod - 1)(rnd);
            solve(x);
        }
        if (se.size() == 1)
        {
            int x = *se.begin();
            answer(x, x, mod - 2 * x);
        }
        else
        {
            int x = *se.begin(), y = *se.rbegin();
            answer(x, y, mod - x - y);
        }
    }
};

int main()
{
#ifndef LOCAL
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    int t;
    cin >> t;
    while (t--)
        Main{}.main();
    return 0;
}
