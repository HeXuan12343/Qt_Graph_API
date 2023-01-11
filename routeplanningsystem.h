#ifndef ROUTEPLANNINGSYSTEM_H
#define ROUTEPLANNINGSYSTEM_H

#include <QString>


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

private:
    WUSGraph<V , W> priGraph;
    WUSGraphClient<V , W> graphClient;
    void PrintCity(V v)
    {
        qDebug()<<QString::fromStdString(v);
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

}

template<class V, class W>
void RoutePlanningSystem<V, W>::ShowSysteamInfo()
{
    int cityCount = priGraph.vertexCount();
    qDebug()<<"City count is\t"<<cityCount;//输出城市数
    auto cityArray = priGraph.getVertices();
    qDebug()<<"城市名称如下:";
    for(int i = 1 ;i <= cityCount; i++){//输出所有城市
        qDebug()<<QString::fromStdString(cityArray[i]);
    }
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
    graphClient.DFS(priGraph , visit);
}

template<class V, class W>
int RoutePlanningSystem<V, W>::maxNeiborCityCount()
{
    return this->MaxDegree(priGraph);
}





#endif // ROUTEPLANNINGSYSTEM_H
