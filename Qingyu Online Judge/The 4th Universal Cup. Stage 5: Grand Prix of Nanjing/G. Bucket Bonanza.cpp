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
    int n;
    vector<pair<i64, int>> a;
    Main()
    {
        cin >> n;
        a.resize(n);
        i64 sumv = 0, suml = 0;
        for (int i = 0; i < n; ++i)
            cin >> a[i].first;
        for (int i = 0; i < n; ++i)
            cin >> a[i].second;
        set<pair<i64, int>> qv;
        set<pair<int, int>> ql;
        for (int i = 0; i < n; ++i)
        {
            sumv += a[i].first, suml += a[i].second;
            qv.emplace(a[i].first, i);
            ql.emplace(a[i].second, i);
        }
        vector<tuple<i64, i64, i64>> p;
        i64 V = sumv, L = suml; 
        while (!qv.empty())
        {
            int x = qv.begin()->second, y = ql.rbegin()->second;
            i64 curt = a[y].second ? (a[x].first - 1) / a[y].second + 1 : LONG_LONG_MAX;
            if (x == y)
            {
                qv.erase(make_pair(a[x].first, x));
                ql.erase(make_pair(a[x].second, x));
                sumv -= a[x].first, suml -= a[x].second;
            }
            else
            {
                qv.erase(make_pair(a[x].first, x));
                qv.erase(make_pair(a[y].first, y));
                ql.erase(make_pair(a[x].second, x));
                ql.erase(make_pair(a[y].second, y));
                sumv -= a[x].first + a[y].first;
                suml -= a[x].second + a[y].second;
                a[x].first = max(a[x].first, a[y].first);
                a[x].second = min(a[x].second, a[y].second);
                sumv += a[x].first, suml += a[x].second;
                qv.emplace(a[x].first, x);
                ql.emplace(a[x].second, x);
            }
            p.emplace_back(curt, sumv, suml);
        }
        int q;
        cin >> q;
        vector<pair<int, int>> que(q);
        vector<i64> answer(q);
        for (int i = 0; i < q; ++i)
        {
            cin >> que[i].first;
            que[i].second = i;
        }
        sort(que.begin(), que.end());
        
        for (int i = 0, j = 0; i < q; ++i)
        {
            auto [t, id] = que[i];
            while (j < (int)p.size() && get<0>(p[j]) <= t)
            {
                V = get<1>(p[j]), L = get<2>(p[j]);
                ++j;
            }
            answer[id] = max(V - L * t, (i64)0);
        }
        for (int i = 0; i < q; ++i)
            cout << answer[i] << ' ';
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
