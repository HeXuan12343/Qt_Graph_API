#include "widget.h"

#include <QApplication>

#include<QDebug>

#include <iostream>


using namespace std;


#include <QTextStream>

#include <dblinkedlist.h>
#include <expandablearraylist.h>
#include "hashmap.h"



int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Widget w;
    w.show();

//    DbLinkedList<int , int> l;
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

    return a.exec();
}

