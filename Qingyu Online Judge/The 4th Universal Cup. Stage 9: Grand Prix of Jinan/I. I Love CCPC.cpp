#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/priority_queue.hpp>
using namespace std;
typedef int64_t i64;
typedef uint64_t u64;
typedef __int128_t i128;
typedef __uint128_t u128;
typedef __float80 f80;
typedef __float128 f128;

struct pam
{
    struct node
    {
        int ch[26];
        int fail, len;
        int dep, ans;
        auto &operator[](int x) { return ch[x]; }
        const auto &operator[](int x) const { return ch[x]; }
    };
    vector<int> where;
    vector<array<int, 23>> fa;
    vector<node> point;
    pam() = default;
    pam(const string &str) : point(2)
    {
        auto newnode = [&]()
        {
            point.emplace_back();
            return (int)point.size() - 1;
        };
        point[0].fail = 1;
        point[1].len = -1;
        where.resize((int)str.size());
        for (int n = 0, las = 1; n < (int)str.size(); ++n)
        {
            int c = str[n] - 'a';
            auto find = [&](int now)
            {
                while (str[n] != str[n - point[now].len - 1])
                    now = point[now].fail;
                return now;
            };
            int cur = find(las), now = point[cur][c];
            if (!now)
            {
                now = newnode();
                point[now].len = point[cur].len + 2;
                point[now].fail = point[find(point[cur].fail)][c];
                point[now].dep = point[point[now].fail].dep + (point[now].len >= 3);
                point[now].ans = point[point[now].fail].ans +
                                 (point[point[now].fail].len >= 3 &&
                                  n - point[point[now].fail].len >= 0 &&
                                  str[n - point[point[now].fail].len] == str[n - point[point[now].fail].len + 1]);
                point[cur][c] = now;
            }
            where[n] = las = now;
        }
        fa.resize(point.size());
        for (int i = 1; i < (int)point.size(); ++i)
        {
            fa[i][0] = point[i].fail;
            for (int j = 0; j < 20; ++j)
                fa[i][j + 1] = fa[fa[i][j]][j];
        }
    }
    auto find(int pos, int len)
    {
        int u = where[pos];
        if (point[u].len <= len)
            return u;
        for (int i = 20; i >= 0; --i)
            if (point[fa[u][i]].len > len)
                u = fa[u][i];
        return fa[u][0];
    }
};
struct Main
{
    int m;
    string str;
    string s, t, L, R;
    Main()
    {
        cin >> str >> m;
        vector<pair<int, int>> p(m + 1);
        p[0] = make_pair(0, (int)str.length() - 1);
        auto rev = [](string _s)
        {
            reverse(_s.begin(), _s.end());
            return _s;
        };
        for (int i = 1, l = 0, r = (int)str.length() - 1; i <= m; ++i)
        {
            string c;
            cin >> c;
            if (c.front() == 'L')
            {
                L.push_back(c.back());
                --l;
            }
            else
            {
                R.push_back(c.back());
                ++r;
            }
            p[i] = make_pair(l, r);
        }
        s = rev(L) + str + R;
        t = rev(R) + rev(str) + L;
        auto tree = pam(s);
        auto revtree = pam(t);
        for (int i = 0; i <= m; ++i)
        {
            p[i].first += (int)L.length();
            p[i].second += (int)L.length();
        }
        i64 res = 0;
        for (int i = 0, l = p[0].first, r = p[0].first + 2; i <= m; ++i)
        {
            int ql = p[i].first, qr = p[i].second;
            while (l > ql)
            {
                if (s[l - 1] == s[l])
                {
                    int u = revtree.find((int)s.length() - l - 1, r - l + 1);
                    res += revtree.point[u].dep;
                }
                --l;
            }
            while (r < qr)
            {
                ++r;
                int u = tree.find(r, r - l);

                res += tree.point[u].ans +
                       (tree.point[u].len >= 3 &&
                        r - tree.point[u].len >= 0 &&
                        s[r - tree.point[u].len] == s[r - tree.point[u].len + 1]);
            }
            cout << res << ' ';
        }
        cout << '\n';
    }
};
signed main()
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    int T = 1;
    cin >> T;
    while (T--)
        Main();
    return 0;
}
