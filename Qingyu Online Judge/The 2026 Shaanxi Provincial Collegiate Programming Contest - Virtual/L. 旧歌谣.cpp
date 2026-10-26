#include <bits/stdc++.h>
using namespace std;

constexpr int N = int(1e6) + 5;
constexpr int M = 8;
int d[N], pw10[M];
const bool __init_d = []() -> bool
{
    for (int x = 1; x < N; ++x)
    {
        d[x] = d[x / 10] + 1;
    }
    pw10[0] = 1;
    for (int i = 1; i < M; ++i)
    {
        pw10[i] = pw10[i - 1] * 10;
    }
    return 1;
}();

struct Main
{
    void main()
    {
        int x;
        cin >> x;
        const int y = next(x);
        const int z = next(y);
        cout << (x - z) << "\n";
    }
    static int next(int x)
    {
        if (x <= 10)
            return x - 1;
        const int high = x / (pw10[d[x] - 1]);
        return high * (pw10[d[x] - 1]) - 1;
    }
};
signed main()
{
#ifndef LOCAL
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
#endif
    Main{}.main();
    return 0;
}
