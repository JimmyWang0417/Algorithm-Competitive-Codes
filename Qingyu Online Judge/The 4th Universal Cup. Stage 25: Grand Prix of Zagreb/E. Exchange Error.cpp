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
typedef complex<i64> p2;
auto dot(p2 x, p2 y)
{
    return (conj(x) * y).real();
}
auto cross(p2 x, p2 y)
{
    return (conj(x) * y).imag();
}
struct Main
{
    int n, q;
    vector<int> a;
    auto cdq(int l, int r) -> tuple<vector<p2>, vector<p2>, vector<p2>>
    {
        if (l == r)
            return {{p2(1, a[l])}, {p2(1, a[l])}, {p2(1, a[l])}};
        int mid = (l + r) / 2;
        auto [preA, sufA, ansA] = cdq(l, mid);
        auto [preB, sufB, ansB] = cdq(mid + 1, r);
        auto pre = preA, suf = sufB;
        {
            auto ad = preA.back();
            for (auto i : preB)
            {
                while (pre.size() >= 2 && cross(pre[pre.size() - 2] - pre.back(), (i + ad - pre.back())) <= 0)
                    pre.pop_back();
                pre.push_back(i + ad);
            }
        }
        {
            auto ad = sufB.back();
            for (auto i : sufA)
            {
                while (suf.size() >= 2 && cross(suf[suf.size() - 2] - suf.back(), (i + ad - suf.back())) <= 0)
                    suf.pop_back();
                suf.push_back(i + ad);
            }
        }
        vector<p2> ans;
        {
            vector<p2> A(sufA), B(preB);
            adjacent_difference(A.begin(), A.end(), A.begin());
            adjacent_difference(B.begin(), B.end(), B.begin());
            vector<p2> C(A.size() + B.size() - 1);
            C.front() = A.front() + B.front();
            merge(A.begin() + 1, A.end(), B.begin() + 1, B.end(), C.begin() + 1, [](auto x, auto y)
                  { return cross(x, y) < 0; });
            partial_sum(C.begin(), C.end(), C.begin());
            C.insert(C.begin(), ansA.begin(), ansA.end());
            C.insert(C.begin(), ansB.begin(), ansB.end());
            sort(C.begin(), C.end(), [](auto x, auto y)
                 { return make_pair(x.real(), x.imag()) < make_pair(y.real(), y.imag()); });
            for (auto i : C)
            {
                while (ans.size() >= 2 && cross(ans[ans.size() - 2] - ans.back(), (i - ans.back())) <= 0)
                    ans.pop_back();
                ans.push_back(i);
            }
        }
        return {pre, suf, ans};
    }
    Main()
    {
        cin >> n >> q;
        a.resize(n);
        for (auto &i : a)
            cin >> i;
        auto ans = get<2>(cdq(0, n - 1));
        while (q--)
        {
            int x;
            cin >> x;
            int l = 0, r = (int)ans.size() - 2;
            while (l <= r)
            {
                int mid = (l + r) / 2;
                if (x * ans[mid].real() + ans[mid].imag() <
                    x * ans[mid + 1].real() + ans[mid + 1].imag())
                    l = mid + 1;
                else
                    r = mid - 1;
            }
            cout << ans[l].real() * x + ans[l].imag() << ' ';
        }
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
