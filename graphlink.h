#ifndef GRAPHLINV_H
#define GRAPHLINV_H

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
    DblNode<V , Vertex<V , W>> *vp; //指向另一个顶点的指针
    DblNode<W , Edge<V , W>> *frien_p;  //伙伴指针
    W _cost; //权值
    Edge<V , W>(DblNode<V , Vertex<V , W>> *vpoint = NULL , DblNode<W , Edge<V , W>> *frien_point = NULL)
        : vp(vpoint) , frien_p(frien_point){}
    Edge<V , W>(W cost, DblNode<V , Vertex<V , W>> *vpoint = NULL , DblNode<W , Edge<V , W>> *frien_point = NULL)
        : _cost(cost) , vp(vpoint) , frien_p(frien_point){}
};

template<typename V , typename W>
struct Vertex{
    V data; //顶点数据
    int degree;//顶点的度
    DbLinkedList<V , Edge<V , W>> EdgeList;//顶点的边链表
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
};

template<typename V , typename W>
struct VertexForHash{
    V key;//插入哈希映射中的关键码
    int data;//顶点整数值
    DblNode<V , Vertex<V , W>> *pForGV;//指向图中顶点的指针
    VertexForHash<V , W>(V Ve , DblNode<V , Vertex<V , W>> *p = NULL)//构造函数
        :key(Ve) , pForGV(p){}
    VertexForHash<V , W>(V Ve , int dat , DblNode<V , Vertex<V , W>> *p = NULL)
        :key(Ve) , data(dat), pForGV(p){}

};

template<typename V , typename W>
struct EdgeForHash{
    V Vey; //插入哈希映射中的关键码
    int v[2]; //连接的顶点对
    DblNode<V , Edge<V , W>> *pForGE;//指向图中边的指针
    EdgeForHash<V , W>(V Ve , DblNode<V , Edge<V , W>> *p = NULL)//构造函数
        :Vey(Ve) , pForGE(p){}
    EdgeForHash<V , W>(V Ve , Vertex<V,W> v1 , Vertex<V ,W> v2 , DblNode<V , Edge<V , W>> *p = NULL)//构造函数
        :Vey(Ve) , pForGE(p)
    {
        v[0] = v1;
        v[1] = v2;
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
    Vertex<V , W> *getVertices();//返回包含所有顶点的数组
    void addVertex(V ver);//添加顶点
    void removeVertex(V ver);//删除顶点
    bool isVertex(V ver);//判断该顶点是否在图中
    int Degree(V ver);//顶点的度
    Neighbors<V , W> getNeighbors(V ver);//返回顶点的所有邻接顶点
    void addEdge(V ver1 , V ver2 , W cost);//添加边
    void removeEdge(V ver1 , V ver2);//删除边
    bool isEdge(V ver1 , V ver2);//判断边是否在图中
    W getWeight(V ver1 , V ver2);//求某边的权值
private:
    HashMap<V , int> verMap;//顶点散列映射
    HashMap<V , int> edgMap;//边散列映射
    DbLinkedList<V , int> verList;//顶点双链表,规定顶点的值为整数
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
Vertex<V, W> *WUSGraph<V, W>::getVertices()//获取包含所有顶点的数组
{
    Vertex<V, W> *v = new Vertex<V, W>[vertexNum];
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
    verList.Append(insertOder);//将整数值存入定点表
    insertOder++;//更新顶点的整数值

}

template<typename V, typename W>
void WUSGraph<V, W>::removeVertex(V ver)
{
    auto verData = verMap.getValue(ver);//通过映射获取对应整数值
    verList.Remove(verData);//从顶点表中删除
    verMap.Remove(ver);//从map中删除映射
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
    DblNode<V , int> *vNode = verList.Search(ver);//在顶点双链表中查找
    return vNode->data.degree;//返回顶点的度
}

template<typename V, typename W>
Neighbors<V, W> WUSGraph<V, W>::getNeighbors(V ver)
{
    Neighbors<V, W> neighbor;
    if(!isVertex(ver))
        return NULL;
    auto verData = verMap.getValue(ver);//通过映射获取对应整数值
    DblNode<V , int> *vNode = verList.Search(ver);//在顶点双链表中查找
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


#endif // GRAPHLINV_H
