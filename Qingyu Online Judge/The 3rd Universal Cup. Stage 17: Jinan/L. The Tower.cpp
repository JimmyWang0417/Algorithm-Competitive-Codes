#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 5e5 + 5;
int n;
mt19937 rnd(114514);
struct Tree
{
	int ch[2], fa;
	ll l, r;
	ll size;
	int key;
} tree[N];
int root[N], cnt, belong[N];
#define lc(rt) tree[rt].ch[0]
#define rc(rt) tree[rt].ch[1]
#define fa(rt) tree[rt].fa
inline int newnode(ll l, ll r)
{
	int rt = ++cnt;
	tree[rt].l = l;
	tree[rt].r = r;
	tree[rt].key = rnd();
	tree[rt].size = r - l + 1;
	lc(rt) = rc(rt) = fa(rt) = 0;
	return rt;
}
inline void pushup(int rt)
{
	tree[rt].size = tree[lc(rt)].size + tree[rc(rt)].size + (tree[rt].r - tree[rt].l + 1);
	if (lc(rt))
		fa(lc(rt)) = rt;
	if (rc(rt))
		fa(rc(rt)) = rt;
}
set<tuple<ll, ll, int>> se;
inline void splitval(int rt, ll val, int &x, int &y)
{
	if (!rt)
		x = y = 0;
	else
	{
		if (tree[rt].l <= val)
		{
			x = rt;
			splitval(rc(rt), val, rc(x), y);
			pushup(x);
		}
		else
		{
			y = rt;
			splitval(lc(rt), val, x, lc(y));
			pushup(y);
		}
	}
}
int qwq;
inline void split(int rt, ll size, int &x, int &y)
{
	if (!size)
	{
		x = 0;
		y = rt;
	}
	else if (!rt)
		x = y = 0;
	else
	{
		if (tree[lc(rt)].size < size)
		{
			x = rt;
			if (size < tree[lc(rt)].size + (tree[rt].r - tree[rt].l + 1))
			{
				size -= tree[lc(rt)].size;
				se.erase(make_tuple(tree[rt].l, tree[rt].r, rt));
				
				qwq = newnode(tree[rt].l + size, tree[rt].r), rc(qwq) = rc(rt);
				tree[x].l = tree[rt].l, tree[x].r = tree[rt].l + size - 1, rc(x) = 0;
				y = 0;
				
				se.emplace(tree[x].l, tree[x].r, x);
				se.emplace(tree[qwq].l, tree[qwq].r, qwq);
				pushup(x), pushup(qwq);
			}
			else
			{
				split(rc(rt), size - tree[lc(rt)].size - (tree[rt].r - tree[rt].l + 1), rc(x), y);
				pushup(x);
			}
		}
		else
		{
			y = rt;
			split(lc(rt), size, x, lc(y));
			pushup(y);
		}
	}
}
inline int merge(int x, int y)
{
	if (!x || !y)
		return x | y;
	if (tree[x].key < tree[y].key)
		swap(x, y);
	int l, r;
	splitval(y, tree[x].l, l, r);
	lc(x) = merge(lc(x), l);
	rc(x) = merge(rc(x), r);
	pushup(x);
	return x;
}
inline void print(int rt)
{
	if (!rt)
		return;
	print(lc(rt));
	printf(" %d %d %d %d\n", rt, fa(rt), lc(rt), rc(rt));
	print(rc(rt));
}
inline void updateroot(int x)
{
	fa(root[x]) = 0;
	belong[root[x]] = x;
}
signed main()
{
//	freopen("project.in", "r", stdin);
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	root[0] = newnode(1, 1e15);
	se.emplace(1, 1e15, root[0]);
	int m = 0;
	for (int i = 1; i <= n; ++i)
	{
		int opt, x;
		cin >> opt >> x;
		if (opt == 1)
		{
			split(root[0], x, root[++m], root[0]);
			root[0] = merge(qwq, root[0]);
			qwq = 0;
			updateroot(0);
			updateroot(m);
		}
		else if (opt == 2)
		{
			root[0] = merge(root[0], root[x]);
			updateroot(0);
			root[x] = 0;
		}
		else
		{
			auto it = se.upper_bound(make_tuple(x, 1e18, 0));
			--it;
			int rt = get<2>(*it);
			while (fa(rt))
				rt = fa(rt);
			cout << belong[rt] << '\n';
		}
	}
	return 0;
}