#pragma once
#include <algorithm>
#include <limits>
#include <utility>
#include <vector>

#define lc(x) tree[x].ls
#define rc(x) tree[x].rs

struct lichao
{
    using db = long double;
    static constexpr db negInf = -1e100L;

    struct Line
    {
        db k = 0, b = negInf;
        int id = 0;
        auto calc(long long x) const { return k * x + b; }
    };

    struct Node
    {
        int ls = 0, rs = 0, line = 0;
    };

    long long L = 1, R = 0;
    int root = 0;
    vector<Line> line;
    vector<Node> tree;

    lichao() : line(1), tree(1) {}
    lichao(long long l, long long r) : L(l), R(r), line(1), tree(1) {}

    void clear()
    {
        root = 0;
        line.resize(1);
        tree.resize(1);
        line[0] = Line();
        tree[0] = Node();
    }

    void build(long long l, long long r)
    {
        L = l, R = r;
        root = 0;
        line.resize(1);
        tree.resize(1);
        line[0] = Line();
        tree[0] = Node();
    }

    auto newnode()
    {
        tree.push_back(Node());
        return (int)tree.size() - 1;
    }

    auto addLine(db k, db b, int id = -1)
    {
        if (id == -1)
            id = (int)line.size();
        line.push_back({k, b, id});
        return (int)line.size() - 1;
    }

    auto better(int x, int y, long long pos) const
    {
        db vx = line[x].calc(pos), vy = line[y].calc(pos);
        if (vx != vy)
            return vx > vy;
        return line[x].id < line[y].id;
    }

    auto insert(int rt, long long l, long long r, int id) -> int
    {
        if (!rt)
            rt = newnode();
        if (!tree[rt].line)
        {
            tree[rt].line = id;
            return rt;
        }
        long long mid = (l + r) >> 1;
        int cur = tree[rt].line;
        if (better(id, cur, mid))
            swap(id, tree[rt].line), cur = tree[rt].line;
        if (l == r)
            return rt;
        if (better(id, cur, l))
            lc(rt) = insert(lc(rt), l, mid, id);
        else if (better(id, cur, r))
            rc(rt) = insert(rc(rt), mid + 1, r, id);
        return rt;
    }

    auto insertLine(db k, db b, int id = -1)
    {
        root = insert(root, L, R, addLine(k, b, id));
    }

    auto insertSeg(int rt, long long l, long long r, long long x, long long y, int id) -> int
    {
        if (r < x || l > y)
            return rt;
        if (x <= l && r <= y)
            return insert(rt, l, r, id);
        if (!rt)
            rt = newnode();
        long long mid = (l + r) >> 1;
        lc(rt) = insertSeg(lc(rt), l, mid, x, y, id);
        rc(rt) = insertSeg(rc(rt), mid + 1, r, x, y, id);
        return rt;
    }

    auto insertSeg(long long l, long long r, db k, db b, int id = -1)
    {
        if (l > r)
            swap(l, r);
        root = insertSeg(root, L, R, l, r, addLine(k, b, id));
    }

    auto insertSegment(long long x1, db y1, long long x2, db y2, int id = -1)
    {
        if (x1 == x2)
            return insertSeg(x1, x1, 0, max(y1, y2), id);
        db k = (y2 - y1) / (x2 - x1);
        db b = y1 - k * x1;
        insertSeg(min(x1, x2), max(x1, x2), k, b, id);
    }

    auto best(pair<db, int> lhs, pair<db, int> rhs) const
    {
        if (lhs.first != rhs.first)
            return lhs.first > rhs.first ? lhs : rhs;
        if (!lhs.second)
            return rhs;
        if (!rhs.second)
            return lhs;
        return lhs.second < rhs.second ? lhs : rhs;
    }

    auto query(int rt, long long l, long long r, long long pos) const -> pair<db, int>
    {
        if (!rt)
            return {negInf, 0};
        pair<db, int> res = {negInf, 0};
        if (tree[rt].line)
        {
            const auto &cur = line[tree[rt].line];
            res = {cur.calc(pos), cur.id};
        }
        if (l == r)
            return res;
        long long mid = (l + r) >> 1;
        if (pos <= mid)
            return best(res, query(lc(rt), l, mid, pos));
        return best(res, query(rc(rt), mid + 1, r, pos));
    }

    auto query(long long pos) const
    {
        return query(root, L, R, pos);
    }
};

#undef lc
#undef rc
