#ifndef MINSPANFOREST_H
#define MINSPANFOREST_H

#define DefaltSize 100000

#include <QDebug>

#include"minspantree.h"
template<class V , class W>
struct MinSpanForestNode{
    int tail , head;//两个顶点位置
    W key;
    MinSpanForestNode<V , W>()
        :tail(-1) , head(-1) , key(0)
    {

    }

    bool operator <= (const MinSpanForestNode<V , W>& R)
    {
        return key <= R.key;
    }
    bool operator > (const MinSpanForestNode<V , W>& R)
    {
        return key > R.key;
    }
//    bool operator < (const MinSpanForestNode<V , W>& R)
//    {
//        return key < R.key;
//    }
//    bool operator >= (const MinSpanForestNode<V , W>& R)
//    {
//        return key >= R.key;
//    }
//    bool operator == (const MinSpanForestNode<V , W>& R)
//    {
//        return ((tail==R.tail&&head==R.tail)||(tail==R.head&&head==R.tail))&&key==R.key;
//    }
    MinSpanForestNode& operator = (MinSpanForestNode<V , W>& R)
    {
        tail=R.tail;
        head=R.head;
        key=R.key;
        return *this;
    }
};


template<class V , class W>
class MinSpanForest{
public:
    MinSpanForest(int size = DefaltSize);
    void Insert( MinSpanForestNode<V , W> item);
    void PrintTree();
private:
    int *edgeList;
    int currentSize;
};

template<class V, class W>
MinSpanForest<V, W>::MinSpanForest(int size)
{
    edgeList = new int[size];
    currentSize = size;
}

template<class V, class W>
void MinSpanForest<V, W>::Insert( MinSpanForestNode<V, W> item)
{
    edgeList[item.tail] = item.head;
}

template<class V, class W>
void MinSpanForest<V, W>::PrintTree()
{
    for(int i = 0; i < currentSize; i++){
        qDebug()<<edgeList[i];
    }
}



#endif // MINSPANFOREST_H
