#pragma once
#include <vector>

#define lc (rt << 1)
#define rc (rt << 1 | 1)

template <typename Event>
struct SegDivide
{
    int n = 0;
    vector<vector<Event>> tree;

    SegDivide() = default;
    SegDivide(int _n) : n(_n), tree(n * 4 + 5) {}

    auto build(int _n)
    {
        n = _n;
        tree.resize(n * 4 + 5);
    }

    auto add(int rt, int l, int r, int x, int y, const Event &e) -> void
    {
        if (r < x || l > y)
            return;
        if (x <= l && r <= y)
        {
            tree[rt].push_back(e);
            return;
        }
        int mid = (l + r) >> 1;
        add(lc, l, mid, x, y, e);
        add(rc, mid + 1, r, x, y, e);
    }

    auto add(int l, int r, const Event &e)
    {
        if (l <= r && n)
            add(1, 1, n, l, r, e);
    }

    template <typename Add, typename Snapshot, typename Rollback, typename Answer>
    auto dfs(int rt, int l, int r, Add &&addEvent, Snapshot &&snapshot, Rollback &&rollback, Answer &&answer) -> void
    {
        auto state = snapshot();
        for (const auto &e : tree[rt])
            addEvent(e);
        if (l == r)
            answer(l);
        else
        {
            int mid = (l + r) >> 1;
            dfs(lc, l, mid, addEvent, snapshot, rollback, answer);
            dfs(rc, mid + 1, r, addEvent, snapshot, rollback, answer);
        }
        rollback(state);
    }

    template <typename Add, typename Snapshot, typename Rollback, typename Answer>
    auto work(Add &&addEvent, Snapshot &&snapshot, Rollback &&rollback, Answer &&answer)
    {
        if (n)
            dfs(1, 1, n, addEvent, snapshot, rollback, answer);
    }
};

#undef lc
#undef rc
