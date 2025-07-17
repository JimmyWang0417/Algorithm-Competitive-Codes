#include <bits/stdc++.h>
using namespace std;
constexpr int N = 105;
inline void work()
{
	string s;
	cin >> s;
	int res = 0;
	auto calc = [](char c)
	{
		return (c == '(' || c == ')') ? 1 : 0;
	};
	for (int i = 1; i < (int)s.length(); ++i)
		if (calc(s[i - 1]) == calc(s[i]))
			++res;
	cout << ((res < 3) ? "Yes" : "No") << '\n';
}
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	int T;
	cin >> T;
	while (T--)
		work();
	return 0;
}