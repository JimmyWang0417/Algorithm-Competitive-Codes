#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
constexpr int N = 1e6 + 5;
constexpr int mod = 998244353;
constexpr int inv2 = (mod + 1) / 2;
int n, q;
struct Tree
{
	int val, dis;
} tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void pushup(int rt)
{
	tree[rt].dis = min(tree[rt].val, tree[lc].dis + tree[rc].dis);
}
inline void build()
{
	for (int i = (1 << (n + 1)) - 1; i >= (1 << n); --i)
		tree[i].dis = tree[i].val;
	for (int i = (1 << n) - 1; i >= 1; --i)
		pushup(i);
}
inline void update(int x, int y)
{
	tree[x].val = y;
	if (x >= (1 << n))
	{
		tree[x].dis = tree[x].val;
		x >>= 1;
	}
	while (x)
	{
		pushup(x);
		x /= 2;
	}
}
int lx[23], rx[23], ly[23], ry[23]; 
inline int query(int x, int y)
{
	x = x | (1 << n);
	y = (y - 1) | (1 << n);
	lx[n] = 0, rx[n] = tree[x].dis;
	ly[n] = tree[y].dis, ry[n] = 0;
	int ans = INT_MAX;
	for (int i = n; i >= 1; --i, x >>= 1, y >>= 1)
	{
		if (x & 1)
		{
			lx[i - 1] = min(lx[i] + tree[x ^ 1].dis, rx[i] + tree[x / 2].dis);
			rx[i - 1] = min(rx[i], lx[i] + tree[x ^ 1].dis + tree[x / 2].dis);
		}
		else
		{
			lx[i - 1] = min(lx[i], rx[i] + tree[x ^ 1].dis + tree[x / 2].dis);
			rx[i - 1] = min(rx[i] + tree[x ^ 1].dis, lx[i] + tree[x / 2].dis);
		}
		if (y & 1)
		{
			ly[i - 1] = min(ly[i] + tree[y ^ 1].dis, ry[i] + tree[y / 2].dis);
			ry[i - 1] = min(ry[i], ly[i] + tree[y ^ 1].dis + tree[y / 2].dis);
		}
		else
		{
			ly[i - 1] = min(ly[i], ry[i] + tree[y ^ 1].dis + tree[y / 2].dis);
			ry[i - 1] = min(ry[i] + tree[y ^ 1].dis, ly[i] + tree[y / 2].dis);
		}
		if ((x ^ y) == 1)
			ans = min(ans, rx[i] + ly[i]);
		else if (x == y)
			ans = min(ans, min(lx[i] + ly[i], rx[i] + ry[i]));
	}
	ans = min(ans, min(lx[0] + ly[0], rx[0] + ry[0]));
	return ans;
}
inline void _main()
{
	cin >> n;
	for (int i = 1; i < (1 << (n + 1)); ++i)
		cin >> tree[i].val;
	build();
	cin >> q;
	for (int i = 1; i <= q; ++i)
	{
		int opt, x, y;
		cin >> opt >> x >> y;
		if (opt == 1)
			update(x, y);
		else
			cout << query(x, y) << '\n';
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