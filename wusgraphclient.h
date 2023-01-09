#ifndef WUSGRAPHCLIENT_H
#define WUSGRAPHCLIENT_H
#include<iostream>
#include"wusgraph.h"
#include"minindexheap.h"
#include"minspanforest.h"
#include"minspantree.h"
#include"wqupcufset.h"
#include"myqueue.h"

template<class V,class W>
class WUSGraphClient:public WUSGraph<V,W>
{
public:
    WUSGraphClient();
    void CreatGraphFromFile(std::string filepath,WUSGraph<V,W>& h);//从给定文件路径filepath读取
    int MaxDegree( WUSGraph<V,W>& g);//求g的最大顶点度数
    void Print( WUSGraph<V,W>& g);//输出
    void DFS(WUSGraph<V,W>& g,void (*visit)(V));//深度优先遍历 访问函数是（*visit）（）
    void DFS(WUSGraph<V,W>& g,V v,bool visited[],V vertexlist[],void (*visit)(V));//DFS子过程
    void BFS(WUSGraph<V,W>& g,void (*visit)(V));//广度优先遍历 访问函数是（*visit）（）
    void Kruskal(const WUSGraph<V,W>& g,MinSpanForest<V,W> &msf);//优化的Kruskal方法求解最小生成森林msf
    void Dijkstra(const WUSGraph<V,W>& g,int &s,MinSpanTree<V,W> &mst);//优化的Dijkstra求解g源点
    void Prim(const WUSGraph<V,W>& g, MinSpanForest<V,W> &msf);//
    void LongestPath(const WUSGraph<V,W>& g,Vertex<V,W> &s,MinSpanTree<V,W> &mst);
    void Steiner(const WUSGraph<V,W>& g,int* objectlist,MinSpanForest<V,W> &msf);

private:
    HashMap<string,int> APImap;
};

template<class V,class W>
int WUSGraphClient<V,W>::MaxDegree( WUSGraph<V, W> &g)
{
    int max=0;
    int n=g.vertexCount();
    V* vertexList=g.getVertices();
    for(int i=0;i<n;i++)
    {
        max=g.Degree(vertexList[i])>max?g.Degree(vertexList[i]):max;
    }
    delete [] vertexList;
    return max;
}

template<class V,class W>
void WUSGraphClient<V,W>::Print( WUSGraph<V,W>& g){
    int n,m;
    V* vertexList=g.getVertices();

}

template<class V,class W>
void WUSGraphClient<V,W>::DFS(WUSGraph<V,W>& g,void (*visit)(V)){
    int n=g.vertexCount();
    bool *visited=new bool[n+1];//辅助数组
    for(int i=0;i<n;i++)//初始化
        visited[i]=false;
    V* vertexList=g.getVertices();
    V s=vertexList[1];
    DFS(g,s,visited,vertexList,n,visit);
    delete [] visited;
    delete [] vertexList;
}

template<class V, class W>
void WUSGraphClient<V,W>::DFS(WUSGraph<V,W>& g,V v, bool visited[], V vertexlist[],void (*visit)(V))
{
    int n=g.vertexCount();
    int ver=APImap.getValue(v);
    visit(v);//访问顶点
    visited[ver]=true;//作访问标志
    Neighbors<int, W> neighbor=g.getNeighbors(v);//获取所有邻接顶点
    DblNode<int,W> *first=neighbor.neiborList.getFirst();//头结点
    DblNode<int,W> *p=first->rLink;//获取第一个邻接顶点
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
    visited[ver]=true;//作访问标记
    myQueue<V> Q;
    Q.EnQueue(v);//顶点入队列
    //分层访问
        while(!Q.isEmpty()){
            Q.DeQueue(v);//出队列
          //获取第一个邻接顶点
            Neighbors<int, W> neighbor=g.getNeighbors(v);//获取所有邻接顶点
            DblNode<int,W> *first=neighbor.neiborList.getFirst();//头结点
            DblNode<int,W> *p=first->rLink;//获取第一个邻接顶点

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
        delete [] vertexList;
}

template<class V, class W>
void WUSGraphClient<V,W>::Kruskal(const WUSGraph<V, W> &g, MinSpanForest<V, W> &msf)
{

}

#endif // WUSGRAPHCLIENT_H
