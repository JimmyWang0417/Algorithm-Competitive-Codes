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
    double areaPolygon(const polygon &p)
    {
        double area = 0;
        for (int i = 0; i < (int)p.size(); ++i)
            area += cross(p[i], p[(i + 1) % p.size()]);
        return abs(area) / 2.0;
    }
    bool inPolygon(const polygon &p, p2 q, bool strict = false)
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
        li.push_back(line(p2(-1e9, -1e9), p2(1e9, -1e9)));
        li.push_back(line(p2(1e9, -1e9), p2(1e9, 1e9)));
        li.push_back(line(p2(1e9, 1e9), p2(-1e9, 1e9)));
        li.push_back(line(p2(-1e9, 1e9), p2(-1e9, -1e9)));

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
namespace threeDimension
{
    constexpr double eps = 1e-9;
    auto sgn = [](double x)
    {
        return x < -eps ? -1 : (x > eps ? 1 : 0);
    };

    // point
    struct p3
    {
        double x, y, z;
        p3(double _x = 0, double _y = 0, double _z = 0) : x(_x), y(_y), z(_z) {}
        auto operator<(const p3 &rhs) const
        {
            return tie(x, y, z) < tie(rhs.x, rhs.y, rhs.z);
        }
        auto operator+(p3 p) const
        {
            return p3(x + p.x, y + p.y, z + p.z);
        }
        auto operator-(p3 p) const
        {
            return p3(x - p.x, y - p.y, z - p.z);
        }
        auto operator*(double p) const
        {
            return p3(x * p, y * p, z * p);
        }
        auto operator/(double p) const
        {
            return p3(x / p, y / p, z / p);
        }

        auto friend dot(p3 a, p3 b)
        {
            return a.x * b.x + a.y * b.y + a.z * b.z;
        }
        auto friend cross(p3 a, p3 b)
        {
            return p3(a.y * b.z - a.z * b.y, a.z * b.x - a.x * b.z, a.x * b.y - a.y * b.x);
        }
        auto friend mixed(p3 a, p3 b, p3 c)
        {
            return dot(cross(a, b), c);
        }
        auto friend norm(p3 a)
        {
            return dot(a, a);
        }
        auto friend abs(p3 a)
        {
            return sqrt(norm(a));
        }
        auto friend angle(p3 a, p3 b)
        {
            return acos(clamp(dot(a, b) / abs(a) / abs(b), -1.0, 1.0));
        }
        auto friend orient(p3 p, p3 q, p3 r, p3 n)
        {
            return mixed(q - p, r - p, n);
        }
    };

    // plane
    struct plane
    {
        p3 n;
        double d;
        plane(p3 _n = p3(), double _d = 0) : n(_n), d(_d) {}
        plane(p3 _n, p3 _p) : n(_n), d(dot(_n, _p)) {}
        plane(p3 p, p3 q, p3 r) : plane(cross(q - p, r - p), p) {}

        auto side(p3 p) const
        {
            return dot(n, p) - d;
        }
        auto dist(p3 p) const
        {
            return dot(n, p) / abs(n);
        }

        auto translate(p3 t) const
        {
            return plane(n, d + dot(n, t));
        }
        auto shiftUp(double dist) const
        {
            return plane(n, d + abs(n) * dist);
        }
        auto proj(p3 p) const
        {
            return p - n * side(p) / norm(n);
        }
        auto refl(p3 p) const
        {
            return p - n * side(p) * 2 / norm(n);
        }

        auto friend angle(plane a, plane b)
        {
            return angle(a.n, b.n);
        }
    };

    // Coordinate System
    struct coords
    {
        p3 o, dx, dy, dz;
        coords(p3 p, p3 q, p3 r) : o(p)
        {
            dx = (q - p) / abs(q - p);
            dz = cross(dx, (r - p) / abs(r - p));
            dy = cross(dz, dx);
        }

