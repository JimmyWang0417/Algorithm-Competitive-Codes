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
struct poly : vector<i64>
{
    constexpr static int inv2 = quickpow(2);
    constexpr static int inv3 = quickpow(3);
    using vector<i64>::vector;

    inline static vector<int> rk;
    inline static int limit, len;

    static auto init(size_t n)
    {
        len = 0, limit = 1;
        while (limit < (int)n)
        {
            ++len;
            limit <<= 1;
        }
        rk.resize(limit);
        for (int i = 0; i < limit; ++i)
            rk[i] = (rk[i >> 1] >> 1) | ((i & 1) << (len - 1));
    }
    auto friend &operator>>(istream &in, poly &p)
    {
        for (auto &i : p)
            in >> i;
        return in;
    }
    auto friend &operator<<(ostream &out, const poly &p)
    {
        for (auto i : p)
            out << (i + mod) % mod << ' ';
        return out;
    }

    auto friend operator+(poly lhs, poly rhs)
    {
        if (lhs.size() < rhs.size())
            lhs.resize(rhs.size());
        rhs.resize(lhs.size());
        for (int i = 0; i < (int)lhs.size(); ++i)
            (lhs[i] += rhs[i]) %= mod;
        return lhs;
    }
    auto friend operator-(poly lhs, poly rhs)
    {
        if (lhs.size() < rhs.size())
            lhs.resize(rhs.size());
        rhs.resize(lhs.size());
        for (int i = 0; i < (int)lhs.size(); ++i)
            (lhs[i] -= rhs[i]) %= mod;
        return lhs;
    }

    auto friend operator*(poly lhs, i64 rhs)
    {
        for (auto &i : lhs)
            (i *= rhs) %= mod;
        return lhs;
    }
    auto friend operator/(poly lhs, i64 rhs)
    {
        return lhs * quickpow(rhs);
    }

    auto NTT()
    {
        for (int i = 0; i < limit; ++i)
            if (i < rk[i])
                std::swap(at(i), at(rk[i]));
        for (int mid = 1; mid < limit; mid <<= 1)
        {
            const auto gn = quickpow(3, (mod - 1) / (mid << 1));
            for (int i = 0; i < limit; i += mid << 1)
            {
                i64 g = 1;
                for (int j = 0; j < mid; ++j, (g *= gn) %= mod)
                {
                    auto x = at(i + j), y = at(i + j + mid) * g % mod;
                    at(i + j) = (x + y) % mod;
                    at(i + j + mid) = (x - y) % mod;
                }
            }
        }
    }
    auto INTT()
    {
        for (int i = 0; i < limit; ++i)
            if (i < rk[i])
                std::swap(at(i), at(rk[i]));
        for (int mid = 1; mid < limit; mid <<= 1)
        {
            const auto gn = quickpow(inv3, (mod - 1) / (mid << 1));
            for (int i = 0; i < limit; i += mid << 1)
            {
                i64 g = 1;
                for (int j = 0; j < mid; ++j, (g *= gn) %= mod)
                {
                    auto x = at(i + j), y = at(i + j + mid) * g % mod;
                    at(i + j) = (x + y) % mod;
                    at(i + j + mid) = (x - y) % mod;
                }
            }
        }
        auto invlimit = quickpow(limit);
        for (auto &i : (*this))
            (i *= invlimit) %= mod;
    }
    auto friend operator*(poly lhs, poly rhs)
    {
        if (lhs.empty() || rhs.empty())
            return poly{};
        auto up = lhs.size() + rhs.size() - 1;
        init(up);
        lhs.resize(limit), lhs.NTT();
        rhs.resize(limit), rhs.NTT();
        for (int i = 0; i < limit; ++i)
            (lhs[i] *= rhs[i]) %= mod;
        lhs.INTT(), lhs.resize(up);
        return lhs;
    }
};
struct Main
{
    int n, d;
    vector<vector<int>> G;
    vector<tuple<int, int, int, int>> p;
    vector<int> col;
    array<i64, 2> mul;
    array<int, 2> sze;
    auto dfs(int u, int c) -> void
    {
        col[u] = c + 1;
        (mul[c] *= get<3>(p[u])) %= mod;
        sze[c]++;
        for (auto v : G[u])
        {
            if (!col[v])
                dfs(v, c ^ 1);
            else if (col[v] == c + 1)
                throw logic_error("");
        }
    }
    Main()
    {
        cin >> n >> d;
        G.resize(n);
        p.resize(n);
        map<tuple<int, int, int>, vector<int>> mp;
        for (auto &[x, y, z, w] : p)
            cin >> x >> y >> z >> w;
        for (int i = 0; i < n; ++i)
        {
            auto [x, y, z, w] = p[i];
            mp[{(2 * x + d - 1) / d, (2 * y + d - 1) / d, (2 * z + d - 1) / d}].push_back(i);
        }
        for (auto &[P, v] : mp)
        {
            if (v.size() > 2)
            {
                for (int _ : views::iota(1, n))
                    cout << "0\n";
                return;
            }
            auto [x, y, z] = P;
            for (int i = 0; i < (int)v.size(); ++i)
                for (int j = i + 1; j < (int)v.size(); ++j)
                {
                    G[v[i]].push_back(v[j]);
                    G[v[j]].push_back(v[i]);
                }
            for (int i = x - 2; i <= x + 2; ++i)
                for (int j = y - 2; j <= y + 2; ++j)
                    for (int k = z - 2; k <= z + 2; ++k)
                    {
                        if (i == x && j == y && k == z)
                            continue;
                        if (mp.find({i, j, k}) == mp.end())
                            continue;
                        for (int l : v)
                            for (int r : mp[{i, j, k}])
                            {
                                i64 A = get<0>(p[l]) - get<0>(p[r]);
                                i64 B = get<1>(p[l]) - get<1>(p[r]);
                                i64 C = get<2>(p[l]) - get<2>(p[r]);
                                if ((i64)d * d > A * A + B * B + C * C)
                                    G[l].push_back(r);
                            }
                    }
        }
        col.resize(n);
        priority_queue<pair<size_t, poly>, vector<pair<size_t, poly>>, greater<>> q;
        for (int i = 0; i < n; ++i)
        {
            if (col[i])
                continue;
            mul.fill(1);
            sze.fill(0);
            try
            {
                dfs(i, 0);
            }
            catch (const logic_error &e)
            {
                for (int _ : views::iota(1, n))
                    cout << "0\n";
                return;
            }
            poly _(max(sze[0], sze[1]) + 1);
            (_[sze[0]] += mul[0]) %= mod;
            (_[sze[1]] += mul[1]) %= mod;
            q.emplace(_.size(), _);
        }
        while (q.size() > 1)
        {
            auto x = q.top().second;
            q.pop();
            auto y = q.top().second;
            q.pop();
            auto z = x * y;
            q.emplace(z.size(), z);
        }
        for (int i = 1; i < n; ++i)
            cout << (i < (int)q.top().second.size() ? (q.top().second[i] + mod) % mod : 0) << '\n';
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

