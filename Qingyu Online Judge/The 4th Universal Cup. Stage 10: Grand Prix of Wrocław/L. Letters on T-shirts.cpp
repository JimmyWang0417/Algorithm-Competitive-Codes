#include<bits/stdc++.h>
using namespace std;

#ifdef LOCAL
#include<local/dbg.h>
#else
#define dbg(...) 42
#endif

using LL=long long;
#define ai(x) using ai##x=array<int,x>;
ai(2);ai(3);ai(4);ai(5);ai(6);ai(7);ai(8);ai(9);ai(10);ai(26);
#undef ai

#define all(x) (x).begin(),(x).end()
#define allr(x) (x).rbegin(),(x).rend()
template<class T>inline bool updmx(T& x,const T& y){return x<y?x=y,1:0;}
template<class T>inline bool updmn(T& x,const T& y){return y<x?x=y,1:0;}
template<class T>inline void clr(T& x){T().swap(x);}

mt19937_64 rng(chrono::system_clock::now().time_since_epoch().count());
LL rand(LL l,LL r){return rng()%(r-l+1)+l;}

int main(){
#ifndef LOCAL
	cin.tie(nullptr)->sync_with_stdio(false);
#endif
	string s[3];
	cin>>s[0]>>s[1]>>s[2];
	vector<int>p{0,1,2};
	do{
		string t="";
		for(int i=0;i<3;++i){
			t+=s[p[i]];
			if(t=="cerc"){
				cout<<"YES\n";
				cout<<(i+1)<<'\n';
				for(int j=0;j<=i;++j){
					cout<<(p[j]+1)<<' ';
				}
				exit(0);
			}
		}
	}while(next_permutation(all(p)));
	cout<<"NO\n";
	return 0;
}