        auto pos2d(p3 p) const
        {
            p = p - o;
            return twoDimension::p2(dot(p, dx), dot(p, dy));
        }
        auto pos3d(p3 p) const
        {
            p = p - o;
            return p3(dot(p, dx), dot(p, dy), dot(p, dz));
        }
    };
    struct line
    {
        p3 d, o;
        line(p3 p = p3(), p3 q = p3()) : d(q - p), o(p) {}
        line(plane p, plane q)
        {
            d = cross(p.n, q.n);
            o = cross((cross(q.n, p.d) - cross(p.n, q.d)), d) / norm(d);
        }
        auto sqDist(p3 p) const
        {
            return norm(cross(d, p - o)) / norm(d);
        }
        auto dist(p3 p) const
        {
            return sqrt(sqDist(p));
        }
        auto cmpProj(p3 p, p3 q) const
        {
            return dot(d, p) < dot(d, q);
        }
        auto proj(p3 p) const
        {
            return o + d * dot(d, p - o) / norm(d);
        }
        auto refl(p3 p) const
        {
            return proj(p) * 2 - p;
        }
        auto friend inter(plane p, line l)
        {
            return l.o - l.d * p.side(l.o) / dot(p.n, l.d);
        }
        auto friend dist(line l1, line l2)
        {
            p3 n = cross(l1.d, l2.d);
            if (sgn(norm(n)) == 0)
                return l1.dist(l2.o);
            return abs(dot(l2.o - l1.o, n)) / abs(n);
        }
        auto friend closestOnL1(line l1, line l2)
        {
            auto n2 = cross(l2.d, cross(l1.d, l2.d));
            return l1.o + l1.d * dot(l2.o - l1.o, n2) / dot(l1.d, n2);
        }
        auto friend angle(line a, line b)
        {
            return angle(a.d, b.d);
        }
        auto friend perpThrough(plane p, p3 o)
        {
            return line(o, o + p.n);
        }
        auto friend perpThrough(line l, p3 o)
        {
            return plane(l.d, o);
        }
    };

    // polygon
    typedef vector<p3> polygon;
    auto vectorArea2(const polygon &p)
    {
        p3 res = p3();
        for (int i = 0; i < (int)p.size(); ++i)
            res = res + cross(p[i], p[(i + 1) % p.size()]);
        return res;
    }
    auto area(const polygon &p)
    {
        return abs(vectorArea2(p)) / 2;
    }

    // polyhedron
    typedef vector<polygon> polyhedron;
    auto reorient(polyhedron &p)
    {
        int n = (int)p.size();
        vector<vector<pair<int, bool>>> g(n);
        map<pair<p3, p3>, int> mp;
        for (int u = 0; u < n; ++u)
        {
            for (int i = 0; i < (int)p[u].size(); ++i)
            {
                auto a = p[u][i], b = p[u][(i + 1) % p[u].size()];
                if (mp[{a, b}])
                {
                    int v = mp[{a, b}];
                    g[u].emplace_back(v, true);
                    g[v].emplace_back(u, true);
                }
                else if (mp[{b, a}])
                {
                    int v = mp[{b, a}];
                    g[u].emplace_back(v, false);
                    g[v].emplace_back(u, false);
                }
                else
                    mp[{a, b}] = i;
            }
        }
        vector<bool> flip(n), vis(n);
        queue<int> q;
        q.push(0);
        while (!q.empty())
        {
            int u = q.front();
            q.pop();
            for (auto [v, f] : g[u])
            {
                if (vis[v])
                    continue;
                flip[v] = flip[u] ^ f;
                vis[v] = true;
                q.push(v);
            }
            if (flip[u])
                reverse(p[u].begin(), p[u].end());
        }
    }
    auto volume(const polyhedron &p)
    {
        double res = 0;
        for (auto q : p)
            res += dot(q.front(), vectorArea2(q));
        return res / 6;
    }

