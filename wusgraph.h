#ifndef WUSGRPH_H
#define WUSGRPH_H

#include"dblinkedlist.h"
#include"expandablelinkedhashtable.h"
#include"hashmap.h"

/******声明要用到的结构体*******/
template<typename V , typename W>
struct Edge;
template<typename V , typename W>
struct Vertex;
template<typename V , typename W>
struct Neighbors;

/***************************/

template<typename V , typename W>
struct Edge{
    DblNode<V ,Vertex<V , W>> *vp; //指向另一个顶点的指针
    DblNode<V , Edge<V , W>> *frien_p;  //伙伴指针
    W _cost; //权值
    Edge<V , W>(DblNode<V ,Vertex<V , W>> vpoint = 0 , DblNode<W , Edge<V , W>> *frien_point = NULL)
        : vp(vpoint) , frien_p(frien_point){}
    Edge<V , W>(W cost, DblNode<V ,Vertex<V , W>> vpoint = 0 , DblNode<W , Edge<V , W>> *frien_point = NULL)
        : _cost(cost) , vp(vpoint) , frien_p(frien_point){}
};

template<typename V , typename W>
struct Vertex{
    V data; //顶点数据
    int degree;//顶点的度
    DbLinkedList<int , Edge<V , W>> EdgeList;//顶点的边链表
    Vertex<V , W>()
        : data(NULL) , degree(0){}
    Vertex<V , W>(V dat)
        : data(dat) , degree(0){}
    Vertex<V , W> & operator =(const Vertex<V , W> &v)//重载赋值运算符
    {
        this->data = v.data;
        this->degree = v.degree;
        return *this;
    }
    bool operator == (const Vertex<V , W> v)
    {
        if(this->data == v.data)
            return true;
        else
            return false;
    }
};


template<typename V , typename W>
struct Neighbors{
    DbLinkedList<V , Vertex<V , W>> neiborList;//存储邻接点
    DbLinkedList<V , W> costList; //存储对应权值
};


template<typename V , typename W>
class WUSGraph
{
public:
    WUSGraph();//构造函数
    int vertexCount();//返回图中顶点的个数
    int edgeCount();//返回图中边的个数
    V *getVertices();//返回包含所有顶点的数组
    void addVertex(V ver);//添加顶点
    void removeVertex(V ver);//删除顶点
    bool isVertex(V ver);//判断该顶点是否在图中
    int Degree(V ver);//顶点的度
    Neighbors<V , W> getNeighbors(V ver);//返回顶点的所有邻接顶点
    void addEdge(V ver1 , V ver2 , W cost);//添加边
    bool removeEdge(V ver1 , V ver2);//删除边
    bool isEdge(V ver1 , V ver2);//判断边是否在图中
    W getWeight(V ver1 , V ver2);//求某边的权值
private:
    HashMap<V , int> verMap;//顶点散列映射
    HashMap<V , int> edgMap;//边散列映射
    DbLinkedList<int , Vertex<int , W>> verList;//顶点双链表,规定顶点的值为整数
    int vertexNum;//顶点数量
    int edgeNum;//边数量
    int insertOder;//插入的第几个顶点


};

template<typename V, typename W>
WUSGraph<V, W>::WUSGraph()//构造函数，初始化顶点插入次序
{
    insertOder = 1;
}

template<typename V, typename W>
int WUSGraph<V, W>::vertexCount()//返回顶点数
{
    return vertexNum;
}

template<typename V, typename W>
int WUSGraph<V, W>::edgeCount()//返回边数
{
    return edgeNum;
}

template<typename V, typename W>
V *WUSGraph<V, W>::getVertices()//获取包含所有顶点的数组
{
    V *v = new int[vertexNum];
    DblNode<V , Vertex<V , W>> *first = verList.getFirst();
    DblNode<V , Vertex<V , W>> *p = first->rLinV;
    for(int i = 0; i < vertexNum; i++){
        if(p != first){
            v[i] = p->data;
        }
    }
    return v;
}


template<typename V, typename W>
void WUSGraph<V, W>::addVertex(V ver)//插入顶点
{
    if(isVertex(ver))//如果顶点已经在图中，返回
        return;
    std::pair<V , int> pai(ver , insertOder);//创建映射
    verMap.Insert(pai);//将映射对存入map
    Vertex<int , W> v(insertOder);//新建结点
    verList.Append(insertOder , v);//将顶点存入顶点表,insertOder在这里成为关键码,verList存储的是顶点Vertex对象
    insertOder++;//更新顶点的整数值
    vertexNum++;//更新顶点数量
}

template<typename V, typename W>
void WUSGraph<V, W>::removeVertex(V ver)
{
    auto verData = verMap.getValue(ver);//通过映射获取对应整数值
    DblNode<int , Vertex<int , W>> *vNode = verList.Search(verData);
    vNode->lLink->rLink = vNode->rLink;
    vNode->rLink->lLink = vNode->lLink;
    delete vNode;
}

template<typename V, typename W>
bool WUSGraph<V, W>::isVertex(V ver)
{
    if(verMap.getValue(ver) == 0)
        return false;
    else
        return true;
}

template<typename V, typename W>
int WUSGraph<V, W>::Degree(V ver)
{
    auto verData = verMap.getValue(ver);//通过映射获取对应整数值
    DblNode<int , Vertex<int , W>> *vNode = verList.Search(verData);//在顶点双链表中查找
    return vNode->data.degree;//返回顶点的度
}

