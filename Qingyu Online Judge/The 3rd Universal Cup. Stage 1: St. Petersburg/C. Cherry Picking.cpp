#include <bits/stdc++.h>
using namespace std;

#define ONLINE
#ifndef ONLINE
char DEBUG_BUFFER[1000];
#define debug(...)                                                        \
    {                                                                     \
        sprintf(DEBUG_BUFFER, ##__VA_ARGS__);                             \
        cerr << "\033[1;36m" << DEBUG_BUFFER << "\033[0;2m" << "\033[0m"; \
    }
#else
#define debug(...) ;
#endif

using LL = long long;
using PII = pair<int, int>;

#define all(x) (x).begin(), (x).end()
#define allr(x) (x).rbegin(), (x).rend()

#define FAST_IO                      \
    {                                \
        ios::sync_with_stdio(false); \
        cin.tie(nullptr);            \
    }
inline int read()
{
    static int x;
    cin >> x;
    return x;
}
inline LL readLL()
{
    static LL x;
    cin >> x;
    return x;
}
mt19937_64 rng(chrono::system_clock::now().time_since_epoch().count());

#define ls (id << 1)
#define rs (id << 1 | 1)
class SGT
{ // 以线段树维护区间最大值为例，支持区间修改
private:
    struct Node
    {
        int l, r;
        LL lmx, rmx, sum, mx;
        friend Node operator+(const Node &A, const Node &B)
        {
            Node ret;
            ret.l = A.l, ret.r = B.r;

            ret.sum = A.sum + B.sum;
            ret.lmx = max({0ll, A.lmx, A.sum + B.lmx});
            ret.rmx = max({0ll, B.rmx, B.sum + A.rmx});
            ret.mx = max({A.mx, B.mx, ret.lmx, A.rmx + B.lmx, ret.rmx});

            return ret;
        }
    };
    vector<Node> q;
    void build(int l, int r, int id = 1)
    {
        if (l == r)
        {
            q[id].l = l, q[id].r = r;
            q[id].sum = q[id].lmx = q[id].rmx = q[id].mx = 0ll;
            return;
        }
        int mid = l + r >> 1;
        build(l, mid, ls);
        build(mid + 1, r, rs);
        q[id] = q[ls] + q[rs];
    }

public:
    SGT(int n)
    {
        init(n);
    }
    void init(int n)
    {
        q.resize(n * 5);
        build(1, n);
    }
    void modify(int pos, int val, int id = 1)
    {
        if (q[id].l == q[id].r)
        {
            // modify the value
            q[id].sum = q[id].lmx = q[id].rmx = q[id].mx = val;
            return;
        }
        int mid = q[id].l + q[id].r >> 1;
        if (pos <= mid)
            modify(pos, val, ls);
        else if (pos > mid)
            modify(pos, val, rs);
        q[id] = q[ls] + q[rs];
    }
    Node query(int l, int r, int id = 1)
    {
        if (q[id].l == l && q[id].r == r)
            return q[id];
        int mid = q[id].l + q[id].r >> 1;
        if (r <= mid)
            return query(l, r, ls);
        else if (l > mid)
            return query(l, r, rs);
        return query(l, mid, ls) + query(mid + 1, r, rs);
    }
    //	int get(int pos,int id=1){
    //		if(q[id].l==q[id].r) return q[id].mx;
    //		spread(id);
    //		int mid=q[id].l+q[id].r>>1;
    //		if(pos<=mid) return get(pos,ls);
    //		return get(pos,rs);
    //	}
};
#undef ls
#undef rs

int main()
{
    int n = read(), lim = read();
    vector<int> a(n + 1), b;
    for (int i = 1; i <= n; i++)
    {
        cin >> a[i];
        b.push_back(a[i]);
    }
    string s;
    cin >> s;
    sort(all(b));
    b.erase(unique(all(b)), b.end());
    vector<PII> c;
    for (int i = 1; i <= n; i++)
    {
        a[i] = lower_bound(all(b), a[i]) - b.begin() + 1;
        c.push_back({a[i], i});
        debug("%d %d\n", a[i], i);
    }
    sort(allr(c));
    SGT sgt(n);
    int ans = 0;
    {
        int i = 0;
        for (int nw = b.size(); nw > 0; nw--)
        {
            debug("nw=%d\n", nw);
            while (i < n && c[i].first == nw)
            {
                debug("\t%d %d %d\n", c[i].first, c[i].second, (int)(s[c[i].second - 1] == '1' ? 1 : -1e6));
                if (s[c[i].second - 1] == '1')
                {
                    sgt.modify(c[i].second, 1);
                }
                else
                {
                    sgt.modify(c[i].second, -1e6);
                }
                i++;
            }
            debug("mx=%lld\n", sgt.query(1, n).mx);
            if (sgt.query(1, n).mx >= lim)
            {
                ans = nw;
                break;
            }
        }
    }
    if (ans)
    {
        ans = b[ans - 1];
    }
    cout << ans;
    return 0;
}

/* stuff you should look for
 * int overflow, array bounds
 * special cases (n=1?)
 * do smth instead of nothing and stay organized
 * WRITE STUFF DOWN
 * DON'T GET STUCK ON ONE APPROACH
 */