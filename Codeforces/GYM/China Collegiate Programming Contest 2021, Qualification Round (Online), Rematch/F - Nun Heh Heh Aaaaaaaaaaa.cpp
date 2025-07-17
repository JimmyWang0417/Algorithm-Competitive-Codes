#include<bits/stdc++.h>
using namespace std;
#define ll long long
#define N 100010
#define yu (998244353)
ll n;
inline ll ksm(ll x,ll y){
	ll an=1;
	for(;y;y>>=1){
		if(y&1)an=an*x%yu;
		x=x*x%yu;
	}return an;
}inline ll ni(ll x){return ksm(x,yu-2);}
char a[10]={' ','n','u','n','h','e','h','h','e','h'};//nunhehheh
ll f[N][10];
ll g[N];
string s;
inline void add(ll &x,ll y){x+=y;if(x>=yu)x-=yu;return ;}
int main()
{
//	freopen("test1.in","r",stdin);
	//freopen(".in","r",stdin);
	//freopen("test1.out","w",stdout);
	ios::sync_with_stdio(false);cin.tie(0);cout.tie(0);
	ll ti;cin>>ti;while(ti--){
		cin>>s;n=s.length();
		f[0][0]=1;
		for(int i=1;i<=n;i++){
			char nww=s[i-1];
			memcpy(f[i],f[i-1],sizeof(f[i]));
			for(int j=0;j<=8;j++){
				if(nww==a[j+1])add(f[i][j+1],f[i-1][j]);
			}
		}ll ans=0;
		for(int i=1;i<=n;i++)g[i]=(s[i-1]=='a');
		for(int i=n-1;i>=1;i--)g[i]+=g[i+1];
		for(int i=1;i<=n;i++){
			ll ji=f[i][9]-f[i-1][9]+yu;
			add(ans,ji*(ksm(2,g[i+1])-1)%yu);
		}for(int i=1;i<=n;i++)g[i]=0;
		cout<<ans<<'\n';
	} 
	return 0;
}
