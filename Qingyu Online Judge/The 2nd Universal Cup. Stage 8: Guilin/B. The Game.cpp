#include <bits/stdc++.h>
#include <cassert>
using namespace std;

// #define LOCAL
#ifdef LOCAL
#define dbg(...) fprintf(stderr, ##__VA_ARGS__)
#else
#define dbg(...) 42
#endif

using LL = long long;
#define all(x) (x).begin(), (x).end()
#define allr(x) (x).rbegin(), (x).rend()

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

#define FAIL return void(cout << "-1\n")
struct Main
{
    int n, m;
    vector<int> a, b;
    multiset<int> a_sml, a_big;
    vector<int> ans;
    LL sum_b = 0, sum_a_big = 0;
    void main()
    {
        // read and sort
        cin >> n >> m;
        a.assign(n, 0);
        b.assign(m, 0);
        for (auto &x : a)
            cin >> x;
        for (auto &x : b)
            cin >> x;
        sort(allr(a));
        sort(allr(b));
#ifdef LOCAL
        dbg("a: ");
        for (int i = 0; i < int(a.size()); ++i)
            dbg("%d ", a[i]);
        dbg("\n");
        dbg("b: ");
        for (int i = 0; i < m; ++i)
            dbg("%d ", b[i]);
        dbg("\n");
#endif
        // trivial check
        {
            LL diff = 0;
            for (int i = 0; i < m; ++i)
            {
                if (a[i] > b[i])
                    FAIL;
                else
                    diff += b[i] - a[i];
            }
            if (diff > n - m)
                FAIL;
        }
        for (int i = 0; i < m; ++i)
            sum_b += b[i];
        for (int i = 0; i < m; ++i)
        {
            sum_a_big += a[i];
            a_big.insert(a[i]);
        }
        for (int i = m; i < n; ++i)
            a_sml.insert(a[i]);
        while (sum_b - sum_a_big < n - m)
        {
            int x = *a_sml.begin();
            a_sml.extract(x);
            ans.push_back(x++);
            const int y = *a_big.begin();
            if (x > y)
            {
                sum_a_big += x - y;
                a_big.extract(y);
                a_big.insert(x);
                a_sml.insert(y);
            }
            else
            {
                a_sml.insert(x);
            }
            a_sml.erase(a_sml.begin());
            --n;
        }
        a = {allr(a_big)};
        a.insert(a.end(), allr(a_sml));
        for (int i = 0; i < m; ++i)
        {
            if (a[i] > b[i])
                FAIL;
        }
        for (int i = 0; i < m; ++i)
        {
            while (a[i] < b[i])
            {
                ans.push_back(a[i]++);
                a.pop_back();
                if (int(a.size()) < m)
                    FAIL;
            }
        }
        if (a != b)
            FAIL;
        cout << ans.size() << "\n";
        for (auto x : ans)
            cout << x << " ";
        cout << "\n";
    }
};

signed main()
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
