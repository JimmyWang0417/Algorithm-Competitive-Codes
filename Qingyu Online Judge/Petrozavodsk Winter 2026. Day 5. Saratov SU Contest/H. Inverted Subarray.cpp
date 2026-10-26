#include <bits/stdc++.h>
using namespace std;

// #define LOCAL
#ifdef LOCAL
#define dbg(...) fprintf(stderr, ##__VA_ARGS__)
#else
#define dbg(...) 42
#endif

using LL = long long;

template <class S>
inline bool updmn(S &x, const S y)
{
    if (y < x)
    {
        x = y;
        return 1;
    }
    return 0;
}
template <class S>
inline bool updmx(S &x, const S y)
{
    if (x < y)
    {
        x = y;
        return 1;
    }
    return 0;
}

struct Main
{
    int n;
    vector<int> a, L, R;
    void main()
    {
        cin >> n;
        a.assign(n + 1, 0);
        for (int i = 1; i <= n; ++i)
            cin >> a[i];
        vector<int> stk;
        stk.reserve(n);
        stk.push_back(1);
        L.assign(n + 1, 0);
        L[1] = 1;
        for (int i = 2; i <= n; ++i)
        {
            while (stk.size() && a[stk.back()] < a[i])
                stk.pop_back();
            L[i] = stk.empty() ? i : stk.back();
            stk.push_back(i);
        }
        stk.clear();
        stk.push_back(n);
        R.assign(n + 1, 0);
        R[n] = n;
        for (int i = n - 1; i > 0; --i)
        {
            while (stk.size() && a[stk.back()] > a[i])
                stk.pop_back();
            R[i] = stk.empty() ? i : stk.back();
            stk.push_back(i);
        }
#ifdef LOCAL
        for (int i = 1; i <= n; ++i)
        {
            dbg("i = %d [%d, %d]\n", i, L[i], R[i]);
        }
        dbg("\n");
#endif
        int ans = 0, l = -1, r = -1;
        for (int i = 1; i <= n; ++i)
        {
            if (L[i] == R[i])
                continue;
            bool ok = 0;
            if (l <= L[i])
            {
                if (R[i] <= r)
                    ok = 1;
                if (L[i] <= r && r <= R[i])
                    ok = 1;
            }
            if (L[i] <= l)
            {
                if (r <= R[i])
                    ok = 1;
                if (l <= R[i] && R[i] <= r)
                    ok = 1;
            }
            if (R[i] + 1 == l)
                ok = 1;
            if (r + 1 == L[i])
                ok = 1;
            if (ok)
            {
                updmn(l, L[i]);
                updmx(r, R[i]);
            }
            else
            {
                l = L[i], r = R[i];
            }
            updmx(ans, r - l + 1);
        }
        cout << ans << "\n";
    }
};

int main()
{
#ifndef LOCAL
    cin.tie(nullptr)->sync_with_stdio(false);
#endif
    int t;
    cin >> t;
    while (t--)
        Main{}.main();
    return 0;
}
