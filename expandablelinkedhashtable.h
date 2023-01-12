#ifndef EXPANDABLELINKEDHASHTABLE_H
#define EXPANDABLELINKEDHASHTABLE_H
#include<iostream>
#include"dblinkedlist.h"
#include"expandablearraylist.h"
using namespace std;

template <class K,class E>
class ExpandableLinkedHashTable
{
public:
    ExpandableLinkedHashTable(int initialSize=16, double maxLoadFactor=0.7){
        TableSize=initialSize;
        HashTable.resizeList(initialSize);
        for(int i = 0; i < initialSize; i++){//初始化数组元素为空指针
            HashTable[i] = NULL;
        }
        LoadFactor=maxLoadFactor;
    }
    ~ExpandableLinkedHashTable(){
        HashTable.Clear();
    }

    DblNode<K,E> *findPos( K& key,int &bucket) ;//返回关键码key对应的结点，通过bucket返回桶号
    bool Search(  K& key) ;//查找
    bool Insert(  K& key,  E&e);
    int Remove(  K& key);
    void resizeTable();//扩容
    void Clear();//清空，保留大小为0的散列表
    int getCapacity() {return TableSize;}//获取容量
    int getSize() {return getdivisor(TableSize);}//获取桶数
    int getBucketcount();//获取非空桶数量
    int getBucket(  K& k) {//返回k对应桶号
        return hashcode(k);
    }

    int getBucketSize(int i) {//获取第i个桶的元素个数
        return HashTable[i]->Size();
    }
    bool isPrim(int n) ;//判断质数
    int getdivisor(int tablesize) ;//获取最近的质数


private:
    ExpandableArrayList<DbLinkedList<K,E>*> HashTable;//可扩容数组，用作散列表，数组元素为指向双向链表的指针
    double LoadFactor;//负载系数
    int TableSize;//表长
    int BucketSize;//桶数
    int hashcode(  K key) ;//哈希函数
};

template <class K, class E>
DblNode<K,E>* ExpandableLinkedHashTable<K,E>::findPos( K& key,int &bucket) {
    if(!Search(key)){//如果不存在
        bucket=-1;
        return NULL;
    }
    bucket=getBucket(key);
    DblNode<K,E> *p=HashTable[bucket]->Search(key);//交给双向链表搜索
    return p;
}



template <class K, class E>
bool ExpandableLinkedHashTable<K,E>::Search(  K& key) {
    if(TableSize==0) return  false;//如果是以clear的表，则返回
    int bucket=getBucket(key);//获取桶号
    if(HashTable[bucket]){//如果桶不空
        if(HashTable[bucket]->Search(key))//如果桶中的双向链表存在该元素
            return true;
        return false;
    }
    return false;
}

template <class K, class E>
bool ExpandableLinkedHashTable<K,E>::Insert(  K& key,  E& e){
    int bucket;
    if(findPos(key,bucket)){//如果元素存在 则替换
        HashTable[bucket]->Remove(key);//先删除该元素
        HashTable[bucket]->Append(key,e);//再插入元素
        return true;
    }
    bucket = getBucket(key);
    //若不存在
    if(HashTable[bucket]){//如果不为空桶
        HashTable[bucket]->Append(key,e);
        return true;
    }
    else{//对应的桶空
        HashTable[bucket]=new DbLinkedList<K,E>();
        HashTable[bucket]->Append(key,e);
        BucketSize++;//桶数+1
        if(double(getBucketcount()/getCapacity())>LoadFactor)//如果负载超出限制，则扩容
            resizeTable();
        return true;
    }

    return false;
}

template <class K, class E>
int ExpandableLinkedHashTable<K,E>::Remove(  K& key){
    if(TableSize==0) return  0;
    int bucket=getBucket(key);
    if(HashTable[bucket]->Remove(key)){//如果存在该关键码的结点
        return 1;
    }
    return 0;
}

template <class K, class E>
void ExpandableLinkedHashTable<K,E>::resizeTable(){
    int i=getdivisor(this->TableSize);//保存桶数
    this->TableSize=getdivisor(TableSize*2);//容留扩大
    ExpandableArrayList<DbLinkedList<K,E>*> newHashTable(TableSize);//创造新数组以暂存再散列的元素
//    HashTable.resizeList(TableSize);
    for(int j=0;j<i;j++){//再散列
        if(HashTable[j]){//如果该桶不空
          //因为一个桶的双向链表中所有元素关键码的哈希值都一样，这里只取一个即可
            DblNode<K,E> *p=HashTable[j]->getFirst()->rLink;
            if(p!=HashTable[j]->getFirst()){//如果桶中有元素
                int bucket=getBucket(p->key);
                newHashTable[bucket]=HashTable[j];
            }
        }
    }
    HashTable.resizeList(TableSize);//对原散列表进行扩容并将元素删除
    for(int j=0;j<TableSize;j++){//将暂存数组的元素移动过去
        HashTable[j]=newHashTable[j];
    }
}

template<class K, class E>
void ExpandableLinkedHashTable<K,E>::Clear(){
    for(int i=0;i<getSize();i++){
        if(HashTable[i]){
            HashTable[i]->Clear();
            HashTable[i]=NULL;
        }
    }
    HashTable.Clear();
    TableSize=0;
}

template<class K, class E>
int ExpandableLinkedHashTable<K,E>::getBucketcount()
{
    int count=0;
    for(int i=0;i<getSize();i++)
        if(HashTable[i])
            count++;
    return  count;
}

template<class K, class E>
bool ExpandableLinkedHashTable<K,E>::isPrim(int n) {
    if(n <= 1)
            return false;
        else
        {
            for (int i=2;i<n;i++){
                 if (n%i==0){
                    return false;
                 }
            }
            return true;
        }
}

template<class K, class E>
int ExpandableLinkedHashTable<K,E>::getdivisor(int tablesize) {
    if(isPrim(tablesize))
            return tablesize;
        while (!isPrim(tablesize)) {
            tablesize--;
        }
        return tablesize;
}


template<class K, class E>
int ExpandableLinkedHashTable<K,E>::hashcode(K key) {
//    int h=0;
//    for(int i=0;i<key.size();i++)
//        h=((unsigned char)key[0]-129)*190 +
//                ((unsigned char)key[1]-64) - (unsigned char)key[1]/128;
    int t = getdivisor(TableSize);
    return key%t;
}

#endif // EXPANDABLELINKEDHASHTABLE_H
