#include <bits/stdc++.h>
#include <complex>
typedef long long ll;
typedef unsigned long long ull;
#define lowbit(x) ((x) & (-(x)))
using namespace std;
namespace std
{
    template <typename T>
    bool operator<(const complex<T> &lhs, const complex<T> &rhs)
    {
        return tie(lhs.real(), lhs.imag()) < tie(rhs.real(), rhs.imag());
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
        return sgn(dot(n, p)) == 0 && dot(n, cross(a, p)) >= 0 && (dot(n, cross(p, b))) >= 0;
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
signed main()
{
    int n;
    cin >> n;
    threeDimension::polygon p(n);
    for (auto &[x, y, z] : p)
        cin >> x >> y >> z;
    auto q = threeDimension::convexHull(p);
    double area = 0;
    for (auto i : q)
        area += threeDimension::area(i);
    cout << fixed << setprecision(3) << area << '\n';
    return 0;
}