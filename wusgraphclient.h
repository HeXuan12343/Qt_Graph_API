#ifndef WUSGRAPHCLIENT_H
#define WUSGRAPHCLIENT_H
#include<iostream>
#include"wusgraph.h"
#include"minindexheap.h"
#include"minspanforest.h"
#include"minspantree.h"
#include"wqupcufset.h"

template<class V,class W>
class WUSGraphClient:public WUSGraph<V,W>
{
public:
    WUSGraphClient();
    void CreatGraphFromFile(std::string filepath,WUSGraph<V,W>& h);//从给定文件路径filepath读取
    int MaxDegree(const WUSGraph<V,W>& g);//求g的最大顶点度数
    void Print(const WUSGraph<V,W>& g);//输出
    void DFS(WUSGraph<V,W>& g,void (*vist)(...));//深度优先遍历 访问函数是（*visit）（）
    void BFS(WUSGraph<V,W>& g,void (*vist)(...));//广度优先遍历 访问函数是（*visit）（）
    void Kruskal(const WUSGraph<V,W>& g,MinSpanForest<V,W> &msf);//优化的Kruskal方法求解最小生成森林msf
    void Dijkstra(const WUSGraph<V,W>& g,int &s,MinSpanTree<V,W> &mst);//优化的Dijkstra求解g源点
    void Prim(const WUSGraph<V,W>& g, MinSpanForest<V,W> &msf);//
    void LongestPath(const WUSGraph<V,W>& g,Vertex<V,W> &s,MinSpanTree<V,W> &mst);
    void Steiner(const WUSGraph<V,W>& g,int* objectlist,MinSpanForest<V,W> &msf);
};

#endif // WUSGRAPHCLIENT_H
