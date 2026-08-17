#include <bits/stdc++.h>
using namespace std;

using LL=long long;
#define all(x) (x).begin(),(x).end()

#define N 200010
int n,a[N];

constexpr int P=30;
constexpr int M=1<<P;
bitset<M>mp;

bool dfs(int u,int x,int rest){
	if(n-u+1<rest) return 0;
	if(!rest){
		if(mp[x]) return 1;
		mp[x]=1;
		return 0;
	}
	if(dfs(u+1,x^a[u],rest-1)) return 1;
	if(dfs(u+1,x,rest)) return 1;
	return 0;
}

signed main()
{
	ios::sync_with_stdio(false);
	cin.tie(0), cout.tie(0);
	
	set<int>buc;
	bool flag=0;
	
	cin>>n;
	for(int i=1;i<=n;++i){
		cin>>a[i];
//		a[i]=a[i]*2+1;
		if(buc.find(a[i])!=buc.end()){
			flag=1;
		}
		else{
			buc.insert(a[i]);
		}
	}
	if(flag){
		cout<<"Yes\n2";
		return 0;
	}
	for(int len=2;len<=P/2;++len){
//		printf("len=%d\n",len);
		mp.reset();
		if(dfs(1,0,len)){
			cout<<"Yes\n"<<len*2;
			return 0;
		}
	}
	cout<<"No";
	return 0;
}
