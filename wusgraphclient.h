#ifndef WUSGRAPHCLIENT_H
#define WUSGRAPHCLIENT_H
#include<iostream>
#include"wusgraph.h"
#include"minindexheap.h"
#include"minspanforest.h"
#include"minspantree.h"
#include"wqupcufset.h"
#include"myqueue.h"
#include"minheap.h"
#include<QDebug>
template<class V,class W>
class WUSGraphClient:public WUSGraph<V,W>
{
public:
    WUSGraphClient();
    void CreatGraphFromFile(std::string filepath,WUSGraph<V,W>& h);//从给定文件路径filepath读取
    int MaxDegree(WUSGraph<V,W>& g);//求g的最大顶点度数
    void Print( WUSGraph<V,W>& g);//输出
    void DFS(WUSGraph<V,W>& g,V& s,void (*visit)(V));//深度优先遍历 访问函数是（*visit）（）
    void DFS(WUSGraph<V,W>& g,V v,bool visited[],V vertexlist[],void (*visit)(V));//DFS子过程
    void BFS(WUSGraph<V,W>& g,void (*visit)(V));//广度优先遍历 访问函数是（*visit）（）
    void Kruskal( WUSGraph<V,W>& g,MinSpanForest<V,W> &msf);//优化的Kruskal方法求解最小生成森林msf
    void Dijkstra( WUSGraph<V,W>& g,V &s,MinSpanTree<V,W> &mst);//优化的Dijkstra求解g源点
    void Prim( WUSGraph<V,W>& g,V &s, MinSpanForest<V,W> &msf);//
    void LongestPath( WUSGraph<V,W>& g,V &s,MinSpanTree<V,W> &mst);
    void Steiner(const WUSGraph<V,W>& g,int* objectlist,MinSpanForest<V,W> &msf);

private:
    HashMap<string,int> APImap;
};

template<class V, class W>
WUSGraphClient<V, W>::WUSGraphClient()
{
    std::pair<string , int> p1("北京" , 1);
    std::pair<string , int> p2("南京" , 2);
    std::pair<string , int> p3("河北" , 3);
    std::pair<string , int> p4("河南" , 4);
    std::pair<string , int> p5("日本" , 5);
    APImap.Insert(p1);
    APImap.Insert(p2);
    APImap.Insert(p3);
    APImap.Insert(p4);
    APImap.Insert(p5);
}

template<class V,class W>
int WUSGraphClient<V,W>::MaxDegree(WUSGraph<V, W> &g)
{
    int max=0;
    int n=g.vertexCount();
    V* vertexList=g.getVertices();
    for(int i=1;i<=n;i++)
    {
//        qDebug()<<QString::fromStdString(vertexList[i]);
        max=g.Degree(vertexList[i])>max?g.Degree(vertexList[i]):max;
    }

    return max;
}

template<class V,class W>
void WUSGraphClient<V,W>::Print( WUSGraph<V,W>& g){
    int n,m;
    V* vertexList=g.getVertices();

}

template<class V,class W>
void WUSGraphClient<V,W>::DFS(WUSGraph<V, W> &g, V& v,void (*visit)(V)){
    int n=g.vertexCount();
    bool *visited=new bool[n+1];//辅助数组
    for(int i=0;i<n+1;i++)//初始化
        visited[i]=false;
    auto vertexList =g.getVertices();

    DFS(g,v,visited,vertexList,visit);
    delete [] visited;

}

template<class V, class W>
void WUSGraphClient<V,W>::DFS(WUSGraph<V, W> &g, V v, bool visited[], V vertexlist[], void (*visit)(V))
{
    int n=g.vertexCount();
    int ver=APImap.getValue(v);
    visit(v);//访问顶点
    visited[ver]=true;//作访问标志
    Neighbors<int, W> neighbor=g.getNeighbors(v);//获取所有邻接顶点
    auto *first=neighbor.neiborList.getFirst();//头结点
    auto *p=first->rLink;//获取第一个邻接顶点
    while(p!=first){//当结点存在
        Vertex<int , W> Vdata=p->data;
        int index=Vdata.data;
        if(!visited[index])
            DFS(g,vertexlist[index],visited,vertexlist,visit);
        p=p->rLink;
    }
}


