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

struct Main
{
    int n;
    auto query(int l, int r)
    {
        cout << "? " << l << ' ' << r << endl;
        int x;
        cin >> x;
        return x;
    }
    auto answer(bool ok)
    {
        if (ok)
        {
            cout << "YES ";
            cout << 0;
            for (int i = 2; i < n; ++i)
                cout << 1;
            cout << "0\n";
        }
        else
            cout << "NO\n";
        cout.flush();
        int x;
        cin >> x;
        return x;
    }
    void main()
    {
        cin >> n;
        if (n == 3)
        {
            if (!answer(!(query(1, 3) == 2)))
                exit(0);
        }
        else
        {
            if (!answer(!(query(2, n - 1) == 1 && query(1, n - 1) == 2 && query(2, n) == 2)))
                exit(0);
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
