#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
using namespace std;
typedef long long ll;
constexpr int N = 2e5 + 5;
int n, m, a[N];
int S, T;
int p[N * 10], tot;
struct Edge
{
	int next, to, flow, cap, cost;
} edge[N * 10];
int head[N], num_edge = 1;
inline void add_edge(int from, int to, int cap, int cost, bool flag = true)
{
	edge[++num_edge].next = head[from];
	edge[num_edge].to = to;
	edge[num_edge].cap = cap;
	edge[num_edge].cost = cost;
	head[from] = num_edge;
	if (flag)
		add_edge(to, from, 0, -cost, false);
}
int dis[N], cur[N];
bool exist[N];
inline bool spfa()
{
	for(int i=S; i<=T; ++i)
	{
		cur[i]=head[i];
		dis[i] = ~0x3f3f3f3f;
		exist[i] = 0;
	}
	std::queue<int>q;
	q.push(S);
	dis[S]=0;
	exist[S]=true;
	while(!q.empty())
	{
		int u=q.front();
		q.pop();
		exist[u]=false;
		for(int i=head[u]; i; i=edge[i].next)
		{
			int &v=edge[i].to;
			if(edge[i].cap>edge[i].flow&&dis[v]<dis[u]+edge[i].cost)
			{
				dis[v]=dis[u]+edge[i].cost;
				if(!exist[v])
				{
					q.push(v);
					exist[v]=true;
				}
			}
		}
	}
	return dis[T]>=~0x3f3f3f3f / 2;
}
using std::pair;
using std::make_pair;
ll ans=0;
inline int dinic(int u,int flow)
{
	if(u==T)
		return flow;
	exist[u]=true;
	int res=0;
	for(int &i=cur[u]; i; i=edge[i].next)
	{
		int &v=edge[i].to;
		if(!exist[v]&&dis[v]==dis[u]+edge[i].cost&&edge[i].cap>edge[i].flow)
		{
			int f=dinic(v,std::min(flow,edge[i].cap-edge[i].flow));
			if(f)
			{
				res+=f;
				edge[i].flow+=f;
				edge[i^1].flow-=f;
				flow-=f;
				if(!flow)
				{
					exist[u]=false;
					break;
				}
			}
		}
	}
	return res;
}
inline int maxcost_maxflow()
{
	int res = 0;
	while (spfa())
	{
		int f = dinic(S, INT_MAX);
		res += f * dis[T];
	}
	return res;
}
int cnt[N];
signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	cin >> n;
	for (int i = 1; i <= n; ++i)
	{
		cin >> a[i];
		for (int j = 1; j * j <= a[i]; ++j)
			if (a[i] % j == 0)
			{
				p[++tot] = j;
				if (j * j != a[i])
					p[++tot] = a[i] / j;
			}
	}
	sort(p + 1, p + 1 + tot);
	tot = (int)(unique(p + 1, p + 1 + tot) - p - 1);
	for (int i = 1; i <= tot; ++i)
	{
		int x = p[i];
		for (int j = 2; j * j <= x; ++j)
			while (x % j == 0)
			{
				++cnt[i];
				x /= j;
			}
		if (x > 1)
			++cnt[i];
	}
	S = 0, T = tot + 1;
	for (int i = 1; i <= tot; ++i)
		add_edge(i, T, 1, -cnt[i]);
	for (int i = 1; i <= n; ++i)
	{
		int u = (int)(lower_bound(p + 1, p + 1 + tot, a[i]) - p);
		add_edge(S, u, 1, cnt[u]);
		for (int j = 1; j * j <= a[i]; ++j)
		{
			if (a[i] % j)
				continue;
			int v1 = (int)(lower_bound(p + 1, p + 1 + tot, j) - p);
			int v2 = (int)(lower_bound(p + 1, p + 1 + tot, a[i] / j) - p);
			add_edge(u, v1, INT_MAX, 0);
			if (j * j != a[i])
				add_edge(u, v2, INT_MAX, 0);
		}
	}
	cout << maxcost_maxflow() << '\n';
	return 0;
} 