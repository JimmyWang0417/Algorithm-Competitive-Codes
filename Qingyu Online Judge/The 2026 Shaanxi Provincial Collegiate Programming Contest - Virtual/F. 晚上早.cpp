#include <bits/stdc++.h>
#define int long long
using namespace std;
inline int read(){
    int x=0,f=1;char ch=getchar();
    for(;!isdigit(ch);ch=getchar())f^=ch=='-';
    for(;isdigit(ch);ch=getchar())x=x*10+(ch^48);
    return f?x:-x;
}

int sgn(int t){
    if(6<=t&&t<=17)return 0;
    else return 1;
}

signed main(){
    int d=read(),t0=read(),ans=-1;
    for(int i=0;i<24;++i){
        if(!sgn((t0+i)%24)&&sgn((t0+i+d)%24)){
            ans=i;
            break;
        }
    }
    printf("%lld\n",ans);
    return 0;
}
