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
struct Main
{
    int n;
    vector<int> a, b;
    vector<int> fa;
    auto find(int x) -> int
    {
        return !fa[x] ? x : fa[x] = find(fa[x]);
    }
    auto check(int x, int y)
    {
        x = find(x), y = find(y);
        return x == y;
    }
    auto merge(int x, int y)
    {
        x = find(x), y = find(y);
        fa[x] = y;
    }
    Main()
    {
        cin >> n;
        a.resize(2 * n + 5);
        b.resize(n + 5);
        for (int i = 1; i <= 2 * n; ++i)
            cin >> a[i];
        fa.resize(2 * n + 5);
        for (int i = 1; i <= 2 * n; ++i)
        {
            if (b[a[i]])
                merge(b[a[i]], i);
            else
                b[a[i]] = i;
        }
        stack<int> st;
        st.push(1);
        vector<char> ans(2 * n + 1);
        ans[1] = '(';
        for (int i = 2; i <= 2 * n; ++i)
        {
            if ((check(i - 1, i) || st.empty()) && i < 2 * n)
            {
                st.push(i);
                ans[i] = '(';
            }
            else
            {
                merge(i - 1, i);
                ans[i] = ')';
                st.pop();
            }
        }
        for (int i = 1; i <= 2 * n; ++i)
            cout << ans[i];
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
