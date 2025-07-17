#include <bits/stdc++.h>
using namespace std;
constexpr int N = 5e5 + 5;
int n, m, a[N];
int c[N];
#define lowbit(x) ((x) & (-x))
inline int query(int pos)
{
	int res = 0;
	for (int i = pos; i <= n; i += lowbit(i))
		res += c[i];
	return res;
}
inline void update(int pos, int val)
{
	for (int i = pos; i; i -= lowbit(i))
		c[i] += val;
}
inline void _main()
{
	cin >> n;
	int res = 0;
	for (int i = 1; i <= n; ++i)
	{
		int x;
		cin >> x;
		res ^= query(x) & 1;
		update(x, 1);
	}
	for (int i = 1; i <= n; ++i)
		c[i] = 0;
	for (int i = 1; i <= n; ++i)
	{
		int x;
		cin >> x;
		res ^= query(x) & 1;
		update(x, 1);
	}
	for (int i = 1; i <= n; ++i)
		c[i] = 0;
	cout << (res ? "A" : "B");
	for (int i = 1; i < n; ++i)
	{
		char t;
		int l, r, d;
		cin >> t >> l >> r >> d;
		res ^= ((long long)(r - l + 1 - d) * d) & 1;
		cout << (res ? "A" : "B");
	}
	cout << '\n';
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int test = 1;
	cin >> test;
	while (test--)
		_main();
	return 0;
}