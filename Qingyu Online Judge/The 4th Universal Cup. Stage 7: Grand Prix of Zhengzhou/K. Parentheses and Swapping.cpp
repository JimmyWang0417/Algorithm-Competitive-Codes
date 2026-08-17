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
vector<int> Log;
auto init(int n)
{
    Log.resize(n + 1);
    Log[0] = -1;
    for (int i = 1; i <= n; ++i)
        Log[i] = Log[i >> 1] + 1;
}
struct Main
{
    int n;
    vector<int> a;
    array<vector<pair<int, int>>, 20> dp[2];
    Main()
    {
        cin >> n;
        a.resize(n + 5);
        dp[0].fill(vector<pair<int, int>>(n + 5));
        dp[1].fill(vector<pair<int, int>>(n + 5));
        for (int i = 1; i <= n; ++i)
        {
            cin >> a[i];
            dp[i & 1][0][i] = {a[i], -i};
            dp[(i & 1) ^ 1][0][i] = {INT_MAX, -1};
        }
        for (int j = 0; j < Log[n]; ++j)
            for (int i = 1; i + (2 << j) - 1 <= n; ++i)
            {
                dp[0][j + 1][i] = min(dp[0][j][i], dp[0][j][i + (1 << j)]);
                dp[1][j + 1][i] = min(dp[1][j][i], dp[1][j][i + (1 << j)]);
            }
        auto calc = [](auto &f, int l, int r)
        {
            int k = Log[r - l + 1];
            return -min(f[k][l], f[k][r - (1 << k) + 1]).second;
        };
        stack<pair<int, int>> st;
        st.emplace(0, n + 1);
        for (int i = 1; i <= n; ++i)
        {
            if (i == st.top().second)
            {
                cout << ')';
                st.pop();
            }
            else
            {
                int pos = calc(dp[(i & 1) ^ 1], i + 1, st.top().second - 1);
                if (a[i] == a[st.top().second] && a[pos] >= a[st.top().first])
                {
                    cout << ')';
                    st.pop();
                }
                else
                {
                    cout << '(';
                    st.emplace(i, pos);
                }
            }
        }
        cout << '\n';
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    init(5e5);
    int T = 1;
    cin >> T;
    while (T--)
        Main();
    return 0;
}