template<class V,class W>
void WUSGraphClient<V,W>::BFS(WUSGraph<V,W>& g,void (*visit)(V)){
    int n=g.vertexCount();
    bool *visited=new bool[n];//辅助数组
    for(int i=0;i<n;i++)//初始化
        visited[i]=false;
    V* vertexList=g.getVertices();//获得顶点数组
    V v=vertexList[1];//取源点
    int ver=APImap.getValue(v);//取对应整数值
    visit(v);//访问源点
    visited[ver]=true;//作访问标记
    myQueue<V> Q;
    Q.EnQueue(v);//顶点入队列
    //分层访问
        while(!Q.isEmpty()){
            Q.DeQueue(v);//出队列
          //获取第一个邻接顶点
            Neighbors<int, W> neighbor=g.getNeighbors(v);//获取所有邻接顶点
            auto *first=neighbor.neiborList.getFirst();//头结点
            auto *p=first->rLink;//获取第一个邻接顶点
            while(p!=first){//若邻接顶点存在
                Vertex<int , W> Vdata=p->data;
                int index=Vdata.data;
                if(!visited[index]){//如果未访问
                    visit(vertexList[index]);//访问顶点
                    visited[index]=true;//作访问节点
                    Q.EnQueue(vertexList[index]);
                }
                p=p->rLink;//访问下一个邻接顶点
            }

        }

    delete [] visited;
}

template<class V, class W>
void WUSGraphClient<V,W>::Kruskal( WUSGraph<V, W> &g, MinSpanForest<V, W> &msf)
{
    MinSpanForestNode<V,W>ed;
    int u,v;
    int count;
    int n=g.vertexCount();
    int m=g.edgeCount();
    MinHeap<MinSpanForestNode<V,W>>H(m);
    WQUPCUFset F(n+1);
    set<MinSpanForestNode<V,W>> Edge;
    V* verlist=g.getVertices();
  //取边
    for(int i=1;i<n+1;i++){
        Neighbors<int,W> neighbor=g.getNeighbors(verlist[i]);//获取该顶点的邻接边
        auto *first=neighbor.neiborList.getFirst();//头结点
        auto *p=first->rLink;//获取第一个邻接顶点
        while(p!=first){//若邻接结点存在
            Vertex<int , W> Vdata=p->data;
            int index=Vdata.data;
            u=APImap.getValue(verlist[i]);
            v=APImap.getValue(verlist[index]);
            ed.tail=u;
            ed.head=v;
            ed.key=g.getWeight(verlist[i],verlist[index]);
//            H.Insert(ed);
            Edge.insert(ed);
            p = p->rLink;
        }
    }
        typename set<MinSpanForestNode<V,W>>::iterator it;
        for(it=Edge.begin();it!=Edge.end();it++){
            auto temp = *it;
            H.Insert(temp);
        }

    count=1;
    while (count<n) {
        H.Remove(ed);
        u=F.Find(ed.tail);
        v=F.Find(ed.head);
        if(u!=v){
            F.Union(u,v);
            msf.Insert(ed);
            count++;
        }
    }

}

template<class V, class W>
void WUSGraphClient<V,W>::Dijkstra( WUSGraph<V, W> &g, V &s, MinSpanTree<V, W> &mst)
{
    int n=g.vertexCount();
//    MinIndexHeap<MinNode<V,W>> heap(n);
    V* vertexlist=g.getVertices();
    int *dist=new int[n+1];//储存到各顶点的最短距离
    bool *visited=new bool[n+1];
    int *path=new int[n+1];//路径
    for(int i=1;i<n+1;i++) {
       visited[i]=false;
       path[i]=-1;
       dist[i]=2147483646;
    }
    dist[APImap.getValue(s)]=0;
    MinNode<V,W> q;
    MinNode<V,W>* node=new MinNode<V,W>[n];
    for(int i=0;i<n;i++){
        MinNode<V,W> t;
        t.vertex=vertexlist[i+1];
        t.cost=dist[i+1];
        node[0]=t;
    }
    node[APImap.getValue(s)].cost=0;
    MinIndexHeap<MinNode<V,W>> heap(node,n);
    while (!heap.IsEmpty()) {
        heap.Remove(q);
        V v=q.vertex;//选定顶点
        int v_int=APImap.getValue(v);//选定顶点的整数编号
        if(visited[APImap.getValue(v)])
            continue;
        visited[APImap.getValue(v)]=true;
        Neighbors<int,W> neighbor=g.getNeighbors(v);//获取该顶点的邻接边
        auto *first=neighbor.neiborList.getFirst();//头结点
        auto *p=first->rLink;//获取第一个邻接顶点
        while (p!=first) {
            Vertex<int , W> Vdata=p->data;
            int index=Vdata.data;
            W w=g.getWeight(v,vertexlist[index]);
            if(!visited[index]&&dist[v_int]+w<dist[index]){
                dist[index]=dist[v_int]+w;
                path[index]=v_int;
                MinNode<V,W> modify;
                modify.vertex=vertexlist[index];
                modify.cost=dist[index];
                heap.Modify(index,modify);
            }
            p=p->rLink;
        }

    }
    for(int i=1;i<n+1;i++){
        if(path[i]!=-1){
            MSTEdgeNode<V,W> treenode;
            treenode.head=path[i];
            treenode.tail=i;
            treenode.key=g.getWeight(vertexlist[i],vertexlist[path[i]]);
            mst.Insert(treenode);
        }
    }
}

