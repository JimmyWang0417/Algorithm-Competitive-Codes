#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
constexpr int N = 3e5 + 5;
int n, q, a[N], b[N], c[N], fa[N];
inline int find(int x)
{
	return !fa[x] ? x : fa[x] = find(fa[x]);
}
int st[N], top;
inline void _main()
{
	cin >> n >> q;
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	st[0] = n + 1;
	for (int i = n; i >= 1; --i)
	{
		while (top && a[st[top]] <= a[i])
			--top;
		b[i] = st[top];
		st[++top] = i;
	}
	while (q--)
	{
		string s;
		int x, y;
		cin >> s >> x;
		if (s == "+")
		{
			cin >> y;
			while (y && (x = find(x)) != n + 1)
			{
				int d = min(y, a[x] - c[x]);
				c[x] += d;
				y -= d;
				if (a[x] == c[x])
					fa[x] = b[x];
			}
		}
		else
			cout << c[x] << '\n';
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