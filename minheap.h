#ifndef MINHEAP_H
#define MINHEAP_H

template<class T>
class MinHeap
{
public:

    MinHeap (int sz = 16); //构造函数
    MinHeap (T arr[], int n); //构造函数
    ~MinHeap() { delete [ ] heap; } //析构函数
    bool Insert (T& d); //插入
    bool Remove (T& d); //删除
    bool IsEmpty ()  { return currentSize == 0; } //判堆空否
    bool IsFull ()  { return currentSize == maxHeapSize; } //判堆满否
    void MakeEmpty () { currentSize = 0; } //置空堆
private:
    T *heap;//最小堆元素存储数组
    int currentSize; //最小堆当前元素个数
    int maxHeapSize; //最小堆最大容量
    void siftDown (int start, int m); //从start到m下滑调整为最小堆
    void siftUp (int start); //从start到0上滑调整为最小堆
};

template <class T>
MinHeap<T>::MinHeap (int sz) {
    maxHeapSize = (16 < sz) ? sz : 16;
    heap = new T[maxHeapSize]; //创建堆空间
    currentSize = 0; //建立当前大小
}

template <class T>
MinHeap<T>::MinHeap (T arr[], int n) {
    maxHeapSize = (16 < n) ? n : 16;
    heap = new T[maxHeapSize];

    for (int i = 0; i < n; i++) heap[i] = arr[i];
    currentSize = n; //复制堆数组, 建立当前大小
    int currentPos = (currentSize-2)/2; //找最初调整位置:最后分支结点
    while (currentPos >= 0) { //逐步向上扩大堆
    siftDown (currentPos, currentSize-1); //局部自上向下下滑调整
    currentPos--;
    }
}

template <class T>
void MinHeap<T>::siftDown (int start, int m ) {
//私有函数: 从结点start开始到m为止, 自上向下比较,
//如果子女的值小于父结点的值, 则关键码小的上浮,
//继续向下层比较, 将一个集合局部调整为最小堆。
    int i = start, j = 2*i+1; //j是i的左子女位置
    T temp = heap[i];
    while (j <= m){ //检查是否到最后位置
        if ( j < m && heap[j] > heap[j+1] ) j++; //让j指向两子女中的小者
        if ( temp <= heap[j] ) break; //小则不做调整
        else {
          heap[i] = heap[j];
          i = j;
          j = 2*j+1;
        } //否则小者上移, i, j下降
   }
   heap[i] = temp; //回放temp中暂存的元素
}

template <class T>
bool MinHeap<T>::Insert ( T& x ) {//公共函数: 将x插入到最小堆中
    if ( currentSize == maxHeapSize ) //堆满
       return false;
    heap[currentSize] = x; //插入
    siftUp (currentSize); //向上调整
    currentSize++; //堆计数加1
    return true;
}

template <class T>
void MinHeap<T>::siftUp (int start) {
//私有函数: 从结点start开始到结点0为止, 自下向上
//比较, 如果子女的值小于父结点的值, 则相互交换,
//这样将集合重新调整为最小堆。关键码比较符<=在T中定义
    int j = start, i = (j-1)/2; T temp = heap[j];
    while (j > 0) { //沿父结点路径向上直达根
        if (heap[i] <= temp) break; //父结点值小, 不调整
        else { //父结点结点值大, 调整
            heap[j] = heap[i];
            j = i;
            i = (i-1)/2;
        }
    }
    heap[j] = temp; //回送
}

template <class T>
bool MinHeap<T>::Remove (T& x) {
    if ( !currentSize ) //堆空, 返回false
        return false;
    x = heap[0];
    heap[0] = heap[currentSize-1];
    currentSize--;
    siftDown(0, currentSize-1); //自上向下调整为堆
    return true;
}


#endif // MINHEAP_H
