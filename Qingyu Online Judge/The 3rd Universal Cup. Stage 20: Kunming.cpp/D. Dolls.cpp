#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1e5 + 5;
int n, a[N];
pair<int, int> st[N];
int top;
inline bool check(int l, int r)
{
	if (r > n)
		return false;
	vector<int> p, b;
	for (int i = l; i <= r; ++i)
		p.push_back(a[i]);
	sort(p.begin(), p.end());
	p.erase(unique(p.begin(), p.end()), p.end());
	for (int i = l; i <= r; ++i)
		b.push_back((int)(lower_bound(p.begin(), p.end(), a[i]) - p.begin()));
	top = 0;
	for (auto x : b)
	{
		st[++top] = make_pair(x, x);
		while (top > 1 && (st[top].first == st[top - 1].second + 1 || st[top].second + 1 == st[top - 1].first))
		{
			st[top - 1].first = min(st[top].first, st[top - 1].first);
			st[top - 1].second = max(st[top].second, st[top - 1].second);
			--top;
		}
	}
	return top == 1;
}
inline void _main()
{
	cin >> n;
	for (int i = 1; i <= n; ++i)
		cin >> a[i];
	int res = 0;
	for (int l = 1, r = 0; l <= n; l = r + 1)
	{
		int maxlen = 2;
		while (check(l, l + maxlen))
			maxlen <<= 1;
		r = l;
		for (int i = maxlen / 2; i >= 1; i >>= 1)
			if (check(l, r + i))
				r += i;
		++res;
	}
	cout << n - res << '\n';
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