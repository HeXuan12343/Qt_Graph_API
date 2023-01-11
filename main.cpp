#include "widget.h"

#include <QApplication>

#include<QDebug>

#include <iostream>


using namespace std;


#include <QTextStream>

#include <dblinkedlist.h>
#include <expandablearraylist.h>
#include "hashmap.h"
#include "wusgraph.h"
#include "wusgraphclient.h"
#include "minspanforest.h"
#include "minspantree.h"

void PrintCity(string v)
{
    qDebug()<<QString::fromStdString(v);
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget w;
    w.show();
/***** 双链表测试 *****/
//    DbLinkedList<std::string , int> l;
//    for(int i = 0; i < 20; i++){
//        l.Append(i);
//    }
//    qDebug()<<l.Size();
//    ExpandableArrayList<int> array(5);
//    for(int i = 0; i < 5; i++){
//        array[i] = i;
//    }
//    for(int i = 0; i < 5; i++){
//        qDebug()<<array[i];
//    }
//    array.resizeList(10);
//    for(int i = 0; i < 10; i++){
//        array[i] = i;
//    }
//    for(int i = 0; i < 10; i++){
//        qDebug()<<array[i];
//    }
/*****   HashMap测试  *****/
//    HashMap<std::string , int> m;
//    std::pair<std::string , int> ptest;
//    std::pair<std::string , int> ptest2;
//    ptest.first = "北京";
//    ptest.second = 5;
//    ptest2.first = "北方";
//    ptest2.second = 2;
//    m.Insert(ptest);
//    m.Insert(ptest2);
//    std::string test = "北京";
//    std::string test2 = "北方";
//    std::string test3="南京";
//    m.Clear();
//    qDebug()<<m.getValue(test);
//    qDebug()<<m.getValue(test2);

/*****  wushgraph测试 *****/
//    WUSGraph<std::string , int> g(5);
//    std::string test1 = "北京";
//    std::string test2 = "南京";
//    std::string test3 = "河北";
//    std::string test4 = "河南";
//    std::string test5 = "日本";
//    g.addVertex(test1);
//    g.addVertex(test2);
//    g.addVertex(test3);
//    g.addVertex(test4);
//    g.addVertex(test5);
//    auto *vList = g.getVertices();
//    for(int i = 0; i < 6; i++)
//    {
//        qDebug()<<QString::fromStdString(vList[i]);
//    }
//    g.removeVertex("北京");
//    qDebug()<<"删除顶点测试,"<<"remove"<<'\t'<<"北京"<<'\t'<<"1";
//    auto *vList2 = g.getVertices();
//    for(int i = 0; i < 6; i++)
//    {
//        qDebug()<<QString::fromStdString(vList2[i]);
//    }
//    g.addEdge(test1 , test2 , 50);
//    g.addEdge(test1 , test5 , 150);
//    g.addEdge(test3 , test2 , 60);
//    bool isEd = g.isEdge(test3 , test2);
//    qDebug()<<isEd;
//    qDebug()<<"删除边测试"<<"remove<河北,南京>"<<'\t'<<"<3,2>";
//    g.removeEdge(test3 , test2);
//    bool isEd2 = g.isEdge(test3 , test2);
//    qDebug()<<isEd2;
//    qDebug()<<"getWeight测试,"<<"cost for <北京,日本>"<<'\t'<<"150";
//    auto cost = g.getWeight(test1 , test5);
//    qDebug()<<cost;
//    qDebug()<<"getNeibors测试,Neibors of 北京"<<'\t'<<"2\t5";
//    Neighbors<int , int> neibor = g.getNeighbors(test1);
//    auto neiborList = neibor.neiborList;
//    auto costList = neibor.costList;
//    auto neiborFirst = neiborList.getFirst();
//    auto costFirst = costList.getFirst();
//    auto np = neiborFirst->rLink;
//    auto cp = costFirst->rLink;
//    while (np != neiborFirst) {
//        qDebug()<<np->data.data;
//        np = np->rLink;
//    }
//    qDebug()<<"权值为：";
//    while (cp != costFirst) {
//        qDebug()<<cp->data;
//        cp = cp->rLink;
//    }
/*****wusgraphclient测试*****/
    WUSGraph<std::string , int> g(5);
    std::string test1 = "北京";
    std::string test2 = "南京";
    std::string test3 = "河北";
    std::string test4 = "河南";
    std::string test5 = "日本";
    g.addVertex(test1);
    g.addVertex(test2);
    g.addVertex(test3);
    g.addVertex(test4);
    g.addVertex(test5);
    g.addEdge(test1 , test2 , 50);
    g.addEdge(test3 , test2 , 60);
    g.addEdge(test2 , test5 , 180);
    g.addEdge(test3 , test4 , 40);
    g.addEdge(test1 , test5 , 900);
    auto vList = g.getVertices();
    for(int i = 0; i < 6; i++){
        qDebug()<<QString::fromStdString(vList[i]);
    }
//    auto neibor = g.getNeighbors(test4);
//    auto *first = neibor.neiborList.getFirst();
//    auto *p = first->rLink;
//    while (p!= first) {
//        int index = p->data.data;
//        qDebug()<<"河南邻接顶点为"<<QString::fromStdString(vList[index]);
//        p = p->rLink;
//    }
    WUSGraphClient<string , int> gclint;
    int maxDegree = gclint.MaxDegree(g);
    qDebug()<<"获取最大顶点的度"<<maxDegree;
    qDebug()<<"DFS test**************";
    gclint.DFS(g ,test2, PrintCity);
    qDebug()<<"BFS test**************";
    gclint.BFS(g , PrintCity);
    qDebug()<<"Kruskal test**************";
    MinSpanForest<string , int> minForest(6);
    gclint.Kruskal(g , minForest);
    minForest.PrintTree();
    qDebug()<<"Dijkstra test**************";
    MinSpanTree<string,int> mst(6);
    gclint.Dijkstra(g,test1,mst);
    mst.PrintTree();
    qDebug()<<"Prim test**************";
    MinSpanForest<string , int> minForest_Prim(6);
//    gclint.Prim(g,test1,minForest_Prim);
    return a.exec();
}