template<typename V, typename W>
Neighbors<V, W> WUSGraph<V, W>::getNeighbors(V ver)
{
    Neighbors<V, W> neighbor;
    if(!isVertex(ver))
        return NULL;
    auto verData = verMap.getValue(ver);//通过映射获取对应整数值
    DblNode<int , Vertex<int , W>> *vNode = verList.Search(verData);//在顶点双链表中查找
    Vertex<int , W> v = vNode->data;//获取顶点对象
    auto vEdgeList = v.EdgeList;//获取顶点的边链表
    auto first = vEdgeList.getFirst();//获取链表的头节点
    auto p = first->rLink;//滑动指针
    while (p != first) {
        auto vtemp = p->vp;//获取顶点对象
        auto ecost = p->_cost;//获取边权值
        neighbor.neiborList.Append(vtemp);//插入邻接顶点表
        neighbor.costList.Append(ecost);//插入权值
    }
    return neighbor;

}

template<typename V, typename W>
void WUSGraph<V, W>::addEdge(V ver1, V ver2, W cost)
{
    if(isEdge(ver1 , ver2))//如果已经存在该边，返回
        return;
    if(isVertex(ver1)&&isVertex(ver2))//如果两条边都在图中，直接添加边
    {
        auto v1 = verMap.getValue(ver1);
        auto v2 = verMap.getValue(ver2);//获取顶点整数值
        DblNode<int , Vertex<int , W>> *v1Node = verList.Search(ver1);
        DblNode<int , Vertex<int , W>> *v2Node = verList.Search(ver2);//在顶点双链表中查找
        Vertex<int , W> v_1 = v1Node->data;
        Vertex<int , W> v_2 = v1Node->data;//获取顶点对象
        auto v1EdgeList = v_1.EdgeList;
        auto v2EdgeList = v_2.EdgeList;//获取顶点的边链表
        std::pair<V , std::pair<int , int>> ePair(ver1+ver2 , std::pair<int , int>(v1 , v2));//建立边散列映射
        edgMap.Insert(ePair);//放入边哈希映射
        Edge<V , W> *edg1(cost , v_2);//新建ver1半边结点
        Edge<V , W> *edg2(cost , v_1);//新建ver2半边结点
        edg1->frien_p = edg2;
        edg2->frien_p = edg1;//连接伙伴指针
        v1EdgeList.Append(v2 , edg1);
        v2EdgeList.Append(v1 ,edg2);//将边添加到顶点边链表,邻接顶点整数值成为关键码

    }
    else if(isVertex(ver1)&&!isVertex(ver2))//如果ver2不在图中,添加顶点
    {
        addVertex(ver2);
        addEdge(ver1 , ver2);
    }
    else if(!isVertex(ver1)&&isVertex(ver2))//如果ver1不在图中，添加顶点
    {
        addVertex(ver1);
        addEdge(ver1 , ver2);
    }

}

template<typename V, typename W>
bool WUSGraph<V, W>::removeEdge(V ver1, V ver2)
{
    if(!isEdge(ver1 , ver2))//边不在图中,返回
        return false;
    auto v1 = verMap.getValue(ver1);//获取顶点1的整数值
    auto v2 = verMap.getValue(ver2);//获取顶点2的整数值
    DblNode<int , Vertex<int , W>> *vNode = verList.Search(v1);//在双链表中查找
    Vertex<int , W> objVer1;//获取顶点对象
    DbLinkedList<int , Edge<V , W>> edg1_List = objVer1.EdgeList;//获取顶点边链表
    DblNode<int , Edge<V , W>> *eNode = edg1_List.Search(v2);//查找对应边结点
    Edge<V , W> *edge = eNode->data;//获取边对象
    eNode->lLink->rLink = eNode->rLink;
    eNode->rLink->lLink = eNode->lLink;//从链表中摘下
    DblNode<int , Edge<V , W>> *fri_p = edge->frien_p;//获取伙伴指针结点
    fri_p->lLink->rLink = fri_p->rLink;
    fri_p->rLink->lLink = fri_p->lLink;//从链表中摘下
    delete eNode;
    delete fri_p;//删除结点
}

template<typename V, typename W>
bool WUSGraph<V, W>::isEdge(V ver1, V ver2)
{
    if(edgMap.getValue(ver1+ver2) == 0)
        return false;
    else
        return true;;
}

template<typename V, typename W>
W WUSGraph<V, W>::getWeight(V ver1, V ver2)
{
    if(!isEdge(ver1 , ver2))
        return W();
    else
    {
        auto v1 = verMap.getValue(ver1);//获取顶点1的整数值
        auto v2 = verMap.getValue(ver2);//获取顶点2的整数值
        DblNode<int , Vertex<int , W>> *vNode = verList.Search(v1);//在双链表中查找
        Vertex<int , W> objVer1;//获取顶点对象
        DbLinkedList<int , Edge<V , W>> edg1_List = objVer1.EdgeList;//获取顶点边链表
        DblNode<int , Edge<V , W>> *eNode = edg1_List.Search(v2);//查找对应边结点
        Edge<V , W> *edge = eNode->data;//获取边对象
        return edge->_cost;
    }
}


#endif // WUSGRPH_H
