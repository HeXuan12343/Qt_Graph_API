#ifndef MINSPANTREE_H
#define MINSPANTREE_H

#define DefaltSize 100000

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
public:
    MinSpanTree (int sz = DefaltSize);
    void Insert (const MSTEdgeNode<V , W>& item);
};

template<class V, class W>
MinSpanTree<V, W>::MinSpanTree(int sz)
{
    edgevalue = new int[sz];
}

template<class V, class W>
void MinSpanTree<V, W>::Insert(const MSTEdgeNode<V, W> &item)
{
    edgevalue[item.tail] = item.head;
}

#endif // MINSPANTREE_H
