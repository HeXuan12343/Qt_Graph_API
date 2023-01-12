#ifndef ROUTEPLANNINGSYSTEM_H
#define ROUTEPLANNINGSYSTEM_H

#include <QString>
#include <QList>

#include "wusgraphclient.h"



template<class V,class W>
class RoutePlanningSystem : public WUSGraphClient<V , W>
{
public:
    RoutePlanningSystem(int v);//构造函数初始化交通系统3.1
    bool addCity(const V cityName);//添加城市3.2
    bool removeCity(const V cityName);//删除城市3.2
    bool resetCityInfo(const V cityName);//重设城市信息3.2
    bool addRoad(const V c1 , const V c2 , W cost);//添加交通道路3.2
    bool removeRoad(const V c1 , const V c2);//删除道路3.2
    bool resetRoadInfo(const V c1 , const V c2);//重设道路信息3.2
    void ReadFileAndInit(QString FilePath);//读取文件构建交通系统3.3
    void ShowSysteamInfo();//展示交通系统信息 城市数、所有城市、相邻城市间的道路数、所有道路3.4
    double Sparseness();//计算图的稀疏程度3.5
    int ConnectedComponentCount();//计算连通分量数量3.6
    bool isHaveLoop();//判断连通分量里面是否有环3.7
    bool isInCity(V cityName);//判断该城市是否在交通库中3.8
    bool isInRoad(V c1 , V c2);//判断该道路是否在交通库中3.8
    int NeiborsCount(V cityName);//返回邻接城市数量3.8
    W getRoadDistance(V c1 , V c2);//计算道路的距离3.8
    void getNeiborsCity(V cityName);//输出城市的所有相邻城市3.9
    void getRechableCity(V cityName , void (*visit) (V));//输出从该城市出发可以到达的所有城市3.10
    int maxNeiborCityCount();//输出相邻城市数最多的城市数3.11
    void showMinDistance(V c1 , V c2);//输出两个城市之间的最短路径3.12
    void showPrimForest(V cityName);//prim3.14
    void showKruskalForest(V cityName);//kruskal3.15
    void showMaxDistance(V cityName);//3.18
    void showRangCity(V cityName , W R);//3.16

private:
    WUSGraph<V , W> priGraph;
    WUSGraphClient<V , W> graphClient;
    void PrintCity(V v)
    {
        qDebug()<<QString::fromStdString(v);
    }
    void DFSforCompent(WUSGraph<V , W> &g,bool  *v , V verList[] , V ver)
    {
        v[ver]=true;//作访问标志
        Neighbors<int, W> neighbor=g.getNeighbors(ver);//获取所有邻接顶点
        auto *first=neighbor.neiborList.getFirst();//头结点
        auto *p=first->rLink;//获取第一个邻接顶点
        while(p!=first){//当结点存在
            Vertex<int , W> Vdata=p->data;
            int index=Vdata.data;
            if(!v[index])
                DFSforCompent(g,v,verList,verList[index]);
            p=p->rLink;
        }
    }

    int DFSForLoop(WUSGraph<V , W> &g,bool  *v ,V* vArray,int n ,V verList[] , V ver)
    {
        v[ver]=true;//作访问标志
        Neighbors<int, W> neighbor=g.getNeighbors(ver);//获取所有邻接顶点
        auto *first=neighbor.neiborList.getFirst();//头结点
        auto *p=first->rLink;//获取第一个邻接顶点
        while(p!=first){//当结点存在
            Vertex<int , W> Vdata=p->data;
            int index=Vdata.data;
            vArray[ver] = index;
            if(vArray[index] == ver){
                cout<<index<<"->"<<ver<<endl;
            }
            if(!v[index])
                DFSForLoop(g,v,vArray ,n, verList,verList[index]);
            p=p->rLink;
        }
    }
};

template<class V, class W>
RoutePlanningSystem<V, W>::RoutePlanningSystem(int v)
{
    priGraph.InitGraph(v);
}

template<class V, class W>
bool RoutePlanningSystem<V, W>::addCity(const V cityName)
{
    priGraph.addVertex(cityName);
}

template<class V, class W>
bool RoutePlanningSystem<V, W>::removeCity(const V cityName)
{
    priGraph.removeVertex(cityName);
}

template<class V, class W>
bool RoutePlanningSystem<V, W>::addRoad(const V c1, const V c2, W cost)
{
    priGraph.addEdge(c1 , c2 , cost);
}

template<class V, class W>
bool RoutePlanningSystem<V, W>::removeRoad(const V c1, const V c2)
{
    priGraph.removeEdge(c1 , c2);
}

template<class V, class W>
void RoutePlanningSystem<V, W>::ReadFileAndInit(QString FilePath)
{
    std::string filePath = FilePath.toStdString();
    const char *p = filePath.c_str();
    graphClient.CreatGraphFromFile(p , priGraph);
}

