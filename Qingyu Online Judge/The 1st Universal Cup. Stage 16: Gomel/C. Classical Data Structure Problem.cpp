#include <bits/stdc++.h>
using namespace std;
constexpr int N = 5e5 + 5;
constexpr int mod = (1 << 30);
typedef long long ll;
int n, m;
struct Tree
{
	int l, r;
	int pos;
	int c1, c2;
	ll sum1, sum2;
	unsigned key;
} tree[N * 2];
#define lc(rt) tree[rt].l
#define rc(rt) tree[rt].r
int root, cnt;
mt19937 rnd(114514);
inline void print(int rt)
{
	if (!rt)
		return;
	print(lc(rt));
	printf("%d %d %d\n", tree[rt].pos, tree[rt].c1, tree[rt].c2);
	print(rc(rt));
}
inline int newnode(int pos, int val)
{
	int rt = ++cnt;
	tree[rt].pos = pos;
	tree[rt].c1 = val;
	tree[rt].c2 = (ll)pos * val % mod;
	tree[rt].sum1 = tree[rt].c1;
	tree[rt].sum2 = tree[rt].c2;
	tree[rt].key = rnd();
	return rt;
}
inline void pushup(int rt)
{
	tree[rt].sum1 = ((tree[lc(rt)].sum1 + tree[rc(rt)].sum1) % mod + tree[rt].c1) % mod;
	tree[rt].sum2 = ((tree[lc(rt)].sum2 + tree[rc(rt)].sum2) % mod + tree[rt].c2) % mod;
}
inline int merge(int x, int y)
{
	if (!x || !y)
		return x | y;
	if (tree[x].key > tree[y].key)
	{
		rc(x) = merge(rc(x), y);
		pushup(x);
		return x;
	}
	else
	{
		lc(y) = merge(x, lc(y));
		pushup(y);
		return y;
	}
}
inline void split(int rt, int val, int &x, int &y)
{
	if (!rt)
		x = y = 0;
	else
	{
		if (tree[rt].pos <= val)
		{
			x = rt;
			split(rc(rt), val, rc(x), y);
			pushup(x);
		}
		else
		{
			y = rt;
			split(lc(rt), val, x, lc(y));
			pushup(y);
		}
	}
}
inline void update(int pos, int val)
{
	if (pos == (1 << m))
		return;
	int x, y;
	split(root, pos, x, y);
	root = merge(merge(x, newnode(pos, val)), y);
}
inline int query(int pos)
{
	int x, y;
	split(root, pos, x, y);
	int ans = ((ll)tree[x].sum1 * (pos + 1) - tree[x].sum2 + mod) % mod;
	root = merge(x, y);
	return ans;
}
inline void update(int l, int r, int v)
{
	update(l, v);
	update(r + 1, mod - v);
}
inline int query(int l, int r)
{
	int res = query(r);
	if (l > 0)
		res = (res - query(l - 1) + mod) % mod;
	return res;
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n >> m;
	int x = 0;
	for (int i = 1; i <= n; ++i)
	{
		int p, q;
		cin >> p >> q;
		p = (p + x) % (1 << m);
		q = (q + x) % (1 << m);
		if (p > q)
			swap(p, q);
		update(p, q, i);
		(x += query(p, q)) %= mod;
	}
	cout << x << '\n';
	return 0;
}