#include<cstdio>
#include<cstring>
#include<iostream>
#include<cstdlib>
#include<queue>

#define INF 0x3f3f3f3f

using namespace std;

/*这题要用C++交，G++交会WA*/

/* SPFA mincost-flow Template Start */

const int MaxN = 50*50+50+20;
const int MaxE = 2*(50*50*50+50+50*50)+20;

struct TEdge
{
	int u,v,cap,cost,next,pair;
};

struct TEdge edges[MaxE];
int head[MaxN],pre[MaxN];
int source,target,index;

void AddEdge(int src,int trg,int cap,int cst)
{
    index++;
    edges[index].u=src;
    edges[index].v=trg;
    edges[index].cap=cap;
    edges[index].cost=cst;
    edges[index].next=head[src];
    edges[index].pair=index+1; 
    head[src]=index;
    index++;
    edges[index].u=trg;
    edges[index].v=src;
    edges[index].cap=0;
    edges[index].cost=-cst;
    edges[index].next=head[trg];
    edges[index].pair=index-1; 
    head[trg]=index;
}

int SPFA()
{
    queue<int> q;
    int vis[MaxN],dis[MaxN],i,u,v;
    memset(vis,0,sizeof(vis));
    memset(dis,INF,sizeof(dis));
    dis[source]=0;
    vis[source]=1;
    q.push(source);
    while (!q.empty())
    {
        u=q.front();
        q.pop();
        for (i=head[u];i!=-1;i=edges[i].next)
        {
            v=edges[i].v;
            if (edges[i].cap && dis[v]>dis[u]+edges[i].cost)
            {
                dis[v]=dis[u]+edges[i].cost;
                pre[v]=i;
                if (!vis[v])
                {
                    vis[v]=1;
                    q.push(v);
                } 
            }
        }
        vis[u]=0;
    }
    if (dis[target]==INF) return 0; else return 1;
}

int Augment()
{
    int u,p,minflow=INF,mincost=0;
    for (u=target;u!=source;u=edges[edges[p].pair].v)
    {
        p=pre[u];
        if (minflow>edges[p].cap) minflow=edges[p].cap;
    } 
    for (u=target;u!=source;u=edges[edges[p].pair].v)
    {
        p=pre[u];
        edges[p].cap-=minflow;
        edges[edges[p].pair].cap+=minflow;
        mincost+=minflow*edges[p].cost;
    }
    return(mincost);
}

int MinCostFlow()
{
    int ans=0;
    while (SPFA()) ans+=Augment();
    return(ans); 
}

void InitMinCostFlow(int u,int v)
{
    source=u;
    target=v;
    index=0;
    memset(head,-1,sizeof(head));
}

/* SPFA mincost-flow Template Over */

int n,m;
int map[51][51];

void ReadData()
{
    int i,j,k;
    scanf("%d%d",&n,&m);
    for (i=1;i<=n;i++)
        for (j=1;j<=m;j++) scanf("%d",&map[i][j]);
    InitMinCostFlow(0,n+n*m+1);
    for (i=1;i<=n;i++) 
	{
        AddEdge(source,i,1,0);
    }
    for (i=1;i<=n;i++)
        for (j=1;j<=m;j++)
            for (k=1;k<=n;k++)
            {
                AddEdge(i,n+(j-1)*n+k,1,map[i][j]*k);
            }
    for(i=1;i<=m;i++)
        for(j=1;j<=n;j++)
        {
            AddEdge(n+(i-1)*n+j,target,1,0);
        }
}

int main()
{
    int Cases,ans;
    freopen("poj3686.txt","r",stdin);
    freopen("poj3686ans.txt","w",stdout);
    scanf("%d",&Cases);
    while (Cases--)
    {
        ReadData();
        ans=MinCostFlow();
        printf("%0.6lf\n",ans*1.0/n);
    }
}
