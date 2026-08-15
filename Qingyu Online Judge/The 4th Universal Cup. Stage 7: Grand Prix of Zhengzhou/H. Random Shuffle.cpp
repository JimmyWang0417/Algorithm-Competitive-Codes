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
struct Main
{
    vector<i64> suf;
    vector<f80> p, q;
    vector<f80> dp;
    vector<pair<f80, int>> st;
    Main(int n, const vector<int> &a, const vector<int> &c)
    {
        suf.resize(n + 5);
        p.resize(n + 5);
        q.resize(n + 5);
        {
            vector<int> mp(*max_element(a.begin(), a.end()) + 1);
            for (int i = n; i >= 1; --i)
            {
                suf[i] = suf[i + 1] + c[i];
                p[i] = (f80)++mp[a[i]] / (n - i + 1);
            }
        }
        dp.resize(n + 5);
        int top = 0;
        st.resize(n + 5);
        st[++top] = {0, n + 1};
        for (int i = n; i >= 1; --i)
        {
            q[i] = p[i];
            while (top)
            {
                auto [pre, j] = st[top];
                auto res = (suf[i] - q[i] * pre) / (2 - q[i]);
                if (res >= dp[j])
                {
                    dp[i] = res;
                    break;
                }
                q[i] *= q[j];
                --top;
            }
            st[top + 1] = {st[top].first * q[i] + (1 - q[i]) * dp[i], i};
            ++top;
        }
        cout << fixed << setprecision(11) << dp[1] << '\n';
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int n;
    cin >> n;
    vector<int> a(n + 5), c(n + 5);
    for (int i = 1; i <= n; ++i)
        cin >> a[i];
    for (int i = 1; i <= n; ++i)
        cin >> c[i];
    Main(n, a, c);
    int T = 1;
    cin >> T;
    while (T--)
    {
        int _T;
        cin >> _T;
        while (_T--)
        {
            int p, x, y;
            cin >> p >> x >> y;
            a[p] = x, c[p] = y;
        }
        Main(n, a, c);
    }
    return 0;
}

