struct NearestPoints
{
    struct Point
    {
        i64 x, y;
        auto operator<=>(const Point &) const = default;
    };
    int n;
    vector<Point> p, tmp;
    i64 distance = numeric_limits<i64>::max();
    pair<Point, Point> points;
    static auto calc(const Point &a, const Point &b)
    {
        i64 x = a.x - b.x, y = a.y - b.y;
        return x * x + y * y;
    }
    auto update(const Point &a, const Point &b, i64 &res) -> void
    {
        i64 now = calc(a, b);
        res = min(res, now);
        if (now < distance)
            distance = now, points = {a, b};
    }
    auto solve(int l, int r) -> i64
    {
        auto cmp = [](const Point &a, const Point &b)
        { return tie(a.y, a.x) < tie(b.y, b.x); };
        i64 res = numeric_limits<i64>::max();
        if (r - l <= 3)
        {
            for (int i = l; i < r; ++i)
                for (int j = i + 1; j < r; ++j)
                    update(p[i], p[j], res);
            sort(p.begin() + l, p.begin() + r, cmp);
            return res;
        }
        int mid = (l + r) >> 1;
        i64 midx = p[mid].x;
        res = min(solve(l, mid), solve(mid, r));
        merge(p.begin() + l, p.begin() + mid, p.begin() + mid, p.begin() + r, tmp.begin(), cmp);
        copy(tmp.begin(), tmp.begin() + r - l, p.begin() + l);
        int tot = 0;
        for (int i = l; i < r; ++i)
        {
            i64 dx = p[i].x - midx;
            if (dx * dx >= res)
                continue;
            for (int j = tot - 1; j >= 0; --j)
            {
                i64 dy = p[i].y - tmp[j].y;
                if (dy * dy >= res)
                    break;
                update(p[i], tmp[j], res);
            }
            tmp[tot++] = p[i];
        }
        return res;
    }
    NearestPoints(vector<Point> _p) : n((int)_p.size()), p(move(_p)), tmp(n)
    {
        sort(p.begin(), p.end(), [](const Point &a, const Point &b)
             { return tie(a.x, a.y) < tie(b.x, b.y); });
        if (n > 1)
            solve(0, n);
    }
};
