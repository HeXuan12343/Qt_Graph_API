#ifndef MINSPANTREE_H
#define MINSPANTREE_H

#define DefaltSize 100000

template <class V , class W>
struct MSTEdgeNode { //树边结点的类定义
    V tail, head; //两顶点位置
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
    MSTEdgeNode<V, W> *edgevalue; //边值数组
    int maxSize, n; //最大元素个数和当前个数
public:
    MinSpanTree (int sz = DefaltSize);
    bool Insert (MSTEdgeNode<V , W>& item);
};

template<class V, class W>
MinSpanTree<V, W>::MinSpanTree(int sz)
    :maxSize (sz), n (0)
{
    edgevalue = new MSTEdgeNode<V, W>[sz];
}

template<class V, class W>
bool MinSpanTree<V, W>::Insert(MSTEdgeNode<V, W> &item)
{
    edgevalue[n++] = item;
}

#endif // MINSPANTREE_H
