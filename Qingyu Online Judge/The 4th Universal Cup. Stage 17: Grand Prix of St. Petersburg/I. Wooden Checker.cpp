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
constexpr int mod = 1e6 + 3;
template <typename T = int>
constexpr auto quickpow(i64 a, T b = mod - 2)
{
    a %= mod;
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
    vector<int> in;
    vector<int> L, R;
    struct UnionSet : vector<int>
    {
        using vector<int>::vector;
        UnionSet(size_t n) : vector(n) { iota(begin(), end(), 0); }
        auto find(int x)
        {
            if (at(x) == x)
                return x;
            return at(x) = find(at(x));
        }
    };
    UnionSet fa;
    Main()
    {
        cin >> n;
        fa = UnionSet(n + 5);
        in.resize(n + 5);
        L.resize(n + 5), R.resize(n + 5);
        ranges::iota(L, 0);
        ranges::iota(R, 0);
        vector<int> par(n + 5);
        for (int i = 1; i < n; ++i)
        {
            int u, v;
            cin >> u >> v;
            if (par[v])
            {
                cout << "Bad oriented forest\n";
                return;
            }
            par[v] = u;
            int x = fa.find(u), y = fa.find(v);
            if (R[x] + 1 == L[y])
            {
                int t = R[x];
                while (t)
                {
                    if (t == u)
                        break;
                    t = par[t];
                }
                if (!t)
                {
                    cout << "Bad segment at " << u << '\n';
                    break;
                }
                fa[y] = x;
                R[x] = R[y];
            }
            else if (L[x] - 1 == R[y])
            {
                int t = L[x];
                while (t)
                {
                    if (t == u)
                        break;
                    t = par[t];
                }
                if (!t)
                {
                    cout << "Bad segment at " << u << '\n';
                    break;
                }
                fa[y] = x;
                L[x] = L[y];
            }
            else
            {
                cout << "Bad segment at " << x << '\n';
                return;
            }
            cout << "Good" << endl;
        }
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
