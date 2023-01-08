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


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget w;
    w.show();

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
    WUSGraph<std::string , int> g;
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
    auto *vList = g.getVertices();
    for(int i = 0; i < 5; i++)
    {
        qDebug()<<vList[i];
    }
    g.removeVertex("北京");
    qDebug()<<"删除顶点测试,"<<"remove"<<'\t'<<"北京"<<'\t'<<"1";
    auto *vList2 = g.getVertices();
    for(int i = 0; i < 4; i++)
    {
        qDebug()<<vList2[i];
    }
    g.addEdge(test1 , test2 , 50);
    g.addEdge(test1 , test5 , 150);
    g.addEdge(test3 , test2 , 60);
    bool isEd = g.isEdge(test3 , test2);
    qDebug()<<isEd;
    qDebug()<<"删除边测试"<<"remove<河北,南京>"<<'\t'<<"<3,2>";
    g.removeEdge(test3 , test2);
    bool isEd2 = g.isEdge(test3 , test2);
    qDebug()<<isEd2;
    return a.exec();
}

