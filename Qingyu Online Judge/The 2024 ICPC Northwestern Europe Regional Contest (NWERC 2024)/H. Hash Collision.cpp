#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 3e5 + 5;

inline int query(int c, int r)
{
    cout << "? " << c << " " << r << endl;
    int h;
    cin >> h;
    return h;
}

inline void getFinalAnswer(int c, int cycleSize)
{
    int want = c % cycleSize;
    if (want == 0)
    {
        cout << "! " << c << ' ' << c << '\n';
        return;
    }
    int r = query(cycleSize - want, c);
    cout << "! " << c << ' ' << r << '\n';
    return;
}
inline void _main()
{
    int n;
    cin >> n;
    const int h0 = query(n, 1);
    vector<int> cache(n + 1, -1);
    cache[h0] = 0;
    int lastValue = 0;
    for (int i = 1; i * i <= n; i++)
    {
        int v = query(i, h0);
        if (cache[v] != -1)
        {
            assert(v == h0);
            return getFinalAnswer(h0, i);
        }
        else
        {
            cache[v] = i;
            lastValue = i;
        }
    }
    for (int q = 2 * lastValue; true; q += lastValue)
    {
        int ask = min(q, n);
        int v = query(ask, h0);
        if (cache[v] == -1)
            continue;
        return getFinalAnswer(h0, ask - cache[v]);
    }
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int test = 1;
    //	cin >> test;
    while (test--)
        _main();
    return 0;
}