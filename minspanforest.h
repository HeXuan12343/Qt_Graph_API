#ifndef MINSPANFOREST_H
#define MINSPANFOREST_H

#define DefaltSize 100000

#include"minspantree.h"
template<class V , class W>
struct MinSpanForestNode{
    int tail , head;//两个顶点位置
    W cost;
    MinSpanForestNode<V , W>()
        :tail(-1) , head(-1) , cost(0)
    {

    }
    bool operator <= (MinSpanForestNode<V , W>& R)
    {
        return cost <= R.cost;
    }
    bool operator > (MinSpanForestNode<V , W>& R)
    {
        return cost < R.cost;
    }
    bool operator == (MinSpanForestNode<V , W>& R)
    {
        return ((tail==R.tail&&head==R.tail)||(tail==R.head&&head==R.tail))&&cost==R.cost;
    }
    MinSpanForestNode& operator = (MinSpanForestNode<V , W>& R)
    {
        if(*this!=R)
        {
            tail=R.tail;
            head=R.head;
            cost=R.cost;
        }
        return *this;
    }
};


template<class V , class W>
class MinSpanForest{
public:
    MinSpanForest(int size = DefaltSize);
    void Insert( MinSpanForestNode<V , W> &item);
private:
    int *edgeList;
};

template<class V, class W>
MinSpanForest<V, W>::MinSpanForest(int size)
{
    edgeList = new int[size];
}

template<class V, class W>
void MinSpanForest<V, W>::Insert( MinSpanForestNode<V, W> &item)
{
    edgeList[item.tail] = item.head;
}


#endif // MINSPANFOREST_H
