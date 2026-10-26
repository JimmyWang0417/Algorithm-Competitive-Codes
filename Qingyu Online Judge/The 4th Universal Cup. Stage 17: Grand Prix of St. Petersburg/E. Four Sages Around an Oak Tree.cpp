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
    array<string, 3> name{"red", "green", "blue"};
    int strategy[4][3][3] = {
        {{2, 1, 0}, {2, 0, 2}, {0, 1, 1}},
        {{0, 2, 1}, {0, 0, 2}, {2, 1, 1}},
        {{2, 1, 2}, {0, 0, 1}, {1, 0, 2}},
        {{2, 0, 2}, {0, 1, 2}, {1, 1, 0}},
    };
    int color(const string &s)
    {
        return (int)(find(name.begin(), name.end(), s) - name.begin());
    }
    void interact()
    {
        int t, s;
        cin >> t >> s;
        while (t--)
        {
            if (s == 1)
            {
                array<int, 4> c;
                for (auto &x : c)
                {
                    string str;
                    cin >> str;
                    x = color(str);
                }
                int ans = -1;
                for (int m = 0; m < 4; ++m)
                {
                    if (strategy[m][c[(m + 3) % 4]][c[(m + 1) % 4]] == c[m])
                    {
                        ans = m;
                        break;
                    }
                }
                assert(ans != -1);
                cout << ans + 1 << '\n';
                cout.flush();
            }
            else
            {
                int m;
                string l, r;
                cin >> m >> l >> r;
                --m;
                cout << name[strategy[m][color(l)][color(r)]] << '\n';
                cout.flush();
            }
        }
    }
#ifdef GENERATE
    mt19937 rnd{(random_device())()};
    array<int, 36> p;
    vector<array<int, 4>> state;
    int id(const array<int, 4> &c, int m)
    {
        return m * 9 + c[(m + 3) % 4] * 3 + c[(m + 1) % 4];
    }
    bool dfs()
    {
        int mn = 5;
        vector<int> candidate;
        for (int k = 0; k < (int)state.size(); ++k)
        {
            bool ok = false;
            int cnt = 0;
            for (int m = 0; m < 4; ++m)
            {
                int x = p[id(state[k], m)];
                if (x == state[k][m])
                {
                    ok = true;
                    break;
                }
                if (x == -1)
                    ++cnt;
            }
            if (ok)
                continue;
            if (cnt == 0)
                return false;
            if (cnt < mn)
            {
                mn = cnt;
                candidate.clear();
            }
            if (cnt == mn)
                candidate.emplace_back(k);
        }
        if (candidate.empty())
            return true;
        int k = candidate[rnd() % candidate.size()];
        array<int, 4> order{0, 1, 2, 3};
        shuffle(order.begin(), order.end(), rnd);
        for (auto m : order)
        {
            int x = id(state[k], m);
            if (p[x] == -1)
            {
                p[x] = state[k][m];
                if (dfs())
                    return true;
                p[x] = -1;
            }
        }
        return false;
    }
    void generate()
    {
        p.fill(-1);
        for (int mask = 0; mask < 81; ++mask)
        {
            int x = mask;
            array<int, 4> c;
            for (auto &v : c)
            {
                v = x % 3;
                x /= 3;
            }
            state.emplace_back(c);
        }
        assert(dfs());
        for (auto &x : p)
            if (x == -1)
                x = (int)(rnd() % 3);
        for (const auto &c : state)
        {
            bool ok = false;
            for (int m = 0; m < 4; ++m)
                if (p[id(c, m)] == c[m])
                    ok = true;
            assert(ok);
        }
        cout << "int strategy[4][3][3] = {\n";
        for (int m = 0; m < 4; ++m)
        {
            cout << "    {";
            for (int l = 0; l < 3; ++l)
            {
                cout << '{';
                for (int r = 0; r < 3; ++r)
                    cout << p[m * 9 + l * 3 + r] << (r == 2 ? "}" : ", ");
                cout << (l == 2 ? "},\n" : ", ");
            }
        }
        cout << "};\n";
    }
#endif
    Main()
    {
#ifdef GENERATE
        generate();
#else
        interact();
#endif
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
