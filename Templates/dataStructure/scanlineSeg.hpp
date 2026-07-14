#pragma once
#include <algorithm>
#include <array>
#include <vector>

template <typename T = long long>
struct scanlineSeg
{
    struct Node
    {
        int cnt = 0;
        T len = 0;
    };

    std::vector<T> p;
    std::vector<Node> tree;

    scanlineSeg() = default;
    scanlineSeg(const std::vector<T> &_p) { build(_p); }

    auto build(const std::vector<T> &_p)
    {
        p = _p;
        std::sort(p.begin(), p.end());
        p.erase(std::unique(p.begin(), p.end()), p.end());
        tree.assign(p.size() * 4 + 5, {});
    }

    auto pushup(int rt, int l, int r)
    {
        if (tree[rt].cnt)
            tree[rt].len = p[r + 1] - p[l];
        else if (l == r)
            tree[rt].len = 0;
        else
            tree[rt].len = tree[rt << 1].len + tree[rt << 1 | 1].len;
    }

    auto update(int rt, int l, int r, int x, int y, int val) -> void
    {
        if (r < x || l > y)
            return;
        if (x <= l && r <= y)
        {
            tree[rt].cnt += val;
            pushup(rt, l, r);
            return;
        }
        int mid = (l + r) >> 1;
        update(rt << 1, l, mid, x, y, val);
        update(rt << 1 | 1, mid + 1, r, x, y, val);
        pushup(rt, l, r);
    }

    auto update(T l, T r, int val)
    {
        if (l >= r || p.size() < 2)
            return;
        int x = (int)(std::lower_bound(p.begin(), p.end(), l) - p.begin());
        int y = (int)(std::lower_bound(p.begin(), p.end(), r) - p.begin()) - 1;
        if (x <= y)
            update(1, 0, (int)p.size() - 2, x, y, val);
    }

    auto query() const
    {
        return tree.empty() ? T() : tree[1].len;
    }

    static auto area(const std::vector<std::array<T, 4>> &rect)
    {
        struct Event
        {
            T x1, x2, y;
            int v;
            auto operator<(const Event &rhs) const { return y < rhs.y; }
        };
        std::vector<T> xs;
        std::vector<Event> e;
        for (auto [x1, y1, x2, y2] : rect)
        {
            if (x1 == x2 || y1 == y2)
                continue;
            if (x1 > x2)
                std::swap(x1, x2);
            if (y1 > y2)
                std::swap(y1, y2);
            xs.push_back(x1), xs.push_back(x2);
            e.push_back({x1, x2, y1, 1});
            e.push_back({x1, x2, y2, -1});
        }
        if (e.empty())
            return T();
        std::sort(e.begin(), e.end());
        scanlineSeg seg(xs);
        T ans = 0;
        for (int i = 0; i + 1 < (int)e.size(); ++i)
        {
            seg.update(e[i].x1, e[i].x2, e[i].v);
            ans += seg.query() * (e[i + 1].y - e[i].y);
        }
        return ans;
    }
};
