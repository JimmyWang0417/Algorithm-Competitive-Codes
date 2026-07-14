#pragma once
#include "poly.hpp"
namespace polynomial
{
    struct lagrange
    {
    private:
#define lc (rt << 1)
#define rc (rt << 1 | 1)
        vector<poly> tree;
        auto build(int rt, int l, int r, const vector<int> &a)
        {
            if (l == r)
            {
                tree[rt] = poly{1, -a[l]};
                return;
            }
            int mid = (l + r) >> 1;
            build(lc, l, mid, a);
            build(rc, mid + 1, r, a);
            tree[rt] = tree[lc] * tree[rc];
        }
        auto buildI(int rt, int l, int r, const vector<int> &a)
        {
            if (l == r)
            {
                tree[rt] = poly{-a[l], 1};
                return;
            }
            int mid = (l + r) >> 1;
            buildI(lc, l, mid, a);
            buildI(rc, mid + 1, r, a);
            tree[rt] = tree[lc] * tree[rc];
        }
        auto solve(int rt, int l, int r, vector<int> &ans, const poly &p)
        {
            if (l == r)
            {
                ans[l] = p.empty() ? 0 : (int)(p[0] + mod) % mod;
                return;
            }
            int mid = (l + r) >> 1;
            solve(lc, l, mid, ans, mulT(p, tree[rc]));
            solve(rc, mid + 1, r, ans, mulT(p, tree[lc]));
        }
        auto calc(int rt, int l, int r, const vector<int> &a)
        {
            if (l == r)
                return poly{a[l]};
            int mid = (l + r) >> 1;
            return calc(lc, l, mid, a) * tree[rc] + tree[lc] * calc(rc, mid + 1, r, a);
        }
#undef lc
#undef rc
    public:
        auto eval(const poly &F, const vector<int> &X)
        {
            int n = (int)F.size(), m = (int)X.size();
            vector<int> ans(m);
            if (!n || !m)
                return ans;
            tree.resize(m * 4, poly{});
            build(1, 0, m - 1, X);
            auto G = tree[1];
            G.resize(n);
            auto H = F ^ G.inv();
            H.resize(m);
            solve(1, 0, m - 1, ans, H);
            return ans;
        }
        auto interpolation(const vector<int> &X, vector<int> Y)
        {
            if (X.empty())
                return poly{};
            int n = (int)X.size();
            tree.resize(n * 4, poly{});
            buildI(1, 0, n - 1, X);

            vector<poly> _tree;
            swap(_tree, tree);
            auto W = eval(_tree[1].differ(), X);
            swap(_tree, tree);

            for (int i = 0; i < n; ++i)
                Y[i] = (int)((i64)Y[i] * quickpow(W[i]) % mod);

            return calc(1, 0, n - 1, Y);
        }
        static auto eval(const vector<int> &Y, int k) // a0, a1, ... am-1
        {
            int n = (int)Y.size() - 1;
            vector<i64> fac(n + 1), ifac(n + 1);
            vector<i64> pre(n + 1), suf(n + 1);
            fac[0] = 1;
            for (int i = 1; i <= n; ++i)
                fac[i] = fac[i - 1] * i % mod;
            ifac[n] = quickpow(fac[n]);
            for (int i = n; i >= 1; --i)
                ifac[i - 1] = ifac[i] * i % mod;
            pre[0] = 1;
            for (int i = 0; i < n; ++i)
                pre[i + 1] = pre[i] * (k - i) % mod;
            suf[n] = 1;
            for (int i = n; i >= 1; --i)
                suf[i - 1] = suf[i] * (k - i) % mod;
            i64 res = 0;
            for (int i = 0; i <= n; ++i)
                (res += ((n - i) & 1 ? -1 : 1) * Y[i] *
                        (pre[i] * suf[i] % mod) % mod *
                        (ifac[i] * ifac[n - i] % mod)) %= mod;
            return res;
        }
        static auto shift(const vector<int> &Y, int c) // a0, a1, ... am-1
        {
            int n = (int)Y.size() - 1;
            if (c == 0)
                return Y;
            if (0 < c && c <= n)
            {
                auto res = vector<int>(Y.begin() + c, Y.end());
                auto cur = shift(Y, n + 1);
                res.insert(res.end(), cur.begin(), cur.begin() + c);
                return res;
            }
            if (-n <= c && c < 0)
            {
                auto res = vector<int>(Y.begin(), Y.end() + c);
                auto cur = shift(Y, -n - 1);
                res.insert(res.begin(), cur.end() + c, cur.end());
                return res;
            }

            vector<i64> fac(n + 1), ifac(n + 1);
            fac[0] = 1;
            for (int i = 1; i <= n; ++i)
                fac[i] = fac[i - 1] * i % mod;
            ifac[n] = quickpow(fac[n]);
            for (int i = n; i >= 1; --i)
                ifac[i - 1] = ifac[i] * i % mod;

            poly a(2 * n + 1), b(n + 1);
            for (int i = 0; i <= 2 * n; i++)
                a[i] = quickpow(c - n + i);
            for (int i = 0; i <= n; i++)
                b[i] = ((n - i) & 1 ? -1 : 1) * Y[i] * ifac[i] % mod * ifac[n - i] % mod;
            auto res = a * b;
            vector<int> ans(n + 1);
            {
                i64 times = 1;
                for (int i = c - n; i <= c; i++)
                    (times *= i) %= mod;
                for (int i = 0; i <= n; i++)
                {
                    ans[i] = (int)(times * res[i + n] % mod);
                    (times *= (c + i + 1) * a[i]) %= mod;
                }
            }
            return ans;
        }
    };
}
