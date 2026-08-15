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
vector<vector<int>> g(1 << 12);
struct Main
{
    struct node
    {
        vector<int> fa;
        node() = default;
        node(int _n) : fa(_n + 5) {}
        auto find(int x)
        {
            if (!fa[x])
                return x;
            return fa[x] = find(fa[x]);
        }
        auto unionn(int x, int y)
        {
            x = find(x), y = find(y);
            if (x == y)
                return false;
            fa[x] = y;
            return true;
        }
        auto check(int x, int y)
        {
            return find(x) == find(y);
        }
    };
    int n, q;
    Main()
    {
        cin >> n >> q;
        vector<node> se(1 << 12, node(n));
        i64 sum = 0;
        auto query = [&]()
        {
            char c;
            int u, v, w;
            cin >> c >> u >> v;
            if (c == '+')
            {
                cin >> w;
                if (se[w].check(u, v))
                    return;
                for (int i = 0; i < 12; ++i)
                    if ((w >> i) & 1)
                    {
                        queue<int> q;
                        q.push(w & ~((1 << i) - 1));
                        while (!q.empty())
                        {
                            int x = q.front();
                            q.pop();
                            if (!se[x].unionn(u, v))
                                continue;
                            for (int y : g[x])
                                q.push(y);
                        }
                    }
                se[0].unionn(u, v);
            }
            else
            {
                if (!se[0].check(u, v))
                {
                    sum += -1;
                    return;
                }
                int res = 0;
                for (int i = 11; i >= 0; --i)
                    if (se[res | 1 << i].check(u, v))
                        res |= (1 << i);
                sum += res;
            }
        };
        while (q--)
            query();
        cout << sum << '\n';
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    for (int i = 1; i < (1 << 12); ++i)
        for (int j = __builtin_ctz(i) + 1; j < 12; ++j)
            if ((i >> j) & 1)
                g[i].push_back(i ^ (1 << j));
    int T = 1;
    cin >> T;
    while (T--)
        Main();
    return 0;
}
