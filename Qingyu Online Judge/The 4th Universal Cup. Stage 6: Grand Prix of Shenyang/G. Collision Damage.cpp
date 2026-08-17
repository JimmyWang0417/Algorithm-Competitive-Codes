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
auto &operator<<(ostream &out, i128 rhs)
{
    if (rhs == 0)
        out << 0;
    else
    {
        stack<int> st;
        while (rhs)
        {
            st.push((int)(rhs % 10));
            rhs /= 10;
        }
        while (!st.empty())
        {
            out << st.top();
            st.pop();
        }
    }
    return out;
}
auto gcd(i128 x, i128 y)
{
    if (y == 0)
        return x;
    return gcd(y, x % y);
}
typedef complex<int> point;
auto cross(point a, point b)
{
    return (conj(a) * b).imag();
}
namespace std
{
    auto operator<(const point &lhs, const point &rhs)
    {
        return make_pair(lhs.real(), lhs.imag()) < make_pair(rhs.real(), rhs.imag());
    }
}
struct Main
{
    int n, m;
    vector<point> A, B, C;
    auto area(const vector<point> &rhs)
    {
        double area = 0;
        for (int i = 0; i < (int)rhs.size(); ++i)
            area += cross(rhs[i], rhs[(i + 1) % (int)rhs.size()]);
        return area / 2;
    }
    auto convex(vector<point> p)
    {
        sort(p.begin(), p.end());
        auto compare = [&](auto x, auto y)
        {
            auto d = cross(x - p.front(), y - p.front());
            if (d == 0)
                return norm(x) < norm(y);
            else
                return d > 0;
        };
        sort(p.begin() + 1, p.end(), compare);
        vector<point> st;
        for (auto q : p)
        {
            while (st.size() >= 2 && cross(st[st.size() - 2] - st.back(), q - st.back()) >= 0)
                st.pop_back();
            st.push_back(q);
        }
        return st;
    }
    Main()
    {
        cin >> n >> m;
        A.resize(n);
        B.resize(m);
        for (int i = 0; i < n; ++i)
        {
            int x, y;
            cin >> x >> y;
            A[i] = {x, y};
        }
        for (int i = 0; i < m; ++i)
        {
            int x, y;
            cin >> x >> y;
            B[i] = {x, y};
        }
        for (int i = 0; i < n; ++i)
            for (int j = 0; j < m; ++j)
                C.push_back(A[i] - B[j]);
        cout << fixed << setprecision(9) << area(A) * area(B) / area(convex(C)) << '\n';
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