template<class V, class W>
void WUSGraphClient<V,W>::Prim( WUSGraph<V, W> &g,V &s, MinSpanForest<V, W> &msf)
{
    MinSpanForestNode<V,W> ed;
    V* vertexlist=g.getVertices();
    int n=g.vertexCount();
    int m=g.edgeCount();
    MinIndexHeap<MinSpanForestNode<V,W>> H(m);
    bool *Vmst=new bool[n+1];
    for(int i=1;i<n+1;i++){
        Vmst[i]=false;
    }
    int begin=APImap.getValue(s);
    Vmst[begin]=true;
    int count=1;
    do{
        Neighbors<int,W> neighbor=g.getNeighbors(s);//获取该顶点的邻接边
        auto *first=neighbor.neiborList.getFirst();//头结点
        auto *p=first->rLink;//获取第一个邻接顶点
        while (p!=first) {//遍历s的所有顶点
            Vertex<int , W> Vdata=p->data;
            int index=Vdata.data;
            if(!Vmst[index]){
                ed.tail=APImap.getValue(s);
                ed.head=index;
                H.Insert(ed);
            }
            p=p->rLink;
        }
        while (!H.IsEmpty()) {
            H.Remove(ed);
            if(!Vmst[ed.head]){
                s=vertexlist[ed.head];
                msf.Insert(ed);
                Vmst[ed.head]=true;
                count++;
                break;
        }
    }
    }while (count<n);
}

template<class V, class W>
void WUSGraphClient<V,W>::LongestPath( WUSGraph<V, W> &g, V &s, MinSpanTree<V, W> &mst)
{
    int n=g.vertexCount();
    int i,j,k;
    int begin=APImap.getValue(s);
    V* vertexlist=g.getVertices();
    int *dist=new int[n+1];//储存到各顶点的最长距离
    bool *visited=new bool[n+1];
    int *path=new int[n+1];//路径
    for( i=1;i<n+1;i++) {
       visited[i]=false;
       V u=vertexlist[i];
       dist[i]=g.getWeight(s,u);
       if (i != begin && dist[i] > 0) path[i] = begin;
       else path[i] = -1;
    }
    visited[begin]=true;
    dist[begin]=0;
    for( i=0;i<n-1;i++){
        int max=0;
        V v=s;
        for(j=1;j<n+1;j++)
            if(!visited[j] && dist[j]>0){
                v=vertexlist[j];
                max=dist[j];
            }
        visited[APImap.getValue(v)]=true;
        Neighbors<int,W> neighbor=g.getNeighbors(v);//获取该顶点的邻接边
        auto *first=neighbor.neiborList.getFirst();//头结点
        auto *p=first->rLink;//获取第一个邻接顶点
        while (p!=first) {
            Vertex<int , W> Vdata=p->data;
            int index=Vdata.data;
            W w=g.getWeight(v,vertexlist[index]);
            if(!visited[index]&&dist[APImap.getValue(v)]+w>dist[index]){
                dist[index]=dist[APImap.getValue(v)]+w;
                path[index]=APImap.getValue(v);
            }
            p=p->rLink;
        }
    }
    for(int i=1;i<n+1;i++){
        if(path[i]!=-1){
            MSTEdgeNode<V,W> treenode;
            treenode.head=path[i];
            treenode.tail=i;
            treenode.key=g.getWeight(vertexlist[i],vertexlist[path[i]]);
            mst.Insert(treenode);
        }
    }
}

template<class V, class W>
void WUSGraphClient<V,W>::Steiner(const WUSGraph<V, W> &g, int *objectlist, MinSpanForest<V, W> &msf)
{

}

#endif // WUSGRAPHCLIENT_H