    // sphere
    auto sphereLine(p3 o, double r, line l) -> vector<p3>
    {
        double h2 = r * r - l.sqDist(o);
        if (sgn(h2) == -1)
            return {};
        else if (sgn(h2) == 0)
        {
            p3 p = l.proj(o);
            return {p};
        }
        else
        {
            p3 p = l.proj(o);
            p3 h = l.d * sqrt(h2) / abs(l.d);
            return {p - h, p + h};
        }
    }
    auto greatCircleDist(p3 o, double r, p3 a, p3 b)
    {
        return r * angle(a - o, b - o);
    }
    auto onSphSegment(p3 a, p3 b, p3 p)
    {
        p3 n = cross(a, b);
        if (sgn(norm(n)))
            return sgn(norm(cross(a, p))) == 0 && dot(a, p) > 0;
        return sgn(dot(n, p)) == 0 && mixed(n, a, p) >= 0 && mixed(n, p, b) >= 0;
    }
    auto properInter(p3 a, p3 b, p3 c, p3 d) -> pair<bool, p3>
    {
        p3 ab = cross(a, b), cd = cross(c, d);
        int oa = sgn(dot(cd, a));
        int ob = sgn(dot(cd, b));
        int oc = sgn(dot(ab, c));
        int od = sgn(dot(ab, d));
        return {oa != ob && oc != od && oa != oc, cross(ab, cd) * od};
    }
    auto intersSph(p3 a, p3 b, p3 c, p3 d) -> vector<p3>
    {
        auto [f, out] = properInter(a, b, c, d);
        if (f)
            return {out};

        set<p3> se;
        if (onSphSegment(c, d, a))
            se.insert(a);
        if (onSphSegment(c, d, b))
            se.insert(b);
        if (onSphSegment(a, b, c))
            se.insert(c);
        if (onSphSegment(a, b, d))
            se.insert(d);
        vector<p3> vec;
        for (auto p : se)
            vec.emplace_back(p);
        return vec;
    }
    auto angleSph(p3 a, p3 b, p3 c) // ∠BAC
    {
        return angle(cross(a, b), cross(a, c));
    }
    auto orientAngleSph(p3 a, p3 b, p3 c)
    {
        if (dot(a, cross(b, c)) >= 0)
            return angleSph(a, b, c);
        else
            return 2 * M_PI - angleSph(a, b, c);
    }
    auto areaOnSphere(const polygon &p, double r) // 逆时针给出点的多边形
    {
        double sum = -M_PI * ((int)p.size() - 2);
        for (int i = 0; i < (int)p.size(); ++i)
            sum += orientAngleSph(p[(i + 1) % p.size()], p[(i + 2) % p.size()], p[i]);
        return r * r * sum;
    }

    // convex hull
    auto convexHull(polygon p)
    {
        int n = (int)p.size();
        mt19937 rnd(chrono::system_clock::now().time_since_epoch().count());
        auto range = uniform_real_distribution<>(-eps, eps);
        for (auto &[x, y, z] : p)
        {
            x += range(rnd);
            y += range(rnd);
            z += range(rnd);
        }
        vector<array<int, 3>> f{{0, 1, 2}, {2, 1, 0}}, g;
        auto see = [&](auto a, auto b)
        {
            auto x = p[a[0]],
                 y = p[a[1]],
                 z = p[a[2]];
            return dot(b - x, cross(y - z, z - x)) > 0;
        };
        vector<vector<bool>> vis(n, vector<bool>(n));
        for (int i = 3, v; i < (int)p.size(); ++i)
        {
            for (auto h : f)
            {
                if (!(v = see(h, p[i])))
                    g.push_back(h);
                for (int j = 0; j < 3; ++j)
                    vis[h[j]][h[(j + 1) % 3]] = v;
            }
            for (auto h : f)
                for (int j = 0; j < 3; ++j)
                {
                    int x = h[j], y = h[(j + 1) % 3];
                    if (vis[x][y] && !vis[y][x])
                        g.push_back({x, y, i});
                }
            swap(f, g);
            g.clear();
        }
        polyhedron q(f.size(), polygon(3));
        for (int i = 0; i < (int)f.size(); ++i)
        {
            for (int j = 0; j < 3; ++j)
                q[i][j] = p[f[i][j]];
        }
        return q;
    }
}