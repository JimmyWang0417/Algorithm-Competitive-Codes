#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 1.5e5 + 5;
namespace std
{
    template <typename T>
    bool operator<(const complex<T> &lhs, const complex<T> &rhs)
    {
        return make_pair(lhs.real(), lhs.imag()) < make_pair(rhs.real(), rhs.imag());
    }
}
namespace twoDimension
{
    constexpr double eps = 1e-9;
    auto sgn = [](double x)
    {
        return x < -eps ? -1 : (x > eps ? 1 : 0);
    };

    // point
    typedef complex<double> p2;
    auto dot(p2 lhs, p2 rhs)
    {
        return (conj(lhs) * rhs).real();
    }
    auto cross(p2 lhs, p2 rhs)
    {
        return (conj(lhs) * rhs).imag();
    }

    auto perp(p2 p)
    {
        return p2(-p.imag(), p.real());
    }
    auto rot(p2 p, double theta)
    {
        return p * polar(1.0, theta);
    }

    auto translate(p2 lhs, p2 rhs)
    {
        return lhs + rhs;
    }
    auto scale(p2 c, double factor, p2 p)
    {
        return c + (p - c) * factor;
    }

    auto isPerp(p2 p, p2 q)
    {
        return sgn(dot(p, q)) == 0;
    }
    auto angle(p2 a, p2 b)
    {
        return abs(arg(conj(a) * b));
    }
    auto orientAngle(p2 a, p2 b)
    {
        return arg(conj(a) * b);
    }

    auto orient(p2 a, p2 b, p2 c)
    {
        return cross(b - a, c - a);
    }
    auto inAngle(p2 a, p2 b, p2 c, p2 p)
    {
        if (orient(a, b, c) < 0)
            swap(b, c);
        return orient(a, b, p) >= 0 && orient(a, p, c) >= 0;
    }

    // line
    struct line
    {
        p2 v;
        double c;
        line(p2 _v = p2(), double _c = 0) : v(_v), c(_c) {}
        line(p2 p, p2 q) : v(q - p), c(cross(v, p)) {}
        line(double p, double q, double r) : v({q, -p}), c(r) {}

        auto friend operator<(const line &p, const line &q)
        {
            auto ar = arg(p.v) - arg(q.v);
            if (sgn(ar) == 0)
                return dot(p.c * q.v - p.v * q.c, p.v) > 0;
            else
                return ar < 0;
        }

        auto side(p2 p) const
        {
            return cross(v, p) - c;
        }
        // >0 说明是向量左边，<0说明是向量右边
        auto dist(p2 p) const
        {
            return abs(side(p)) / abs(p);
        }
        auto sqDist(p2 p) const
        {
            return side(p) * side(p) / norm(p);
        }
        auto perpThrough(p2 p) const
        {
            return line(p, p + perp(v));
        }
        auto cmpProj(p2 p, p2 q) const
        {
            return dot(v, p) < dot(v, q);
        }
        auto translate(p2 p) const
        {
            return line(v, c + cross(v, p));
        }
        auto shiftLeft(double dist) const
        {
            return line(v, c + dist * abs(v));
        }
        auto friend inter(line l1, line l2) -> pair<bool, p2>
        {
            double d = cross(l1.v, l2.v);
            if (sgn(d) == 0)
                return {false, 0};
            else
                return {true, (l2.v * l1.c - l1.v * l2.c) / d};
        }
        auto proj(p2 p) const
        {
            return p - perp(v) * side(p) / norm(v);
        }
        auto refl(p2 p) const
        {
            return p - 2.0 * perp(v) * side(p) / norm(v);
        }
        friend auto bisector(line l1, line l2, bool interior)
        // if interior = true 则是内角平分线
        // 否则则是外角平分线
        {
            double sign = interior ? 1 : -1;
            return line(l2.v / abs(l2.v) + l1.v / abs(l1.v) * sign, l2.c / abs(l2.v) + l1.c / abs(l1.v) * sign);
        }
    };

    // segment
    auto onSegment(p2 a, p2 b, p2 p)
    {
        return sgn(orient(a, b, p)) == 0 && dot(a - p, b - p) <= 0;
    }
    auto properInter(p2 a, p2 b, p2 c, p2 d) -> pair<bool, p2>
    {
        double oa = orient(c, d, a);
        double ob = orient(c, d, b);
        double oc = orient(a, b, c);
        double od = orient(a, b, d);
        if (oa * ob < 0 && oc * od < 0)
            return {true, (a * ob - b * oa) / (ob - oa)};
        else
            return {false, 0};
    }
    auto inters(p2 a, p2 b, p2 c, p2 d) -> vector<p2>
    {
        auto [x, y] = properInter(a, b, c, d);
        if (x)
            return {y};
        set<p2> se;
        if (onSegment(c, d, a))
            se.insert(a);
        if (onSegment(c, d, b))
            se.insert(b);
        if (onSegment(a, b, c))
            se.insert(c);
        if (onSegment(a, b, d))
            se.insert(d);
        vector<p2> vec;
        for (auto p : se)
            vec.emplace_back(p);
        return vec;
    }
    auto segPoint(p2 a, p2 b, p2 p)
    {
        if (a != b)
        {
            line l(a, b);
            if (l.cmpProj(a, p) && l.cmpProj(p, b))
                return l.dist(p);
        }
        return min(abs(p - a), abs(p - b));
    }
    auto segSeg(p2 a, p2 b, p2 c, p2 d) -> double
    {
        if (properInter(a, b, c, d).first)
            return 0;
        return min({segPoint(a, b, c), segPoint(a, b, d), segPoint(c, d, a), segPoint(c, d, b)});
    }

