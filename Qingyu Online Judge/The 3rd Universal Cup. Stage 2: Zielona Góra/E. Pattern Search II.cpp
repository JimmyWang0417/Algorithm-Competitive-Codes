#include <bits/stdc++.h>
using namespace std;
constexpr int N = 1.5e5 + 5;
int n;
char str[N];
struct node
{
	int size, ans;
	int pref[N], preg[N];
	int suff[N], sufg[N];
	inline node friend operator+(const node &lhs, const node &rhs)
	{
		node res;
		res.size = lhs.size + rhs.size;
		res.ans = min(lhs.ans, rhs.ans);
		for (int i = 1; i <= n; ++i)
		{
			if (lhs.pref[i] == n + 1)
			{
				res.pref[i] = lhs.pref[i];
				res.preg[i] = lhs.preg[i];
			}
			else
			{
				res.pref[i] = rhs.pref[lhs.pref[i]];
				res.preg[i] = lhs.size + rhs.preg[lhs.pref[i]];
			}
			
			if (rhs.suff[i] == 0)
			{
				res.suff[i] = rhs.suff[i];
				res.sufg[i] = rhs.sufg[i];
			}
			else
			{
				res.suff[i] = lhs.suff[rhs.suff[i]];
				res.sufg[i] = lhs.sufg[rhs.suff[i]] + rhs.size;
			}
			if (lhs.suff[i] == 0 && rhs.pref[i + 1] == n + 1)
				res.ans = min(res.ans, lhs.sufg[i] + rhs.preg[i + 1]);
		}
		return res;
	}
} A, B;
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> str;
	n = (int)strlen(str);
	if (n == 1)
	{
		cout << "1\n";
		return 0;
	}
	A.size = B.size = 1;
	for (int i = 1; i <= n; ++i)
	{
		if (str[i - 1] == 'a')
		{
			A.pref[i] = A.suff[i] = i;
			B.pref[i] = i + 1, B.suff[i] = i - 1;
			B.preg[i] = B.sufg[i] = 1;
		}
		else
		{
			B.pref[i] = B.suff[i] = i;
			A.pref[i] = i + 1, A.suff[i] = i - 1;
			A.preg[i] = A.sufg[i] = 1;
		}
	}
	A.ans = B.ans = INT_MAX;
	for (int i = 1; i <= 30; ++i)
	{
		swap(A, B);
		B = A + B;
	}
	cout << B.ans << '\n';
	return 0;
}