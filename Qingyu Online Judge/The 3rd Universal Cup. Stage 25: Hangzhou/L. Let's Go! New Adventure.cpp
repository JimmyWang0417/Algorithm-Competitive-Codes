#include <bits/stdc++.h>
typedef long long ll;
typedef unsigned long long ull;
using namespace std;
typedef pair<long double, ll> node;
constexpr int N = 5e5 + 5;
int n, m, c;
ll a[N], b[N];
ll dp[N];
inline node operator + (const node &lhs, const node &rhs)
{
    return node(lhs.first + rhs.first, lhs.second + rhs.second);
}
pair<int, int> q[N];
int head, tail;
inline void _main()
{
    cin >> n >> m >> c;
    for (int i = 1; i <= n; ++i)
    {
        cin >> a[i];
        a[i] += a[i - 1];
    }
    for (int i = 1; i <= m; ++i)
    {
        cin >> b[i];
        b[i] += b[i - 1];
    }
    b[m + 1] = (ll)1e12 + b[m];
    auto W = [&](int i, int j)
    {
        int pos = (int)(upper_bound(b, b + 1 + m, a[j] - a[i]) - b - 1);
        return dp[i] + pos - c + (long double)(a[j] - a[i] - b[pos]) / (b[pos + 1] - b[pos]);
    };
    auto calc = [](int i, int j)
    {
        return dp[i] + (int)(upper_bound(b, b + 1 + m, a[j] - a[i]) - b - 1) - c;
    };
    q[head = tail = 1] = make_pair(0, 0);
    for (int i = 1; i <= n; ++i)
    {
        while (head < tail && q[head + 1].first <= i)
            ++head;
        dp[i] = calc(q[head].second, i);
        while (head <= tail && q[tail].first >= i && W(i, q[tail].first) >= W(q[tail].second, q[tail].first))
            --tail;
        if (head <= tail)
        {
            int l = max(q[tail].first, i), r = n;
            while (l <= r)
            {
                int mid = (l + r) >> 1;
                if (W(i, mid) >= W(q[tail].second, mid))
                    r = mid - 1;
                else
                    l = mid + 1;
            }
            if (l <= n)
                q[++tail] = make_pair(l, i);
        }
        else
            q[++tail] = make_pair(i, i);
    }
    cout << dp[n] << '\n';
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