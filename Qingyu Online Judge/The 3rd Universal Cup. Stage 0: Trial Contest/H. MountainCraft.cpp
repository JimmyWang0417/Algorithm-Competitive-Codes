#include <bits/stdc++.h>
using namespace std;
constexpr int N = 4e5 + 5;
constexpr auto sqrt2 = sqrt(2);
typedef long long ll;
int n, m;
pair<int, int> a[N];
int p[N], tot;
struct Tree
{
	int size;
	int sum;
	int tag;
} tree[N * 4];
#define lc (rt << 1)
#define rc (rt << 1 | 1)
inline void pushup(int rt)
{
	if (tree[rt].tag)
		tree[rt].sum = tree[rt].size;
	else
		tree[rt].sum = tree[lc].sum + tree[rc].sum;
}
inline void build(int rt, int l, int r)
{
	tree[rt].size = p[r + 1] - p[l];
	if (l == r)
		return;
	int mid = (l + r) >> 1;
	build(lc, l, mid);
	build(rc, mid + 1, r);
}
inline void update(int rt, int l, int r, int x, int y, int val)
{
	if (r < x || l > y)
		return;
	if (x <= l && r <= y)
	{
		tree[rt].tag += val;
		pushup(rt);
		return;
	}
	int mid = (l + r) >> 1;
	update(lc, l, mid, x, y, val);
	update(rc, mid + 1, r, x, y, val);
	pushup(rt);
}
inline void _main()
{
	cin >> n >> m;
	for (int i = 1; i <= n; ++i)
	{
		int x, y;
		cin >> x >> y;
		a[i] = make_pair(x, y);
		p[++tot] = max(x - y, 0), p[++tot] = min(x + y, m);
	}
	sort(p + 1, p + 1 + tot);
	tot = (int)(unique(p + 1, p + 1 + tot) - p - 1);
	build(1, 1, tot - 1);
	set<pair<int, int>> se;
	for (int i = 1; i <= n; ++i)
	{
		auto [x, y] = a[i];
		if (se.find(make_pair(x, y)) != se.end())
		{
			se.erase(make_pair(x, y));
			int l = max(x - y, 0), r = min(x + y, m);
//			printf(" %d %d %d %d\n", l, r, (int)(lower_bound(p + 1, p + 1 + tot, l) - p), (int)(lower_bound(p + 1, p + 1 + tot, r) - p - 1));
			update(1, 1, tot - 1, 
				(int)(lower_bound(p + 1, p + 1 + tot, l) - p), 
				(int)(lower_bound(p + 1, p + 1 + tot, r) - p - 1), 
				-1);
		}
		else
		{
			se.emplace(x, y);
			int l = max(x - y, 0), r = min(x + y, m);
//			printf("%d %d\n", l, r);
			update(1, 1, tot - 1, 
				(int)(lower_bound(p + 1, p + 1 + tot, l) - p), 
				(int)(lower_bound(p + 1, p + 1 + tot, r) - p - 1), 
				1);
		}
		printf("%.8lf\n", sqrt2 * tree[1].sum);
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