template<class V, class W>
void RoutePlanningSystem<V, W>::ShowSysteamInfo()
{
//    int cityCount = priGraph.vertexCount();
//    qDebug()<<"City count is\t"<<cityCount;//输出城市数
//    auto cityArray = priGraph.getVertices();
//    qDebug()<<"城市名称如下:";
//    for(int i = 1 ;i <= cityCount; i++){//输出所有城市
//        qDebug()<<QString::fromStdString(cityArray[i]);
//    }
    graphClient.Print(priGraph);
}

template<class V, class W>
double RoutePlanningSystem<V, W>::Sparseness()
{
    int CityCount = priGraph.vertexCount();
    auto cityArray = priGraph.getVertices();
    double degreeSum;
    for(int i = 1; i < CityCount; i++){
        degreeSum += priGraph.Degree(cityArray[i]);
    }
    double degreeAverage = degreeSum / CityCount;
    return degreeAverage / (CityCount - 1);
}

template<class V, class W>
int RoutePlanningSystem<V, W>::ConnectedComponentCount()
{

    int n=priGraph.vertexCount();
    bool *visited=new bool[n+1];//辅助数组
    for(int i=0;i<n+1;i++)//初始化
        visited[i]=false;
    auto vertexList =priGraph.getVertices();
    int count = 0;
    for(int i= 1; i <= n; i++){
        if(!visited[vertexList[i]]){
            count++;
            DFSforCompent(priGraph , visited , vertexList , vertexList[i]);
        }

    }

    return count-1;
}

template<class V, class W>
bool RoutePlanningSystem<V, W>::isHaveLoop()
{
    int n=priGraph.vertexCount();
    bool *visited=new bool[n+1];//辅助数组
    V *eArray = new V[n+1];//辅助数组
    for(int i=0;i<n+1;i++){//初始化
        visited[i]=false;
        eArray[i] = 0;
    }
    auto vertexList =priGraph.getVertices();
    int count = 0;

    for(int i= 1; i <= n; i++){
        if(!visited[vertexList[i]]){
            count++;
            DFSForLoop(priGraph , visited ,eArray,n, vertexList , vertexList[i]);
        }

    }
}

template<class V, class W>
bool RoutePlanningSystem<V, W>::isInCity(V cityName)
{
    return priGraph.isVertex(cityName);
}

template<class V, class W>
bool RoutePlanningSystem<V, W>::isInRoad(V c1, V c2)
{
    return priGraph.isEdge(c1 , c2);
}

template<class V, class W>
int RoutePlanningSystem<V, W>::NeiborsCount(V cityName)
{
    return priGraph.Degree(cityName);
}

template<class V, class W>
W RoutePlanningSystem<V, W>::getRoadDistance(V c1, V c2)
{
    return priGraph.getWeight(c1 , c2);
}

template<class V, class W>
void RoutePlanningSystem<V, W>::getNeiborsCity(V cityName)
{
    auto verList = priGraph.getVertices();
    Neighbors<V , W> neibor = priGraph.getNeighbors(cityName);
    DblNode<int , W> *first = neibor.neiborList.getFirest();
    DblNode<int , W> *p = first->rLink;
    while (p != first) {
        qDebug()<<verList[p->data]<<",";
    }
}

template<class V, class W>
void RoutePlanningSystem<V, W>::getRechableCity(V cityName, void (*visit)(V))
{
    graphClient.DFS(priGraph , cityName ,visit);
}

template<class V, class W>
int RoutePlanningSystem<V, W>::maxNeiborCityCount()
{
    return graphClient.MaxDegree(priGraph);
}

template<class V, class W>
void RoutePlanningSystem<V, W>::showMinDistance(V c1, V c2)
{
    int sz = priGraph.vertexCount();
    MinSpanTree<int , int> mst(sz);
    graphClient.Dijkstra(priGraph , c1 ,mst);
    mst.PrintTree();
}

template<class V, class W>
void RoutePlanningSystem<V, W>::showPrimForest(V cityName)
{
    int sz = priGraph.vertexCount();
    MinSpanForest<V , W> msf(sz);
    graphClient.Prim(priGraph , cityName , msf);
    msf.PrintTree();
}

template<class V, class W>
void RoutePlanningSystem<V, W>::showKruskalForest(V cityName)
{
    int sz = priGraph.vertexCount();
    MinSpanForest<V , W> msf(sz);
    graphClient.Kruskal(priGraph , msf);
    msf.PrintTree();
}

template<class V, class W>
void RoutePlanningSystem<V, W>::showMaxDistance(V cityName)
{
    int sz = priGraph.vertexCount();
    MinSpanTree<V , W> mst(sz);
    graphClient.LongestPath(priGraph , cityName , mst);
    mst.PrintTree();
}

template<class V, class W>
void RoutePlanningSystem<V, W>::showRangCity(V cityName, W R)
{
    auto neibor = priGraph.getNeighbors(cityName);
    auto *first = neibor.neiborList.getFirst();
    auto *p = first->rLink;
    while (p != first) {
        auto vt = p->data.data;
        if(priGraph.getWeight(cityName , vt) <= R){
            cout<<vt<<endl;
        }
        p = p->rLink;
    }
}





#endif // ROUTEPLANNINGSYSTEM_H
