#include<bits/stdc++.h>
using namespace std;
const int block_size=450;
const int LIM=102;
const int N=200007;
int n,a[N], q,l,r,x,y; int lazy[block_size][LIM];
void preprocess()
{
    for(int id=0;id<block_size;++id)
        for(int i=0;i<LIM;++i)
            lazy[id][i]=i;
}
void block_update(int id, int oval, int nval)
{
    for(int i=0;i<LIM;++i)
        if(lazy[id][i]==oval) lazy[id][i]=nval;
}
void update(int l, int r, int oval, int nval)
{
    int blockL=(l+block_size)/block_size;
    int blockR=r/block_size;
    if(blockL>=blockR){
        for(int i=blockR*block_size;i<min((blockR+1)*block_size,n);++i)
            a[i]=lazy[blockR][a[i]];
        for(int i=0;i<LIM;++i) lazy[blockR][i]=i;
        for(int i=l;i<=r;++i)
            if(a[i]==oval) a[i]=nval;
        return ;
    }
    for(int id=blockL;id<blockR;++id)
        block_update(id,oval,nval);

    //update phan du ben trai
    for(int i=(blockL-1)*block_size;i<blockL*block_size;++i)
        a[i]=lazy[blockL-1][a[i]];
     for(int i=0;i<LIM;++i) lazy[blockL-1][i]=i;
    for(int i=l;i<blockL*block_size;++i)
    {
         if(a[i]==oval) a[i]=nval;
    }

    //update phan du ben phai
     for(int i=blockR*block_size;i<min((blockR+1)*block_size,n);++i)
            a[i]=lazy[blockR][a[i]];
        for(int i=0;i<LIM;++i) lazy[blockR][i]=i;
        for(int i=blockR*block_size;i<=r;++i)
            if(a[i]==oval) a[i]=nval;
}

int main()
{
    //freopen("dulieu.txt","r",stdin);
    cin>>n;
    for(int i=0;i<n;++i)
        cin>>a[i];
    preprocess();
    cin>>q;
    while(q--)
    {
        cin>>l>>r>>x>>y;
        --l; --r;
        update(l,r,x,y);
    }
    for(int i=0;i<n;++i)
        a[i]=lazy[i/block_size][a[i]];
    for(int i=0;i<n;++i)
        cout<<a[i]<<" ";
    return 0;
}
