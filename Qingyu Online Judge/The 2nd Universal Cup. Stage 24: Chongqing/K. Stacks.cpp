#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 1e5 + 5;
int n, m;
struct Tree
{
	int lc, rc;
	int x, y;
	ll sumx, sumy; 
} tree[34000005];
#define lc(rt) tree[rt].lc
#define rc(rt) tree[rt].rc
int cnt;
mt19937 rnd(114514);
inline int newnode(int x, int y)
{
	int rt = ++cnt;
	lc(rt) = rc(rt) = 0;
	tree[rt].x = x;
	tree[rt].y = y;
	tree[rt].sumx = tree[rt].x;
	tree[rt].sumy = (ll)tree[rt].x * tree[rt].y;
	return rt;
}
inline void pushup(int rt)
{
	tree[rt].sumx = tree[rt].x + tree[lc(rt)].sumx + tree[rc(rt)].sumx;
	tree[rt].sumy = (ll)tree[rt].x * tree[rt].y + tree[lc(rt)].sumy + tree[rc(rt)].sumy;
}
inline void split(int &rt, ll k)
{
	tree[++cnt] = tree[rt];
	rt = cnt;
	if (tree[rc(rt)].sumx > k)
		split(rc(rt), k);
	else if (tree[rc(rt)].sumx + tree[rt].x > k)
	{
		tree[rt].x -= (int)(k - tree[rc(rt)].sumx);
		rc(rt) = 0;
	}
	else
	{
		split(lc(rt), k - tree[rc(rt)].sumx - tree[rt].x);
		rt = lc(rt);
	}
	pushup(rt);
}
inline int merge(int x, int y)
{
	if (!x || !y)
		return x | y;
	int rt = ++cnt;
	if (rnd() & 1)
	{
		tree[rt] = tree[x];
		rc(rt) = merge(rc(rt), y);
	}
	else
	{
		tree[rt] = tree[y];
		lc(rt) = merge(x, lc(y));
	}
	pushup(rt);
	return rt;
}
inline ll query(int rt, ll k_th)
{
	ll res = 0;
	while (rt)
	{
		if (k_th < tree[lc(rt)].sumx)
			rt = lc(rt);
		else if (k_th <= tree[lc(rt)].sumx + tree[rt].x)
			return res + tree[lc(rt)].sumy + (k_th - tree[lc(rt)].sumx) * tree[rt].y;
		else
		{
			res += tree[lc(rt)].sumy + (ll)tree[rt].x * tree[rt].y;
			k_th -= tree[lc(rt)].sumx + tree[rt].x;
			rt = rc(rt);
		}
	}
	return res;
}
inline void print(int rt)
{
	if (!rt)
		return;
	print(lc(rt));
	printf("(%d,%d)\n",tree[rt].x, tree[rt].y);
	print(rc(rt));
}
#undef lc
#undef rc
struct
{
	int root;
	ll del;
	inline void update(ll val)
	{
		if (tree[root].sumx > val)
			split(root, val);
		else
		{
			val -= tree[root].sumx;
			del += val;
			root = 0;
		}
	}
	inline void add(int x, int y)
	{
		root = ::merge(root, newnode(x, y));
	}
	inline void merge(int x)
	{
		root = ::merge(root, x);
	}
	inline ll query(ll x, ll y)
	{
		ll res = ::query(root, y);
		if (x > 1)
			res -= ::query(root, x - 1);
		return res;
	}
	inline void print()
	{
		::print(root);
		putchar('\n');
	}
} seg[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void pushdown(int rt)
{
	if (seg[rt].del)
	{
		seg[lc].update(seg[rt].del);
		seg[rc].update(seg[rt].del);
		seg[rt].del = 0;
	}
	if (seg[rt].root)
	{
		seg[lc].merge(seg[rt].root);
		seg[rc].merge(seg[rt].root);
		seg[rt].root = 0;
	}
}
inline void update(int rt, int l, int r, int x, int y, int v1, int v2)
{
	if (r < x || l > y)
		return;
	if (x <= l && r <= y)
	{
		seg[rt].add(v1, v2);
		return;
	}
	int mid = (l + r) >> 1;
	pushdown(rt);
	update(lc, l, mid, x, y, v1, v2);
	update(rc, mid + 1, r, x, y, v1, v2);
}
inline void update(int rt, int l, int r, int x, int y, ll w)
{
	if (r < x || l > y)
		return;
	if (x <= l && r <= y)
	{
		seg[rt].update(w);
		return;
	}
	int mid = (l + r) >> 1;
	pushdown(rt);
	update(lc, l, mid, x, y, w);
	update(rc, mid + 1, r, x, y, w);
}
inline ll query(int rt, int l, int r, int pos, ll p, ll q)
{
	if (l == r)
		return seg[rt].query(p, q);
	int mid = (l + r) >> 1;
	pushdown(rt);
	if (pos <= mid)
		return query(lc, l, mid, pos, p, q);
	else
		return query(rc, mid + 1, r, pos, p, q);
}
signed main() 
{
    ios::sync_with_stdio(false);
    cin.tie(0), cout.tie(0);
    cin >> n >> m;
    for (int i = 1; i <= m; ++i)
    {
    	int opt;
    	cin >> opt;
    	if (opt == 1)
    	{
    		int l, r, x, y;
    		cin >> l >> r >> x >> y;
    		update(1, 1, n, l, r, x, y);
		}
		else if (opt == 2)
		{
			int l, r;
			ll w;
			cin >> l >> r >> w;
			update(1, 1, n, l, r, w);
		}
		else
		{
			int k;
			ll p, q;
			cin >> k >> p >> q;
			cout << query(1, 1, n, k, p, q) << '\n';
		}
	}
    return 0;
}