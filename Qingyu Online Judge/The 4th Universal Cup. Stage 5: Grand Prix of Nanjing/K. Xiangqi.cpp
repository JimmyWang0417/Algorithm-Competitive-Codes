#include<bits/stdc++.h>
const int dx[8]={-2,2,-2,2,-1,1,-1,1};
const int dy[8]={1,-1,-1,1,2,-2,-2,2};
const int ndx[8]={-1,1,-1,1,0,0,0,0};
const int ndy[8]={0,0,0,0,1,-1,-1,1};
void solve()
{
    int x1,x2,y1,y2;
    std::cin>>x1>>y1>>x2>>y2;
    int fl=1;
    for(int i=0;i<8;i++){
        if(x1+dx[i]==x2&&y1+dy[i]==y2) fl=0;
    }
    if(!fl) {
        std::cout<<"NO\n";
        return;
    }
    fl=0;
    for(int i=0;i<8;i++){
        if(x1+dx[i]>=1&&x1+dx[i]<=9&&y1+dy[i]>=1&&y1+dy[i]<=10){
            if(x1+dx[i]!=x2&&y1+dy[i]!=y2&&(x1+ndx[i]!=x2||y1+ndy[i]!=y2)) fl=1;
        }
    }
    if(fl) std::cout<<"NO\n";
    else std::cout<<"YES\n";
    
}
int main()
{
    int T;std::cin>>T;
    while(T--) solve();
}
