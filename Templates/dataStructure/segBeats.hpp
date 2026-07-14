#pragma once
#include <algorithm>
#include <limits>
#include <vector>

template <typename T = long long>
struct segBeats
{
    static constexpr T negInf = std::numeric_limits<T>::lowest() / 4;

    struct Node
    {
        int len = 0, cnt = 0;
        T sum = 0;
        T max = negInf, second = negInf, hisMax = negInf;
        T addMax = 0, addOther = 0, hisMaxTag = 0, hisOtherTag = 0;

        auto update(T valMax, T valOther, T hisMaxVal, T hisOtherVal)
        {
            sum += valMax * cnt + valOther * (len - cnt);
            hisMax = std::max(hisMax, max + hisMaxVal);
            max += valMax;
            if (second > negInf)
                second += valOther;
            hisMaxTag = std::max(hisMaxTag, addMax + hisMaxVal);
            hisOtherTag = std::max(hisOtherTag, addOther + hisOtherVal);
            addMax += valMax;
            addOther += valOther;
        }
    };

    int n = 0;
    std::vector<Node> tree;

    segBeats() = default;
    segBeats(const std::vector<T> &a) { build(a); }

    auto init(int _n)
    {
        n = _n;
        tree.assign(n * 4 + 5, {});
    }

    auto pushup(int rt)
    {
        int lc = rt << 1, rc = rt << 1 | 1;
        tree[rt].len = tree[lc].len + tree[rc].len;
        tree[rt].sum = tree[lc].sum + tree[rc].sum;
        if (tree[lc].max > tree[rc].max)
        {
            tree[rt].max = tree[lc].max;
            tree[rt].cnt = tree[lc].cnt;
            tree[rt].second = std::max(tree[lc].second, tree[rc].max);
        }
        else if (tree[lc].max < tree[rc].max)
        {
            tree[rt].max = tree[rc].max;
            tree[rt].cnt = tree[rc].cnt;
            tree[rt].second = std::max(tree[lc].max, tree[rc].second);
        }
        else
        {
            tree[rt].max = tree[lc].max;
            tree[rt].cnt = tree[lc].cnt + tree[rc].cnt;
            tree[rt].second = std::max(tree[lc].second, tree[rc].second);
        }
        tree[rt].hisMax = std::max(tree[lc].hisMax, tree[rc].hisMax);
    }

    auto pushdown(int rt)
    {
        int lc = rt << 1, rc = rt << 1 | 1;
        if (!tree[rt].addMax && !tree[rt].addOther && !tree[rt].hisMaxTag && !tree[rt].hisOtherTag)
            return;
        T maxv = std::max(tree[lc].max, tree[rc].max);
        if (tree[lc].max == maxv)
            tree[lc].update(tree[rt].addMax, tree[rt].addOther, tree[rt].hisMaxTag, tree[rt].hisOtherTag);
        else
            tree[lc].update(tree[rt].addOther, tree[rt].addOther, tree[rt].hisOtherTag, tree[rt].hisOtherTag);
        if (tree[rc].max == maxv)
            tree[rc].update(tree[rt].addMax, tree[rt].addOther, tree[rt].hisMaxTag, tree[rt].hisOtherTag);
        else
            tree[rc].update(tree[rt].addOther, tree[rt].addOther, tree[rt].hisOtherTag, tree[rt].hisOtherTag);
        tree[rt].addMax = tree[rt].addOther = tree[rt].hisMaxTag = tree[rt].hisOtherTag = 0;
    }

    auto build(int rt, int l, int r, const std::vector<T> &a) -> void
    {
        tree[rt] = Node();
        tree[rt].len = r - l + 1;
        if (l == r)
        {
            T val = l < (int)a.size() ? a[l] : T();
            tree[rt].sum = tree[rt].max = tree[rt].hisMax = val;
            tree[rt].cnt = 1;
            return;
        }
        int mid = (l + r) >> 1;
        build(rt << 1, l, mid, a);
        build(rt << 1 | 1, mid + 1, r, a);
        pushup(rt);
    }

    auto build(const std::vector<T> &a)
    {
        init((int)a.size() - 1);
        if (n)
            build(1, 1, n, a);
    }

    auto rangeAdd(int rt, int l, int r, int x, int y, T val) -> void
    {
        if (r < x || l > y)
            return;
        if (x <= l && r <= y)
            return tree[rt].update(val, val, val, val);
        int mid = (l + r) >> 1;
        pushdown(rt);
        rangeAdd(rt << 1, l, mid, x, y, val);
        rangeAdd(rt << 1 | 1, mid + 1, r, x, y, val);
        pushup(rt);
    }

    auto rangeChmin(int rt, int l, int r, int x, int y, T val) -> void
    {
        if (r < x || l > y || tree[rt].max <= val)
            return;
        if (x <= l && r <= y && tree[rt].second < val)
            return tree[rt].update(val - tree[rt].max, 0, val - tree[rt].max, 0);
        int mid = (l + r) >> 1;
        pushdown(rt);
        rangeChmin(rt << 1, l, mid, x, y, val);
        rangeChmin(rt << 1 | 1, mid + 1, r, x, y, val);
        pushup(rt);
    }

    auto querySum(int rt, int l, int r, int x, int y) -> T
    {
        if (r < x || l > y)
            return 0;
        if (x <= l && r <= y)
            return tree[rt].sum;
        int mid = (l + r) >> 1;
        pushdown(rt);
        return querySum(rt << 1, l, mid, x, y) + querySum(rt << 1 | 1, mid + 1, r, x, y);
    }

    auto queryMax(int rt, int l, int r, int x, int y) -> T
    {
        if (r < x || l > y)
            return negInf;
        if (x <= l && r <= y)
            return tree[rt].max;
        int mid = (l + r) >> 1;
        pushdown(rt);
        return std::max(queryMax(rt << 1, l, mid, x, y),
                        queryMax(rt << 1 | 1, mid + 1, r, x, y));
    }

    auto queryHisMax(int rt, int l, int r, int x, int y) -> T
    {
        if (r < x || l > y)
            return negInf;
        if (x <= l && r <= y)
            return tree[rt].hisMax;
        int mid = (l + r) >> 1;
        pushdown(rt);
        return std::max(queryHisMax(rt << 1, l, mid, x, y),
                        queryHisMax(rt << 1 | 1, mid + 1, r, x, y));
    }

    auto rangeAdd(int l, int r, T val) { if (l <= r && n) rangeAdd(1, 1, n, l, r, val); }
    auto rangeChmin(int l, int r, T val) { if (l <= r && n) rangeChmin(1, 1, n, l, r, val); }
    auto querySum(int l, int r) { return l <= r && n ? querySum(1, 1, n, l, r) : T(); }
    auto queryMax(int l, int r) { return l <= r && n ? queryMax(1, 1, n, l, r) : negInf; }
    auto queryHisMax(int l, int r) { return l <= r && n ? queryHisMax(1, 1, n, l, r) : negInf; }
};
