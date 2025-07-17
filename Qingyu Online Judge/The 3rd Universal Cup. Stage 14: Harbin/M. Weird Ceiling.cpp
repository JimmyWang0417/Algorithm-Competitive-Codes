#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
typedef long long ll;
constexpr int N = 1e5 + 5;
int p[N], tot;
inline void work()
{
    int n;
    cin >> n;
    tot = 0;
    int x = n;
    for (int i = 1; i * i <= x; ++i)
        if (x % i == 0)
        {
            p[++tot] = i;
            if (i * i != n)
                p[++tot] = n / i;
        }
    sort(p + 1, p + 1 + tot);
    p[tot + 1] = n + 1;
    ll ans = 0;
    for (int i = tot; i >= 1; --i)
    {
        int cnt = p[i + 1] - p[i];
        ans += (ll)cnt * (n / p[i]);
    }
    cout << ans << '\n';
}
signed main()
{
    //	freopen("project.in", "r", stdin);
    //	freopen("project.out", "w", stdout);
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        work();
    return 0;
}