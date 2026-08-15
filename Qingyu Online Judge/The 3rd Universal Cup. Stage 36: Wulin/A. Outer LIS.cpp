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
constexpr double eps = 1e-7;
template <typename T, bool isPrefix = true>
struct fenwick
{
    vector<T> c;
    stack<pair<int, T>> st;
    fenwick() = default;
    fenwick(int n) : c(n + 1) {}
    constexpr static auto lowbit = [](int x)
    {
        return x & (-x);
    };
    auto update(int pos, T val)
    {
        if constexpr (isPrefix)
            for (int i = pos; i < (int)c.size(); i += lowbit(i))
            {
                st.emplace(i, c[i]);
                c[i] = max(c[i], val);
            }
        else
            for (int i = pos; i; i -= lowbit(i))
            {
                st.emplace(i, c[i]);
                c[i] = max(c[i], val);
            }
    }
    auto query(int pos)
    {
        T res = 0;
        if constexpr (isPrefix)
            for (int i = pos; i; i -= lowbit(i))
                res = max(c[i], res);
        else
            for (int i = pos; i < (int)c.size(); i += lowbit(i))
                res = max(c[i], res);
        return res;
    }
    auto adjust(size_t s)
    {
        while (st.size() > s)
        {
            auto [x, y] = st.top();
            c[x] = y;
            st.pop();
        }
    }
};
struct Main
{
    int n, q;
    int block, num;
    vector<int> a, b;
    vector<int> L, R;
    vector<int> belong;
    Main()
    {
        cin >> n >> q;
        a.resize(n + 5), b.resize(n + 5);
        for (int i = 1; i <= n; ++i)
            cin >> a[i] >> b[i];
        block = (int)sqrt(n), num = (n - 1) / block + 1;
        L.resize(num + 5), R.resize(num + 5), belong.resize(n + 5);
        for (int i = 1; i <= num; ++i)
        {
            L[i] = R[i - 1] + 1;
            R[i] = min(R[i - 1] + block, n);
            for (int j = L[i]; j <= R[i]; ++j)
                belong[j] = i;
        }
        vector<tuple<int, int, int>> que(q);
        vector<int> answer(q);
        for (int i = 0; i < q; ++i)
        {
            auto &[x, y, id] = que[i];
            cin >> x >> y;
            id = i;
        }
        auto compare = [&](auto x, auto y)
        {
            auto [l1, r1, _] = x;
            auto [l2, r2, __] = y;
            return belong[l1] == belong[l2] ? r1 > r2 : l1 < l2;
        };
        sort(que.begin(), que.end(), compare);
        fenwick<int, true> tree1(n);
        fenwick<int, false> tree2(n);
        int lasbel = 0, l = 1, r = n, res = 0;
        for (auto [ql, qr, id] : que)
        {
            if (belong[ql] != lasbel)
            {
                tree2 = fenwick<int, false>(n);
                while (l < L[belong[ql]])
                {
                    tree1.update(a[l], tree1.query(a[l]) + b[l]);
                    ++l;
                }
                lasbel = belong[ql];
                r = n, res = tree1.query(n);
                tree1.st = stack<pair<int, int>>();
            }
            while (r > qr)
            {
                auto val = tree2.query(a[r]) + b[r];
                tree2.update(a[r], val);
                res = max(res, tree1.query(a[r]) + val);
                --r;
            }
            auto lassize = tree1.st.size();
            int curres = res;
            for (int i = L[belong[ql]]; i < ql; ++i)
            {
                int val = tree1.query(a[i]) + b[i];
                tree1.update(a[i], val);
                curres = max(curres, val + tree2.query(a[i]));
            }
            tree1.adjust(lassize);
            answer[id] = curres;
        }
        for (auto i : answer)
            cout << i << '\n';
    }
};
int main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    while (T--)
        Main();
    return 0;
}

