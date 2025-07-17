#include<bits/stdc++.h>
using namespace std;

//#define ONLINE
#ifndef ONLINE
char DEBUG_BUFFER[1000];
#define debug(...) {sprintf(DEBUG_BUFFER,##__VA_ARGS__);\
cerr<<"\033[1;36m"<<DEBUG_BUFFER<<"\033[0;2m"<<"\033[0m";}
#else
#define debug(...) ;
#endif

using LL=long long;
using PII=pair<int,int>;

#define all(x) (x).begin(),(x).end()
#define allr(x) (x).rbegin(),(x).rend()

#define FAST_IO {ios::sync_with_stdio(false);cin.tie(nullptr);}
inline int read(){static int x; cin>>x; return x;}
inline LL readLL(){static LL x; cin>>x; return x;}
mt19937_64 rng(chrono::system_clock::now().time_since_epoch().count());

void solve_1(){
	string s; cin>>s;
	int n=s.size(),sum=0;
	int d=n,info=0;
	for(int i=0;i<n;i++){
		sum+=(s[i]-'0');
		if(sum%2000<=1){
			d=n-i-1;
			info=(sum/2000)*2+(sum%2000);
		}
	}
	assert(d<2000);
	assert(info<2000);
	cout<<d<<' '<<info<<"\n";
}

void solve_2(){
	int info; string s;
	cin>>info>>s;
	int sum=(info/2)*2000;
	if(info&1) sum++;
	for(auto c:s) sum+=(c-'0');
	cout<<sum<<"\n";
}

int main(){
	FAST_IO;
	if(read()==1){
		for(int T=read();T--;){
			solve_1();
		}
	}
	else{
		for(int T=read();T--;){
			solve_2();
		}
	}
	return 0;
}

/* stuff you should look for
* int overflow, array bounds
* special cases (n=1?)
* do smth instead of nothing and stay organized
* WRITE STUFF DOWN
* DON'T GET STUCK ON ONE APPROACH
*/