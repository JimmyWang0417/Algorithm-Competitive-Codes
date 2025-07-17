#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 2e5 + 5;
constexpr __int128 limit = 1e18;
int n, m;
struct node
{
	ll tag, sum;
	inline void update(ll val)
	{
		tag = (ll)(min((__int128)tag * val, limit));
		sum = (ll)(min((__int128)sum * val, limit));
	}
} tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void pushup(int rt)
{
	tree[rt].sum = min(tree[lc].sum + tree[rc].sum, (ll)1e18);
}
inline void pushdown(int rt)
{
	if (tree[rt].tag != 1)
	{
		tree[lc].update(tree[rt].tag);
		tree[rc].update(tree[rt].tag);
		tree[rt].tag = 1;
	}
}
inline void build(int rt, int l, int r)
{
	tree[rt].tag = 1;
	if (l == r)
	{
		tree[rt].sum = 1;
		return;
	}
	int mid = (l + r) >> 1;
	build(lc, l, mid);
	build(rc, mid + 1, r);
	pushup(rt);
}
inline tuple<int, ll, ll> query(int rt, int l, int r, ll pos)
{
	if (l == r)
		return make_tuple(l, pos, tree[rt].sum);
	int mid = (l + r) >> 1;
	pushdown(rt);
	if (pos <= tree[lc].sum)
		return query(lc, l, mid, pos);
	else
		return query(rc, mid + 1, r, pos - tree[lc].sum);
}
inline void update(int rt, int l, int r, int x, int y)
{
	if (r < x || l > y)
		return;
	if (x <= l && r <= y)
		return tree[rt].update(2);
	int mid = (l + r) >> 1;
	pushdown(rt);
	update(lc, l, mid, x, y);
	update(rc, mid + 1, r, x, y);
	pushup(rt);
}
inline void update(int rt, int l, int r, int pos, ll val)
{
	if (l == r)
	{
		tree[rt].sum = min(tree[rt].sum + val, (ll)1e18);
		return;
	}
	int mid = (l + r) >> 1;
	pushdown(rt);
	if (pos <= mid)
		update(lc, l, mid, pos, val);
	else
		update(rc, mid + 1, r, pos, val);
	pushup(rt);
}
inline void print(int rt, int l, int r)
{
	if (l == r)
	{
		cout << tree[rt].sum << ' ';
		return;
	}
	int mid = (l + r) >> 1;
	pushdown(rt);
	print(lc, l, mid);
	print(rc, mid + 1, r);
}
char str[N];
inline void _main()
{
	cin >> n >> m;
	cin >> str;
	build(1, 1, n);
	for (int i = 1; i <= m; ++i)
	{
		int opt;
		ll l, r;
		cin >> opt >> l;
		if (opt == 1)
		{
			cin >> r;
			auto [x, x1, x2] = query(1, 1, n, l);
			auto [y, y1, y2] = query(1, 1, n, r);
			if (x == y)
				update(1, 1, n, x, y1 - x1 + 1);
			else
			{
				update(1, 1, n, x, x2 - x1 + 1);
				update(1, 1, n, x + 1, y - 1);
				update(1, 1, n, y, y1);
			}
		}
		else
			cout << str[get<0>(query(1, 1, n, l)) - 1] << '\n';
//		print(1, 1, n);
//		cout << '\n';
	}
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int test = 1;
//	cin >> test;
	while (test--)
		_main();
	return 0;
}