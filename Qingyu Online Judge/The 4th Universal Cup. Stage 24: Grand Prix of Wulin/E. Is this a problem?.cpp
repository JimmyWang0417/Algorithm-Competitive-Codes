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
namespace TEST
{
    int n, m, limit;
    map<int, set<int>> mp;
    auto init(int _n, const vector<pair<int, int>> &edge)
    {
        n = _n, m = (int)edge.size();
        mp.clear();
        for (auto [x, y] : edge)
        {
            if (x > y)
                swap(x, y);
            mp[x].insert(y);
        }
        limit = n + m * (2 + (int)ceil(log2(n)));
    }
    auto query(const vector<int> &p)
    {
        --limit;
        cout << "? " << p.size();
        for (int i : p)
            cout << ' ' << i;
        cout << endl;
        set<int> se;
        for (int i : p)
        {
            assert(se.find(i) == se.end());
            assert(1 <= i && i <= n);
            se.insert(i);
        }
        for (int u : p)
        {
            for (int v : mp[u])
                if (se.find(v) != se.end())
                    return cout << 0 << endl, false;
        }
        cout << "1" << endl;
        return true;
    }
    auto answer(vector<pair<int, int>> e)
    {
        cout << "! " << e.size() << '\n';
        for (auto [x, y] : e)
            cout << ' ' << x << ' ' << y << endl;
        
        for (auto &[x, y] : e)
            if (x > y)
                swap(x, y);
        auto las = e.size();
        ranges::sort(e);
        e.erase(unique(e.begin(), e.end()), e.end());
        assert(e.size() == las);
        assert((int)e.size() == m);
        for (auto [x, y] : e)
            assert(mp[x].find(y) != mp[x].end());
        assert(limit >= 0);
    }
}
namespace SUBMIT
{
    auto query(const vector<int> &p)
    {
        cout << "? " << p.size();
        for (int i : p)
            cout << ' ' << i;
        cout << endl;
        bool x;
        cin >> x;
        return x;
    }
    auto answer(const vector<pair<int, int>> &e)
    {
        cout << "! " << e.size();
        for (auto [x, y] : e)
            cout << ' ' << x << ' ' << y;
        cout << endl;
    }
}
using namespace SUBMIT;
struct Main
{
    int n;
    vector<pair<int, int>> edge;
    auto check(vector<int> S, int x)
    {
        if (S.empty())
            return true;
        S.push_back(x);
        return query(S);
    }
    auto sol(const vector<int> &S, int x) -> int
    {
        if (S.size() == 1)
            return S.front();
        vector<int> A, B;
        for (int i = 0; i < (int)S.size(); ++i)
        {
            if (i & 1)
                A.push_back(S[i]);
            else
                B.push_back(S[i]);
        }
        if (!check(A, x))
            return sol(A, x);
        else
            return sol(B, x);
    }
    auto solve(vector<int> S, int x)
    {
        do
        {
            int y = sol(S, x);
            S.erase(ranges::find(S, y));
            edge.emplace_back(x, y);
        } while (!check(S, x));
    }
    auto dfs(const vector<int> &S) -> void
    {
        vector<int> A, B;
        for (int x : S)
        {
            if (check(A, x))
                A.push_back(x);
            else
                B.push_back(x);
        }
        if (!B.empty())
        {
            for (int i : B)
                solve(A, i);
            dfs(B);
        }
    }
    Main()
    {
        cin >> n;
        vector<int> p(n);
        iota(p.begin(), p.end(), 1);
        dfs(p);
        answer(edge);
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    // init(4, {{1, 2}, {2, 3}, {3, 4}, {1, 4}});
    while (T--)
        Main();
    return 0;
}

