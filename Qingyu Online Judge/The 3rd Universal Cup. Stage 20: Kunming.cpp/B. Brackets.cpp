#include <bits/stdc++.h>
using namespace std;
constexpr int N = 5e5 + 5;
constexpr int base = 31;
typedef unsigned long long ull;
int n, m;
struct node
{
	int l, r, p;
	ull hash;
	inline bool operator < (const node &rhs) const
	{
		return r < rhs.r;
	}
} a[N];
int st[N], p[N], top;
ull hsh[N], power[N];
int fa[N];
bool ill[N];
string s;
inline int find(int x)
{
	return !fa[x] ? x : fa[x] = find(fa[x]);
}
inline void clear()
{
	for (int i = 1; i <= n; ++i)
		fa[i] = ill[i] = 0;
	top = 0;
}
inline void solve(int type)
{
	auto calc = [type](char c)
	{
		int res = 0;
		if (c == '(')
			res = 1;
		else if (c == ')')
			res = -1;
		else if (c == '[')
			res = 2;
		else if (c == ']')
			res = -2;
		else if (c == '{')
			res = 3;
		else if (c == '}')
			res = -3;
		else if (c == '<')
			res = 4;
		else if (c == '>')
			res = -4;
		return type == 2 ? -res : res;
	};
	auto gethash = [](int l, int r)
	{
		return hsh[r] - hsh[l - 1] * power[r - l + 1];
	};
	auto makeill = [](int x, int y)
	{
		for (int i = find(x); i <= y; i = find(i))
		{
			ill[i] = true;
			fa[i] = i + 1;
		}
	};
	auto findpos = [](int x)
	{
		if (ill[x])
			return -1;
		return (int)(lower_bound(p + 1, p + 1 + top, x) - p);
	};
	sort(a + 1, a + 1 + m);
	for (int i = 1, j = 1; i <= n; ++i)
	{
		int c = calc(s[i]);
		if (c < 0)
		{
			if (!top || st[top] + c != 0)
			{
				top = 0;
				makeill(1, i);
			}
			else
			{
				makeill(p[top] + 1, i);
				--top;
			}
		}
		else
		{
			st[++top] = c;
			p[top] = i;
			hsh[top] = hsh[top - 1] * base + c;
		}
		while (j <= m && a[j].r == i)
		{
			int q = findpos(a[j].l);
			if (q == top + 1)
				a[j].p = 3;
			else if (q != -1)
			{
				a[j].p = type;
				a[j].hash = gethash(q, top);
			}
			++j;
		}
	}
	clear();
}
inline void _main()
{
	cin >> n >> m >> s;
	s = '\0' + s;
	for (int i = 1; i <= m; ++i)
	{
		cin >> a[i].l >> a[i].r;
		a[i].hash = a[i].p = 0;
	}
	solve(1);
	for (int i = 1; i <= m; ++i)
	{
		auto l = a[i].l, r = a[i].r;
		a[i].l = n - r + 1;
		a[i].r = n - l + 1;
	}
	reverse(s.begin() + 1, s.end());
	solve(2);
	vector<ull> L, R;
	int res = 0;
	for (int i = 1; i <= m; ++i)
	{
		if (a[i].p == 1)
			L.push_back(a[i].hash);
		else if (a[i].p == 2)
			R.push_back(a[i].hash);
		else if (a[i].p == 3)
			++res;
	}
	sort(L.begin(), L.end());
	sort(R.begin(), R.end());
	res /= 2;
	for (int i = 0, j = 0; i < (int)L.size(); ++i)
	{
		while (j < (int)R.size() && L[i] > R[j])
			++j;
		if (j < (int)R.size() && L[i] == R[j])
		{
			++res;
			++j;
		}
	}
	cout << res << '\n';
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	power[0] = 1;
	for (int i = 1; i <= N - 5; ++i)
		power[i] = power[i - 1] * base;
	int test = 1;
	cin >> test;
	for (int i = 1; i <= test; ++i)
	{
		_main();
	}
	return 0;
}