    // circle
    p2 circumcenter(p2 a, p2 b, p2 c)
    {
        b = b - a, c = c - a;
        return a + perp(b * norm(c) - c * norm(b)) / cross(b, c) / 2.0;
    }
    p2 incenter(p2 a, p2 b, p2 c)
    {
        double A = abs(b - c), B = abs(a - c), C = abs(a - b);
        return (A * a + B * b + C * c) / (A + B + C);
    }
    auto circleLine(p2 o, double r, line l) -> vector<p2>
    {
        double h2 = r * r - l.sqDist(o);
        if (sgn(h2) == 0)
        {
            p2 p = l.proj(o);
            return {p};
        }
        else if (sgn(h2) > 0)
        {
            p2 p = l.proj(o);
            p2 h = l.v * sqrt(h2) / abs(l.v);
            return {p - h, p + h};
        }
        else
            return {};
    }
    auto circleCircle(p2 o1, double r1, p2 o2, double r2) -> vector<p2>
    {
        p2 d = o2 - o1;
        double d2 = norm(d);
        if (sgn(d2) == 0)
            return {};
        double pd = (d2 + r1 * r1 - r2 * r2) / 2; // |O1P|*d
        double h2 = r1 * r1 - pd * pd / d2;
        if (sgn(h2) == 0)
        {
            p2 p = o1 + d * pd / d2;
            return {p};
        }
        else if (sgn(h2) == 1)
        {
            p2 p = o1 + d * pd / d2, h = perp(d) * sqrt(h2 / d2);
            return {p - h, p + h};
        }
        else
            return {};
    }
    auto tangents(p2 o1, double r1, p2 o2, double r2, bool inner) -> vector<pair<p2, p2>>
    {
        if (inner)
            r2 = -r2;
        p2 d = o2 - o1;
        double dr = r1 - r2, d2 = norm(d), h2 = d2 - dr * dr;
        if (sgn(d2) == 0)
            return {};
        if (sgn(h2) == 0)
        {
            p2 v = d * dr / h2;
            return {{o1 + v * r1, o2 + v * r2}};
        }
        else if (sgn(h2) == 1)
        {
            p2 v = (d * dr + perp(d) * sqrt(h2)) / d2, w = (d * dr - perp(d) * sqrt(h2)) / d2;
            return {{o1 + v * r1, o2 + v * r2}, {o1 + w * r1, o2 + w * r2}};
        }
        else
            return {};
    }

    // polygon
    typedef vector<p2> polygon;
    auto areaPolygon(const polygon &p)
    {
        double area = 0;
        for (int i = 0; i < (int)p.size(); ++i)
            area += cross(p[i], p[(i + 1) % p.size()]);
        return abs(area) / 2.0;
    }
    auto inPolygon(const polygon &p, p2 q, bool strict = false)
    {
        bool flag = false;
        for (int i = 0; i < (int)p.size(); ++i)
        {
            if (onSegment(p[i], p[(i + 1) % p.size()], q))
                return !strict;
            auto crossRay = [](p2 a, p2 b, p2 c)
            {
                auto above = [](p2 _a, p2 _b)
                {
                    return _a.imag() <= _b.imag();
                };
                return (above(a, c) - above(a, b)) * orient(a, b, c) > 0;
            };
            if (crossRay(q, p[i], p[(i + 1) % p.size()]))
                flag ^= 1;
        }
        return flag;
    }

    // half plane
    auto halfPlane(vector<line> li)
    {
        sort(li.begin(), li.end());
        vector<p2> vec(li.size());
        vector<line> que(li.size());
        int l = 0, r = -1;
        for (int i = 0; i < (int)li.size(); ++i)
        {
            if (i && sgn(cross(li[i - 1].v, li[i].v)) == 0)
                continue;
            while (r - l >= 1 && sgn(li[i].side(vec[r])) <= 0)
                --r;
            while (r - l >= 1 && sgn(li[i].side(vec[l + 1])) <= 0)
                ++l;
            que[++r] = li[i];
            if (r - l >= 1)
                vec[r] = inter(que[r], que[r - 1]).second;
        }

        while (r - l >= 1 && sgn(que[l].side(vec[r])) <= 0)
            --r;
        vec[l] = inter(que[l], que[r]).second;

        vec.erase(vec.begin() + r + 1, vec.end());
        vec.erase(vec.begin(), vec.begin() + l);

        que.erase(que.begin() + r + 1, que.end());
        que.erase(que.begin(), que.begin() + l);

        return make_pair(vec, que);
    }
};
using namespace twoDimension;
inline void _main()
{
    int n;
    cin >> n;
    vector<line> li;
    for (int _n = 0; _n < n; ++_n)
    {
        int m;
        cin >> m;
        vector<p2> p;
        for (int i = 0; i < m; ++i)
        {
            double x, y;
            cin >> x >> y;
            p.emplace_back(x, y);
        }
        for (int i = 0; i < (int)p.size(); ++i)
            li.push_back(line(p[i], p[(i + 1) % p.size()]));
    }
    cout << fixed << setprecision(3) << areaPolygon(halfPlane(li).first) << '\n';
}
inline void _clear()
{
}
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    // cin >> T;
    for (int cas = 1; cas <= T; ++cas)
    {
        _main();
        _clear();
    }
    return 0;
}