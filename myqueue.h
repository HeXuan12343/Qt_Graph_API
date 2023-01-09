#ifndef MYQUEUE_H
#define MYQUEUE_H

template<class T>
class myQueue
{
public:
    myQueue(int size=16);
    bool EnQueue(T x);//进队列
    bool DeQueue(T &x);//出队列
    void MakeEmpty(){front=rear=0;}//队列置空
    bool isEmpty(){return front==rear;}//判队列空
    bool isFull(){return (rear+1)%maxSize==front;}//判队列满
private:
    int front,rear;//队头队尾指针
    T *element;
    int maxSize;
};

template<class T>
myQueue<T>::myQueue(int size)
{
    element=new int[size];
    front=rear=0;
    maxSize=size;
}

template<class T>
bool myQueue<T>::EnQueue(T x)
{
    if(isFull()) return false;
    element[rear]=x;
    rear=(rear+1)%maxSize;
    return true;
}

template<class T>
bool myQueue<T>::DeQueue(T &x)
{
    if(isEmpty()) return false;
    x=element[front];
    front=(front+1)%maxSize;
    return true;
}



#endif // MYQUEUE_H
