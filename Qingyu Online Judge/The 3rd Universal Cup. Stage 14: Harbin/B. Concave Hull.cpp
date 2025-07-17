#include <bits/stdc++.h>
using namespace std;

#define allr(x) (x).rbegin(), (x).rend()
#define all(x) (x).begin(), (x).end()
using LD = long double;
// eps不一定是越精度高越好！
const LD eps = 1e-8; // 精度，可按需要增加至1e-12之类的(?)
const LD pi = 3.141592653589793238462643438328;
int sign(LD x)
{ // 符号函数
    if (fabs(x) < eps)
        return 0;
    if (x < 0)
        return -1;
    return 1;
}
int dcmp(LD x, LD y)
{ // 比较函数
    if (fabs(x - y) < eps)
        return 0;
    if (x < y)
        return -1;
    return 1;
}

using PDD = pair<LD, LD>;
#define x first
#define y second

// 基本运算符重载
PDD operator+(PDD a, PDD b) { return PDD{a.x + b.x, a.y + b.y}; }
PDD operator-(PDD a, PDD b) { return PDD{a.x - b.x, a.y - b.y}; }
PDD operator*(LD k, PDD a) { return PDD{k * a.x, k * a.y}; }
PDD operator*(PDD a, LD k) { return PDD{k * a.x, k * a.y}; }
PDD operator/(PDD a, LD k) { return PDD{a.x / k, a.y / k}; }

LD dot(PDD a, PDD b)
{ // 内积
    return a.x * b.x + a.y * b.y;
}

LD cross(PDD a, PDD b)
{ // 叉积
    return a.x * b.y - b.x * a.y;
}

// 取模（长度）
LD get_length(PDD a)
{
    return dot(a, a);
}

// 点p; 直线由a, b两点表示
// 点到直线的距离
LD dis2line(PDD p, PDD a, PDD b)
{
    PDD v1 = b - a, v2 = p - a;
    return fabs(cross(v1, v2) / get_length(v1));
}

// 计算**任意**多边形面积（不一定凸）
LD polygon_area(vector<PDD> p)
{
    LD s = 0;
    for (int i = 1; i + 1 < p.size(); i++)
        s += cross(p[i] - p[0], p[i + 1] - p[i]);
    return s / 2;
}

LD area(PDD a, PDD b, PDD c)
{
    return cross(b - a, c - a);
}

vector<PDD> Andrew(vector<PDD> &a)
{
    sort(a.begin(), a.end(), [](const PDD &A, const PDD &B)
         {
        if(dcmp(A.y,B.y)==0) return dcmp(A.x,B.x)==-1;
        return dcmp(A.y,B.y)==-1; });
    vector<PDD> up = {a[0]};
    for (int i = 1; i < a.size(); i++)
    {
        while (up.size() >= 2 && sign(area(up[up.size() - 2], up.back(), a[i])) >= 0)
            up.pop_back();
        up.push_back(a[i]);
    }
    vector<PDD> down = {up.back()};
    for (int i = a.size() - 1; i >= 0; i--)
    {
        while (down.size() >= 2 && sign(area(down[down.size() - 2], down.back(), a[i])) >= 0)
            down.pop_back();
        down.push_back(a[i]);
    }
    reverse(all(down));
    down.pop_back();
    up.erase(up.begin());
    down.insert(down.end(), allr(up));
    return down;
}

void solve()
{
    int n;
    cin >> n;
    vector<PDD> tip(n);
    for (int i = 0; i < n; i++)
    {
        cin >> tip[i].x >> tip[i].y;
    }
    vector<PDD> big = Andrew(tip);
    vector<PDD> s_tip;
    map<PDD, int> vis;
    for (auto &x : big)
    {
        vis[x] = 1;
        // cout<<x.x<<" "<<x.y<<"\n";
    }
    for (auto &x : tip)
    {
        if (!vis[x])
        {
            s_tip.push_back(x);
        }
    }
    if (s_tip.empty())
    {
        cout << -1 << "\n";
        return;
    }
    vector<PDD> small = Andrew(s_tip);
    if (small.empty())
    {
        cout << -1 << "\n";
        return;
    }
    // cout<<small[0].x<<" "<<small[0].y<<"\n";
    // reverse(big.begin(),big.end());
    LD tot = polygon_area(big);
    int pos = 0;
    LD ans = 0;
    // small.pop_back();
    // big.pop_back();
    LD d = 9e18;
    for (int i = 0; i < small.size(); i++)
    {
        if (dis2line(small[i], big[0], big[1]) < d)
        {
            d = dis2line(small[i], big[0], big[1]);
            pos = i;
        }
    }
    for (int i = 0; i < big.size(); i++)
    {
        LD dis = 9e18;
        while (dis2line(small[pos], big[i], big[(i + 1) % big.size()]) < dis)
        {
            dis = dis2line(small[pos], big[i], big[(i + 1) % big.size()]);
            pos++;
            if (pos >= small.size())
            {
                pos = 0;
            }
        }
        pos--;
        if (pos < 0)
        {
            pos = small.size() - 1;
        }
        ans = fmax(ans, tot - dis * get_length({big[i].x - big[(i + 1) % big.size()].x, big[i].y - big[(i + 1) % big.size()].y}) / 2);
    }
    cout << (long long)(ans * 2 + 1e-10) << "\n";
}

int main()
{
    ios::sync_with_stdio(false);
    cin.tie(nullptr);

    int t;
    cin >> t;
    while (t--)
    {
        solve();
    }
}