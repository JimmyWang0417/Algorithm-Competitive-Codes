#include <bits/stdc++.h>
#include <cassert>
using namespace std;

// #define LOCAL
#ifdef LOCAL
#define dbg(...) fprintf(stderr, ##__VA_ARGS__)
#else
#define dbg(...) 42
#endif

#define all(x) (x).begin(),(x).end()
#define allr(x) (x).rbegin(),(x).rend()

using LL = long long;

struct Main
{
    int n, m;
    vector<int> b, keep;
    void main()
    {
        cin >> n >> m;
        b.assign(n, 0);
        for (auto &x : b)
        {
            cin >> x;
            --x;
        }
        keep.assign(m, 0);
        int base = 0;
        for (int i = 0, j = 0; i < n; ++i)
        {
            if (b[i] >= m)
                ++base;
            else
            {
                int x = b[i] - j;
                if (x < 0)
                    x += m;
                assert(0 <= x && x < m);
                ++keep[x];
            }
            if (++j == m)
                j = 0;
        }
        cout << (n - *max_element(all(keep))) << "\n";
    }
};
signed main()
{
#ifndef LOCAL
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
#endif
    int t;
    cin >> t;
    while (t--)
        Main{}.main();
    return 0;
}
