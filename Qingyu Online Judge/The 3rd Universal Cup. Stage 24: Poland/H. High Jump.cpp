#include <bits/stdc++.h>
typedef long long ll;
using namespace std;
constexpr int N = 5e5 + 5;
int n;
double p[N], dp[N];
pair<int, int> st[N];
int top;
inline void _main()
{
    cin >> n;
    for (int i = 1; i <= n; ++i)
        cin >> p[i];
    auto W = [](int i, int j)
    {
        return p[i] * (i * (1 - p[j]) + dp[j]);
    };
    auto calc = [](int x)
    {
        int l = 1, r = top;
        while (l <= r)
        {
            int mid = (l + r) >> 1;
            if (st[mid].first >= x)
                l = mid + 1;
            else
                r = mid - 1;
        }
        return st[r].second;
    };
    p[0] = 1;
    dp[n] = p[n] * n;
    // for (int i = n - 1; i >= 0; --i)
    // {
    //     dp[i] = 0;
    //     for (int j = i + 1; j <= n; ++j)
    //         dp[i] = max(dp[i], W(i, j));
    // }
    // for (int i = 1; i <= n; ++i)
    //     cout << dp[i] << ' ';
    // cout << '\n';
    // cout << dp[0] << '\n';
    for (int i = n; i >= 1; --i)
    {
        while (top >= 1 && W(st[top].first, st[top].second) < W(st[top].first, i))
            --top;
        if (top >= 1)
        {
            int l = 0, r = st[top].first;
            while (l <= r)
            {
                int mid = (l + r) >> 1;
                if (W(mid, st[top].second) < W(mid, i))
                    l = mid + 1;
                else
                    r = mid - 1;
            }
            if (r != -1)
                st[++top] = make_pair(r, i);
        }
        else
            st[top = 1] = make_pair(n, i);
        dp[i - 1] = W(i - 1, calc(i - 1));
    }
    cout << fixed << setprecision(9) << dp[0] << '\n';
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        _main();
    return 0;
}