#ifndef DBLINKEDLIST_H
#define DBLINKEDLIST_H
#include<iostream>
using namespace std;

template<typename  K , typename E>
struct DblNode{
    E data;
    K key;

    DblNode<K , E>*lLink , *rLink , *hLink;
    DblNode<K , E>(DblNode<K , E>* left = NULL , DblNode<K , E>* right = NULL , DblNode<K , E>* hlink = NULL)
        : lLink(left) , rLink(right) , hLink(hlink){}
    DblNode<K , E>(E val, DblNode<K , E>* left = NULL , DblNode<K , E>* right = NULL , DblNode<K , E>* hlink = NULL)
        :data(val) , lLink(left) , rLink(right), hLink(hlink){}
    DblNode<K , E>(K key, DblNode<K , E>* left = NULL , DblNode<K , E>* right = NULL , DblNode<K , E>* hlink = NULL)
        :key(key) , lLink(left) , rLink(right), hLink(hlink){}
    DblNode<K , E>(K key, E val , DblNode<K , E>* left = NULL , DblNode<K , E>* right = NULL , DblNode<K , E>* hlink = NULL)
        :key(key) , data(val) ,lLink(left) , rLink(right), hLink(hlink){}
};

template<typename  K , typename E>
class DbLinkedList
{
public:
    DbLinkedList();
    DblNode<K , E> * Search(K key);
    DblNode<K,E> *getFirst(){return first;}
    bool Insert(K val ,int i, int d = 1);
    void Append(K key , E val);
    void Append(K key);
    void Append(E val);
    bool Remove(int i , E &val, int d = 1);
    bool Remove(K key , E &val);
    bool Remove(K key);
    void Clear();
    size_t Size();


private:
    DblNode<K , E> *first;
    DblNode<K , E> * Locate(int i , int d){
        //按照d的指示方向进行查找,d = 0 为前驱方向，否则为后继方向
        if(first->rLink == first || i == 0) return first; //链表为空
        DblNode<K , E>* p;
        p = (d == 0) ? first->lLink : first->rLink;
        for(int j = 0; p != first && j < i; j++){
            p = (d == 0) ? first->lLink : first->rLink;
        }
        return p;
    }
};

template<typename  K , typename E>
DbLinkedList<K , E>::DbLinkedList()
{
    first = new DblNode<K , E>;
    first->lLink = first->rLink = first;
}

template<typename  K , typename E>
DblNode<K , E> *DbLinkedList<K , E>::Search(K key)//根据关键码查找
{
    DblNode<K , E> *p = first->rLink;
    if(p == first)
        return NULL;
    while (p->key != key && p != first) {
        p = p->rLink;
    }
    return p;
}

template<typename  K , typename E>
bool DbLinkedList<K , E>::Insert(K val, int i , int d )
{
    //插入算法，默认为后继搜索插入
    DblNode<K , E> *p = Locate(i , d);
    if(p == first && i > 0) return false; //i不合理，插入失败
    DblNode<K , E> *s = new DblNode<K , E>(val);
    if(d == 0){//前驱方向插入
        s->lLink = p->lLink;
        p->lLink = s;
        s->rLink = p;
        s->lLink->rLink = s;
    }
    else {//后继方向插入
        s->rLink = p->rLink;
        p->rLink = s;
        s->lLink = p;
        s->rLink->lLink = s;
    }
    return true;
}

 template<typename K, typename E>
void DbLinkedList<K, E>::Append(K key, E val)
{
    DblNode<K , E> *s = new DblNode<K , E>(val);
    s->key = key;
    DblNode<K , E> *p = first->rLink;
    if(p == first){//表空
        s->rLink = p->rLink;
        p->rLink = s;
        s->lLink = p;
        s->rLink->lLink = s;
    }
    else {
        while (p->rLink != first) {
            p = p->rLink;
        }
        s->rLink = p->rLink;
        p->rLink = s;
        s->lLink = p;
        s->rLink->lLink = s;
    }

}

template<typename K, typename E>
void DbLinkedList<K, E>::Append(K key)
{
    DblNode<K , E> *s = new DblNode<K , E>(key);
    DblNode<K , E> *p = first->rLink;
    if(p == first){//表空
        s->rLink = p->rLink;
        p->rLink = s;
        s->lLink = p;
        s->rLink->lLink = s;
    }
    else {
        while (p->rLink != first) {
            p = p->rLink;
        }
        s->rLink = p->rLink;
        p->rLink = s;
        s->lLink = p;
        s->rLink->lLink = s;
    }
}

template<typename K, typename E>
void DbLinkedList<K, E>::Append(E val)
{
    DblNode<K , E> *s = new DblNode<K , E>(val);
    DblNode<K , E> *p = first->rLink;
    if(p == first){//表空
        s->rLink = p->rLink;
        p->rLink = s;
        s->lLink = p;
        s->rLink->lLink = s;
    }
    else {
        while (p->rLink != first) {
            p = p->rLink;
        }
        s->rLink = p->rLink;
        p->rLink = s;
        s->lLink = p;
        s->rLink->lLink = s;
    }
}

template<typename  K , typename E>
bool DbLinkedList<K , E>::Remove(int i , E &val , int d)//根据索引查找
{
    //默认后继方向搜索
    DblNode<K , E>* del = Locate(i , d);
    if(del == first && i > 0) return false; //i不合理，删除失败
    del->rLink->lLink = del->lLink;
    del->lLink->rLink = del->rLink;
    val = del->data;
    delete del;
    return true;
}

template<typename K, typename E>
bool DbLinkedList<K, E>::Remove(K key, E &val)//根据关键码查找，通过E返回
{
    DblNode<K , E>* del = first->rLink;
    while (del != first && del->key != key) {
        del = del->rLink;
    }
    if(del == first) return false; //未找到制定结点
    else{
        del->rLink->lLink = del->lLink;
        del->lLink->rLink = del->rLink;
        val = del->data;
        delete del;
        return true;
    }
}

template<typename K, typename E>
bool DbLinkedList<K, E>::Remove(K key){
    DblNode<K , E>* del = first->rLink;
    while (del != first && del->key != key) {
        del = del->rLink;
    }
    if(del == first) return false; //未找到指定结点
    else{
        del->rLink->lLink = del->lLink;
        del->lLink->rLink = del->rLink;
        delete del;
        return true;
    }
}

template<typename  K , typename E>
void DbLinkedList<K , E>::Clear()
{
    DblNode<K , E> *del = first->rLink;
    auto p = del;
    while (p != first) {
        first->rLink = del->rLink;
        del->rLink->lLink = first;
        p = del->rLink;
        delete del;
    }
}

template<typename K, typename E>
size_t DbLinkedList<K, E>::Size()
{
    DblNode<K , E>* p = first->rLink;
    size_t count = 0;
    while (p != first) {
        count++;
        p = p->rLink;
    }
    return count;
}


#endif // DBLINKEDLIST_H
