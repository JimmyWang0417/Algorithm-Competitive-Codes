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
typedef pair<i64, int> node;
auto operator+(const node &lhs, const node &rhs)
{
    return node(lhs.first + rhs.first, lhs.second + rhs.second);
}
struct fenwick
{
    vector<node> c;
    constexpr static auto lowbit = [](int x)
    {
        return x & (-x);
    };
    fenwick() {}
    fenwick(int n) : c(n + 1, node(LLONG_MIN / 2, INT_MIN / 2)) {}
    auto update(int pos, node val)
    {
        for (int i = pos; i < (int)c.size(); i += lowbit(i))
            c[i] = max(c[i], val);
    }
    auto query(int pos)
    {
        node res(LLONG_MIN / 2, INT_MIN / 2);
        for (int i = pos; i; i -= lowbit(i))
            res = max(res, c[i]);
        return res;
    }
};
struct Main
{
    int n;
    vector<int> p;
    auto calc(int mid)
    {
        fenwick tree(n);
        for (auto x : p)
        {
            tree.update(x,
                        max({node(1 - mid, 1),
                             tree.query(n) + node(1 - mid, 1),
                             tree.query(x) + node(1, 0)}));
        }
        return tree.query(n);
    }
    auto solve(int x)
    {
        int l = 0, r = n;
        while (l < r)
        {
            int mid = (l + r + 1) >> 1;
            if (calc(mid).second >= x)
                l = mid;
            else
                r = mid - 1;
        }
        auto [res, _] = calc(l);
        return res + (i64)x * l;
    }
    vector<i64> answer;
    auto solve(int l, int r, int ql, int qr)
    {
        if (l > r)
            return;
        if (ql == qr)
        {
            for (int i = l; i <= r; ++i)
                answer[i] = ql;
            return;
        }
        int mid = (ql + qr + 1) >> 1;
        int pos = calc(mid).second;
        solve(l, min(pos, r), mid, qr);
        solve(pos + 1, r, ql, mid - 1);
    }
    Main()
    {
        cin >> n;
        p.resize(n);
        for (int i = 0; i < n; ++i)
            cin >> p[i];
        answer.resize(n + 5);
        solve(1, n, 0, n);
        for (int i = 1; i <= n; ++i)
            answer[i] += answer[i - 1];
        for (int i = 1; i <= n; ++i)
            cout << n - answer[n] + answer[i] << ' ';
        cout << '\n';
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        Main();
    return 0;
}

