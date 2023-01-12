#ifndef MINSPANTREE_H
#define MINSPANTREE_H

#define DefaltSize 100000
#include<QDebug>
#include <iostream>

template <class V , class W>
struct MSTEdgeNode { //树边结点的类定义
    int tail, head; //两顶点位置
    W key; //边上的权值(为结点关键码)
    MSTEdgeNode()
        : tail(-1), head(-1), key(0) {}
    bool operator <= (MSTEdgeNode<V , W>& R)
    {
        return key <= R.key;
    }
    bool operator > (MSTEdgeNode<V , W>& R)
    {
        return key < R.key;
    }
};

template <class V, class W>
class MinSpanTree { //最小生成树的类定义
protected:
    int *edgevalue; //边值数组
    int currentSize;
public:
    MinSpanTree (int sz = DefaltSize);
    void Insert (const MSTEdgeNode<V , W>& item);
    void PrintTree();
};

template<class V, class W>
MinSpanTree<V, W>::MinSpanTree(int sz)
{
    edgevalue = new int[sz];
    for(int i=0;i<sz;i++){
        edgevalue[i]=-1;
    }
    currentSize = sz;
}

template<class V, class W>
void MinSpanTree<V, W>::Insert(const MSTEdgeNode<V, W> &item)
{
    edgevalue[item.tail] = item.head;
}

template<class V, class W>
void MinSpanTree<V,W>::PrintTree()
{
    for(int i = 1; i < currentSize; i++){
        std::cout<<"“"<<edgevalue[i]<<"”"<<"->";
    }
}

#endif // MINSPANTREE_H
