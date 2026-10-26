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
constexpr int mod = 1e6 + 3;
template <typename T = int>
constexpr auto quickpow(i64 a, T b = mod - 2)
{
    a %= mod;
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
struct Main
{
    int n, m, leaf;
    vector<int> a;
    vector<int> L, R;
    auto check(int len) -> bool
    {
        vector<vector<int>> G(n);
        for (int i = 1; i <= m; ++i)
            if (L[i] != -1 && R[i] != -1)
                G[max(R[i] - len, 0)].emplace_back(i);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q;
        int rem = leaf;
        for (int i = 0, r = -1; i < n; ++i)
        {
            for (auto u : G[i])
                q.emplace(L[u] + len, u);
            if (a[i] == 0)
            {
                if (i <= r)
                    continue;
                while (!q.empty() && q.top().first < i)
                    q.pop();
                if (!q.empty())
                {
                    auto [u, v] = q.top();
                    q.pop();
                    r = min(u, i + len);
                }
                else
                {
                    if (!rem--)
                        return false;
                    r = i + len;
                }
            }
        }
        return true;
    }
    vector<int> b;
    auto calc(int len)
    {
        vector<vector<int>> G(n);
        vector<int> fuck;
        for (int i = 1; i <= m; ++i)
            if (L[i] != -1 && R[i] != -1)
                G[max(R[i] - len, 0)].emplace_back(i);
            else
                fuck.emplace_back(i);
        priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> q;
        for (int i = 0, r = -1, c = 0; i < n; ++i)
        {
            for (auto u : G[i])
                q.emplace(L[u] + len, u);
            if (a[i] == 0)
            {
                if (i <= r)
                {
                    b[i] = c;
                    continue;
                }
                while (!q.empty() && q.top().first < i)
                    q.pop();
                if (!q.empty())
                {
                    auto [u, v] = q.top();
                    q.pop();
                    r = min(u, i + len);
                    c = v;
                }
                else
                {
                    r = i + len;
                    c = fuck.back();
                    fuck.pop_back();
                }
                b[i] = c;
            }
            else
                b[i] = a[i];
        }
    }
    Main()
    {
        cin >> n >> m;
        a.resize(n);
        for (auto &i : a)
            cin >> i;
        L.resize(m + 1, -1);
        R.resize(m + 1, -1);
        for (int i = 0; i < n; ++i)
            if (L[a[i]] == -1)
                L[a[i]] = i;
        for (int i = n - 1; i >= 0; --i)
            if (R[a[i]] == -1)
                R[a[i]] = i;
        leaf = 0;
        int maxlen = 0;
        for (int i = 1; i <= m; ++i)
            if (L[i] != -1 && R[i] != -1)
                maxlen = max(maxlen, R[i] - L[i]);
            else
                ++leaf;
        int l = maxlen, r = n - 1;
        while (l <= r)
        {
            auto mid = (l + r) >> 1;
            if (check(mid))
                r = mid - 1;
            else
                l = mid + 1;
        }
        b.resize(n);
        calc(l);
        for (auto i : b)
            cout << i << ' ';
        cout << '\n';
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        Main();
    return 0;
}
