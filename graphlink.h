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
    DbLinkedList<W , Edge<V , W>> EdgeList;//顶点的边链表
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
    void addVertex(Vertex<V , W> ver);//添加顶点
    void removeVertex(Vertex<V , W> ver);//删除顶点
    bool isVertex(Vertex<V , W> ver);//判断该顶点是否在图中
    int Degree(Vertex<V , W> ver);//顶点的度
    Neighbors<V , W> getNeighbors(Vertex<V , W> ver);//返回顶点的所有邻接顶点
    void addEdge(Vertex<V , W> ver1 , Vertex<V , W> ver2 , W cost);//添加边
    void removeEdge(Vertex<V , W> ver1 , Vertex<V , W> ver2);//删除边
    bool isEdge(Vertex<V , W> ver1 , Vertex<V , W> ver2);//判断边是否在图中
    W getWeight(Vertex<V , W> ver1 , Vertex<V , W> ver2);//求某边的权值
private:
    HashMap<V , VertexForHash<V , W>> verMap;//顶点散列映射
    HashMap<V , EdgeForHash<V , W>> edgMap;//边散列映射
    DbLinkedList<V , int> verList;//顶点双链表,规定顶点的值为整数
    int vertexNum;//顶点数量
    int edgeNum;//边数量
    int insertOder;//插入的第几个顶点
    DblNode<V , W> isVertex(V Vey);

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
void WUSGraph<V, W>::addVertex(Vertex<V, W> ver)//插入顶点
{
    if(isVertex(ver))//如果顶点已经在图中，返回
        return;
    VertexForHash<V , W> vForHash(ver.data , insertOder);//创建要存储到哈希表中的顶点对象
    Vertex<int, W> vForList(insertOder);//转换成整数顶点存入顶点链表
    verList.Append(vForList);

}

#endif // GRAPHLINV_H
