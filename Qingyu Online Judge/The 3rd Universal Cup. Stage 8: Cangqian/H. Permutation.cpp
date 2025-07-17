#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
typedef unsigned long long ull;
constexpr int N = 1e6 + 5;
constexpr int mod = 998244353;
constexpr auto divide = 0.61803398874989484820458683436564;
constexpr int inv2 = (mod + 1) / 2;
inline int query(int x, int y)
{
	cout << "? " << x << ' ' << y << endl;
	int z;
	cin >> z;
	return z;
}
inline int solve(int l, int r, int pos = 0)
{
	if (l == r)
		return l;
	if (!pos)
		pos = query(l, r);
	if (l + 1 == r)
		return l + r - pos;
	int len = max(2, (int)((r - l + 1) * divide));
	if (pos <= (l + r) / 2)
	{
		int npos = query(l, l + len - 1);
		if (npos == pos)
			return solve(l, l + len - 1, pos);
		else
			return solve(l + len, r);
	}
	else
	{
		int npos = query(r - len + 1, r);
		if (npos == pos)
			return solve(r - len + 1, r, pos);
		else
			return solve(l, r - len);
	}
}
inline void _main()
{
	int n;
	cin >> n;
	int res = solve(1, n);
	cout << "! " << res << endl;
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