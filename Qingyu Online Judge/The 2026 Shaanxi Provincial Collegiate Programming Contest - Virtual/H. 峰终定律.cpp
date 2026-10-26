#include <bits/stdc++.h>
using namespace std;

// #define LOCAL
#ifdef LOCAL
#define dbg(...) fprintf(stderr, ##__VA_ARGS__)
#else
#define dbg(...) 42
#endif

#define all(x) (x).begin(), (x).end()
#define allr(x) (x).rbegin(), (x).rend()
using LL = long long;
using ai2 = array<int, 2>;

struct Main
{
    int n, m;
    LL ans = 0;
    vector<int> a, opt;
    void main()
    {
        read();
        work();
        cout << ans << "\n";
        for (int i = 0; i < n; ++i)
            cout << opt[i] << " \n"[i + 1 == n];
    }
    void read()
    {
        cin >> n >> m;
        a.assign(n, 0);
        for (auto &x : a)
            cin >> x;
    }
    void work_only_one_segment()
    {
        ans = *max_element(a.begin(), a.end() - 1) + a[n - 1];
        opt.assign(n, 1);
    }
    void work()
    {
        vector<int> idx(n);
        iota(all(idx), 0);
        sort(all(idx), [&](const int x, const int y) -> bool
             {
            if(a[x]==a[y]) return x>y;
            return a[x]>a[y]; });
        vector<int> pos{n - 1};
        pos.reserve(m * 2);
        {
            int rest = m * 2 - 1;
            for (auto i : idx)
            {
                if (i == n - 1)
                    continue;
                if (a[i] < 0)
                    break;
                pos.push_back(i);
                if (--rest == 0)
                    break;
            }
        }
        sort(allr(pos));
#ifdef LOCAL
        dbg("* pos: ");
        for (auto p : pos)
            dbg("%d ", p);
        dbg("\n");
#endif
        if (pos.size() == 1)
        {
            work_only_one_segment();
            return;
        }
        opt.assign(n, 0);
        int col = 0;
        if (pos.size() & 1)
        {
            const int p = pos.back();
            pos.pop_back();
            opt[p] = ++col;
            ans += a[p];
        }
        while (pos.size())
        {
            const int x = pos.back();
            pos.pop_back();
            const int y = pos.back();
            pos.pop_back();
            ++col;
            opt[x] = opt[y] = col;
            ans += a[x] + a[y];
        }
        for (auto &c : opt)
            if (!c)
                c = col;
        return;
    }
};
signed main()
{
#ifndef LOCAL
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
#endif
    Main{}.main();
    return 0;
}
