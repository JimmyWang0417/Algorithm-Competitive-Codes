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

constexpr int M=7;
constexpr int error=1;

vector<int>OK_MASK,oops2;
int dps[1<<M],dpt[1<<M];
void init_check(const int _mask,const string& str){
	bool ok=0;
	for(const int mask:OK_MASK){
		if(ok) break;
		string s="",t="";
		vector<int>poss,post;
		poss.reserve(M); post.reserve(M);
		for(int i=0;i<M;++i){
			if(mask>>i&1){
				s+=str[i];
				poss.emplace_back(i);
			}
			else{
				t+=str[i];
				post.emplace_back(i);
			}
		}
		if(poss.size()<post.size()){
			swap(poss,post);
			swap(s,t);
		}
		const int nerror=poss.size()-post.size();
		if(nerror>error) continue;
		if(nerror==1){
			for(int p1=0;p1<(int)poss.size() && (!ok);++p1){
				string ns=p1?s.substr(0,p1):"";
				if(p1!=(int)poss.size()-1){
					ns+=s.substr(p1+1);
				}
				if(ns==t){
					ok=1;
					int ms=0,mt=0;
					for(int j=0;j<(int)poss.size();++j){
						if(j!=p1) ms|=(1<<poss[j]);
					}
					for(auto p:post) mt|=(1<<p);
					dps[_mask]=ms;
					dpt[_mask]=mt;
					// dbg(_mask,str);
					// dbg("\t",p1,poss,post);
					break;
				}
			}
		}
		else{
			assert(-1); // not implemented yet
		}
	}
	if(!ok){
		dbg(str);
		oops2.emplace_back(_mask);
	}
	// assert(ok);
}

int dpmask[1<<(M-1)];
vector<int>oops;
void init_check_M_1(const int _mask,const string& str){
	bool ok=0;
	for(int mask=0;mask<(1<<(M-1));++mask){
		if(ok) break;
		string s="",t="";
		for(int i=0;i<(M-1);++i){
			if(mask>>i&1) s+=str[i];
			else t+=str[i];
		}
		if(s==t){
			ok=1;
			dpmask[_mask]=mask;
			break;
		}
	}
	if(!ok){
		dbg(_mask,str);
		oops.emplace_back(_mask);
	}
}

using D=double;
template<int N>
D calc(const D p,const D q){
	array<D,N>dp;
	for(int i=0;i<N;++i) dp[i]=D(i);
	for(int i=M-1;i<N;++i){
		dp[i]=dp[i-(M-1)]+p*((D(1)-q)*1+q*3);
	}
	return dp[N-1];
}

void init(){
	assert(M&1);
	// len=M-1
	for(int mask=0;mask<(1<<(M-1));++mask){
		string s="";
		for(int i=0;i<(M-1);++i){
			if(mask>>i&1) s+="1";
			else s+="0";
		}
		init_check_M_1(mask,s);
	}
	// len=M
	for(int mask=0;mask<(1<<M);++mask){
		int s=0;
		for(int i=0;i<M;++i){
			if(mask>>i&1) ++s;
			else --s;
		}
		if(-error<=s && s<=error) OK_MASK.emplace_back(mask);
	}
	dbg(OK_MASK.size());
	for(int mask=0;mask<(1<<M);++mask){
		string s="";
		for(int i=0;i<M;++i){
			if(mask>>i&1) s+="1";
			else s+="0";
		}
		init_check(mask,s);
	}
	#ifdef LOCAL
	dbg(oops.size(),(1<<(M-1)));
	dbg(oops2.size(),(1<<M));
	const D fail_M_1=D(oops.size())/(1<<(M-1));
	const D fail_M=D(oops2.size())/(1<<M);
	constexpr int N=int(1e5)+1;
	D exp_fail_count=calc<N>(fail_M_1,fail_M);
	dbg(exp_fail_count,exp_fail_count/(N-1));
	#endif
}

unordered_map<string,ai4>fuck={
	{"0111000",ai4{0,4,5,6}},
	{"1000010",ai4{1,2,3,4}},
	{"1000110",ai4{1,2,3,6}},
	{"0001110",ai4{0,1,2,6}},
	{"1001110",ai4{0,3,4,5}},
	{"1011110",ai4{0,2,3,4}},
	{"0111110",ai4{1,2,3,4}},
	{"1000001",ai4{1,2,3,4}},
	{"0100001",ai4{0,2,3,4}},
	{"0110001",ai4{0,3,4,5}},
	{"1110001",ai4{0,1,2,6}},
	{"0111001",ai4{1,2,3,6}},
	{"0111101",ai4{1,2,3,6}},
	{"1000111",ai4{0,4,5,6}}
};

void check_fuck(){
	for(auto& [s,a]:fuck){
		if(s[a[0]]!=s[a[2]]) dbg(s);
		if(s[a[1]]!=s[a[3]]) dbg(s);
	}
}

int main(){
#ifndef LOCAL
	cin.tie(nullptr)->sync_with_stdio(false);
#endif
	init();
	check_fuck();
	{
		int shit; cin>>shit;
	}
	string s,t=""; cin>>s;
	int mask=0;
	const int n=int(s.size());
	vector<int>a,b;
	a.reserve(s.size());
	b.reserve(s.size());
	for(int i=0;i<n;++i){
		t+=s[i];
		if(s[i]=='1') mask|=1<<(t.size()-1);
		if(t.size()==6){
			if(binary_search(all(oops),mask)){
				continue;
			}
			else{
				dbg(mask,t);
				const int base=i-5;
				for(int j=0;j<(M-1);++j){
					if(dpmask[mask]>>j&1){
						a.emplace_back(base+j);
					}
					else{
						b.emplace_back(base+j);
					}
				}
				t.clear();
				mask=0;
			}
		}
		else if(t.size()==7){
			dbg(mask,t);
			const int base=i-6;
			if(binary_search(all(oops2),mask)){ // failed
				a.emplace_back(base+fuck[t][0]);
				a.emplace_back(base+fuck[t][1]);
				b.emplace_back(base+fuck[t][2]);
				b.emplace_back(base+fuck[t][3]);
			}
			else{
				for(int j=0;j<M;++j) if(dps[mask]>>j&1){
					a.emplace_back(base+j);
				}
				for(int j=0;j<M;++j) if(dpt[mask]>>j&1){
					b.emplace_back(base+j);
				}
			}
			t.clear();
			mask=0;
		}
	}
	dbg(a.size(),b.size());
	assert(a.size()==b.size());
	for(int i=0;i<(int)(a.size());++i){
		assert(s[a[i]]==s[b[i]]);
	}
	cout<<a.size()<<'\n';
	for(auto x:a) cout<<x<<' ';
	cout<<'\n';
	for(auto x:b) cout<<x<<' ';
	return 0;
}
