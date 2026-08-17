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
template <typename T = int>
constexpr auto quickpow(i64 a, T b = mod - 2)
{
    i64 res = 1;
    while (b)
    {
        if (b & 1)
            (res *= a) %= mod;
        (a *= a) %= mod;
        b >>= 1;
    }
    return res;
}
template <typename T, typename Cmp>
struct sparse
{
    Cmp cmp;
    vector<vector<int>> dp;
    sparse() = default;
    sparse(const vector<T> &a) : dp(__lg(max((int)a.size(), 1)) + 1, a)
    {
        for (int j = 0; j + 1 < (int)dp.size(); ++j)
            for (int i = 0; i + (2 << j) - 1 < (int)a.size(); ++i)
                dp[j + 1][i] = min(dp[j][i], dp[j][i + (1 << j)], cmp);
    }
    auto query(int l, int r)
    {
        int k = __lg(r - l + 1);
        return min(dp[k][l], dp[k][r - (1 << k) + 1], cmp);
    }
};
struct Main
{
    int n, m, q;
    vector<int> a;
    vector<int> X, Y;
    vector<int> gl, gr;
    vector<int> bad;
    vector<int> L, R;
    Main()
    {
        cin >> n >> q;
        a.resize(n);
        for (int i = 0; i < n; ++i)
        {
            cin >> a[i];
            if (a[i] != -1)
                X.push_back(i), Y.push_back(a[i]);
        }
        m = (int)X.size();
        gl.resize(m), gr.resize(m);
        bad.resize(m);
        for (int i = 0; i < m; ++i)
            gl[i] = i - 1 >= 0 && Y[i - 1] >= Y[i] ? gl[i - 1] : i;
        for (int i = m - 1; i >= 0; --i)
            gr[i] = i + 1 < m && Y[i] >= Y[i + 1] ? gr[i + 1] : i;
        for (int i = 1; i < m; ++i)
            bad[i] = bad[i - 1] +
                     (Y[i - 1] >= Y[i] &&
                      X[i - 1] + Y[i - 1] != X[i] + Y[i]);
        L.resize(m, INT_MIN), R.resize(m, INT_MAX);
        for (int i = 0; i < m; ++i)
        {
            if (gl[i] - 1 >= 0)
            {
                int u = gl[i] - 1;
                L[i] = X[u] - Y[i] + 2;
                int v = (int)(partition_point(Y.begin() + gl[u], Y.begin() + u + 1,
                                              [&](auto val)
                                              { return val >= Y[i]; }) -
                              Y.begin() - 1);
                if (v >= gl[u])
                    L[i] = max(L[i], X[v] + 1);
            }
            if (gr[i] + 1 < m)
                R[i] = X[gr[i] + 1] - Y[i];
        }
        // for (int t = 0; t < m; ++t)
        //     cout << L[t] << ' ';
        // cout << '\n';
        // for (int t = 0; t < m; ++t)
        //     cout << R[t] << ' ';
        // cout << '\n';
        // for (int t = 0; t < m; ++t)
        //     cout << gl[t] << ' ';
        // cout << '\n';
        // for (int t = 0; t < m; ++t)
        //     cout << gr[t] << ' ';
        // cout << '\n';
        sparse<int, greater<int>> maxY(Y), maxL(L);
        sparse<int, less<int>> minR(R);
        while (q--)
        {
            int l, r;
            cin >> l >> r;
            --l, --r;
            int s = (int)(ranges::lower_bound(X, l) - X.begin());
            int e = (int)(ranges::upper_bound(X, r) - X.begin() - 1);
            if (s > e ||
                (bad[s] == bad[e] &&
                 maxY.query(s, e) <= r - l + 1 &&
                 maxL.query(s, e) <= l &&
                 (gl[e] <= s || minR.query(s, gl[e] - 1) >= l)))
                cout << "YES\n";
            else
                cout << "NO\n";
        }
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        Main();
    return 0;
}

