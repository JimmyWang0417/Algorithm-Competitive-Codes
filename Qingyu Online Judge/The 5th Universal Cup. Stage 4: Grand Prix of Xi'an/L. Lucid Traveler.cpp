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
namespace interator
{
    auto ask(int x, int y, const vector<int> &s)
    {
        cout << "? " << x << ' ' << y << ' ' << s.size();
        for (int v : s)
            cout << ' ' << v;
        cout << endl;
        int t;
        cin >> t;
        return t;
    }
    template <typename T>
    auto answer(const T &edges)
    {
        cout << "! " << edges.size() << '\n';
        for (auto [a, b] : edges)
            cout << a << ' ' << b << '\n';
        cout << flush;
    }
}
using namespace interator;
struct Main
{
    int n;
    vector<vector<int>> comp;
    vector<vector<bool>> linked;
    Main()
    {
        cin >> n;
        comp.resize(n + 1, vector<int>(n + 1));
        for (int z = 1; z <= n; ++z)
        {
            vector<int> reps;
            for (int x = 1; x <= n; ++x)
            {
                if (x == z)
                    continue;
                int id = -1;
                for (int r : reps)
                {
                    if (ask(x, r, {z}))
                    {
                        id = r;
                        break;
                    }
                }
                if (id == -1)
                {
                    reps.push_back(x);
                    comp[z][x] = x;
                }
                else
                    comp[z][x] = id;
            }
        }
        linked.resize(n + 1, vector<bool>(n + 1));
        for (int u = 1; u <= n; ++u)
            for (int v = u + 1; v <= n; ++v)
            {
                bool ok = true;
                for (int w = 1; w <= n; ++w)
                {
                    if (w != u && w != v && comp[w][u] != comp[w][v])
                    {
                        ok = false;
                        break;
                    }
                }
                linked[u][v] = linked[v][u] = ok;
            }
        set<vector<int>> blocks;
        for (int u = 1; u <= n; ++u)
            for (int v = u + 1; v <= n; ++v)
            {
                if (!linked[u][v])
                    continue;
                vector<int> block{u, v};
                for (int w = 1; w <= n; ++w)
                    if (w != u && w != v && linked[w][u] && linked[w][v])
                        block.push_back(w);
                sort(block.begin(), block.end());
                blocks.emplace(block);
            }
        set<pair<int, int>> edges;
        auto add = [&](int a, int b)
        {
            if (a > b)
                swap(a, b);
            edges.emplace(a, b);
        };
        for (const auto &block : blocks)
        {
            if (block.size() == 2)
            {
                add(block[0], block[1]);
                continue;
            }
            int X = block[0], Y = block[1], ep = block[2];
            for (int i = 3; i < (int)block.size(); ++i)
                if (!ask(Y, block[i], {X, ep}))
                    ep = block[i];
            auto closer = [&](int a, int b)
            { return ask(ep, b, {X, a}) == 0; };
            auto sortInDist = [&](this auto &&self, vector<int> &a)
            {
                if (a.size() <= 1)
                    return;
                vector<int> b(a.begin(), a.begin() + a.size() / 2);
                vector<int> c(a.begin() + a.size() / 2, a.end());
                self(b), self(c);
                int i = 0, j = 0, k = 0;
                while (j < (int)b.size() && k < (int)c.size())
                    a[i++] = closer(b[j], c[k]) ? b[j++] : c[k++];
                while (j < (int)b.size())
                    a[i++] = b[j++];
                while (k < (int)c.size())
                    a[i++] = c[k++];
            };
            vector<int> order;
            for (int i = 1; i < (int)block.size(); ++i)
            {
                if (block[i] == ep)
                    continue;
                order.emplace_back(block[i]);
            }
            sortInDist(order);
            add(X, ep);
            int prev = ep;
            for (int x : order)
            {
                add(prev, x);
                prev = x;
            }
            add(X, prev);
        }
        answer(edges);
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
