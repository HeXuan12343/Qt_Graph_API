#ifndef MININDEXHEAP_H
#define MININDEXHEAP_H
template<class V,class W>
struct MinNode{
    V vertex;
    W cost;
    MinNode(){

    }
    bool operator < (MinNode & M){
        return  cost<M.cost;
    }
    bool operator > (MinNode & M){
        return  cost> M.cost;
    }
    bool operator >= (MinNode & M){
        return  cost>= M.cost;
    }
    bool operator <= (MinNode & M){
        return  cost<= M.cost;
    }

    MinNode& operator =(MinNode& M){

            vertex=M.vertex;
            cost=M.cost;

        return *this;
    }
};

template<class T>
class MinIndexHeap
{
public:
    MinIndexHeap();  
        MinIndexHeap (int sz = 16); //构造函数
        MinIndexHeap (T arr[], int n); //构造函数
        ~MinIndexHeap() { //析构函数
            delete [ ] data;
            delete [] indexlist;
        }
        bool Insert (T& d); //插入
        bool Remove (T& d); //删除
        bool Modify(int i, T x);//数组第i个修改为x
        bool IsEmpty ()  { return currentIndexSize == 0; } //判堆空否
        bool IsFull ()  { return currentIndexSize == maxHeapSize; } //判堆满否
        void MakeEmpty () { currentSize = 0; } //置空堆
        void swap(int i,int j);
    private:
        T *data;//元素数组
        int *indexlist;//索引数组
        int currentSize; //最小堆当前数据元素个数
        int currentIndexSize;//当前索引个数（堆中实际元素数）
        int maxHeapSize; //最小堆最大容量
        void siftDown (int k); //从start到m下滑调整为最小堆
        void siftUp (int start); //从start到0上滑调整为最小堆



};

template <class T>
MinIndexHeap<T>::MinIndexHeap (int sz) {
    maxHeapSize = (16 < sz) ? sz : 16;
    data = new T[maxHeapSize+1]; //创建堆空间
    indexlist=new int[maxHeapSize+1];//创建索引数组
   //因为要从第1开始所以是maxHeapSize+1
    currentSize = 0; //建立当前大小
    currentIndexSize=0;
}

template <class T>
MinIndexHeap<T>::MinIndexHeap (T arr[], int n) {
    maxHeapSize = (16 < n) ? n : 16;
    data = new T[maxHeapSize+1];
    indexlist = new int[maxHeapSize+1];
    for (int i = 0; i < n; i++){
        data[i+1] = arr[i];
        indexlist[i+1]=i+1;
    }
    currentSize = n; //复制堆数组, 建立当前大小
    currentIndexSize=n;
    int currentPos = currentSize/2; //找最初调整位置:最后分支结点
    while (currentPos > 0) { //逐步向上扩大堆
    siftDown (currentPos); //局部自上向下下滑调整
    currentPos--;
    }
}

template <class T>
void MinIndexHeap<T>::siftDown (int k ) {
    while (k*2<=currentIndexSize) {
        int j=2*k;//左子女
//        int lef=indexlist[j];
//        int rig=indexlist[j+1];
        if(j+1<=currentIndexSize && data[indexlist[j+1]]<=data[indexlist[j]])
            j++;
        if(data[indexlist[k]]<=data[indexlist[j]])
            break;
        swap(k,j);
    }
}

template <class T>
bool MinIndexHeap<T>::Insert ( T& x ) {//公共函数: 将x插入到最小堆中
    if ( currentSize == maxHeapSize ) //堆满
       return false;
    data[currentSize+1]=x;
    indexlist[currentIndexSize+1]=currentSize+1;
    siftUp(currentIndexSize+1);
    currentSize++;
    currentIndexSize++;
}

template <class T>
void MinIndexHeap<T>::siftUp (int k) {
    while (k>1 && data[indexlist[k/2]]>data[indexlist[k]]) {
//        int temp=indexlist[k];
//        indexlist[k]=indexlist[k/2];
//        indexlist[k/2]=temp;
        swap(k,k/2);
        k/=2;
    }
}

template <class T>
bool MinIndexHeap<T>::Remove (T& x) {
    if ( !currentSize ) //堆空, 返回false
        return false;
    int index=indexlist[1];
    swap(1,currentIndexSize);
    currentIndexSize--;
    siftDown(1);
    x=data[index];
    return true;
}

template<class T>
bool MinIndexHeap<T>::Modify(int i,  T x)
{
    data[i]=x;
  //要找到data[i]在堆中的位置，找到j使indexlist[j]=i
    for(int j=1;j<=currentSize;j++)
        if(indexlist[j]==i){
            siftUp(j);
            siftDown(j);
            return true;
        }
    return false;
}

template<class T>
void MinIndexHeap<T>::swap(int i, int j)
{
    int temp=indexlist[i];
    indexlist[i]=indexlist[j];
    indexlist[j]=temp;
}

#endif // MININDEXHEAP_H
