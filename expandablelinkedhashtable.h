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
        for(int i = 0; i < initialSize; i++){
            HashTable[i] = NULL;
        }
        LoadFactor=maxLoadFactor;
    }
    ~ExpandableLinkedHashTable(){
        HashTable.Clear();
    }

    DblNode<K,E> *findPos( K& key,int &bucket) ;
    bool Search(  K& key) ;
    bool Insert(  K& key,  E&e);
    int Remove(  K& key);
    void resizeTable();
    void Clear();
    int getCapacity() {return TableSize;}//获取容量
    int getSize() {return getdivisor(TableSize);}//获取桶数
    int getBucketcount();//获取非空桶数量
    int getBucket(  K& k) {//返回k对应桶号
        return hashcode(k);
    }

    int getBucketSize(int i) {
        return HashTable[i]->Size();
    }
    bool isPrim(int n) ;//判断质数
    int getdivisor(int tablesize) ;//获取最近的质数


private:
    ExpandableArrayList<DbLinkedList<K,E>*> HashTable;
    double LoadFactor;//负载系数
    int TableSize;
    int BucketSize;//桶数
    int hashcode(  K key) ;//哈希函数
};

template <class K, class E>
DblNode<K,E>* ExpandableLinkedHashTable<K,E>::findPos( K& key,int &bucket) {
    if(!Search(key)){
        bucket=-1;
        return NULL;
    }
    bucket=getBucket(key);
    DblNode<K,E> *p=HashTable[bucket]->Search(key);
    if(!p) bucket=-1;
    return p;
}



template <class K, class E>
bool ExpandableLinkedHashTable<K,E>::Search(  K& key) {
    if(TableSize==0) return  false;
    int bucket=getBucket(key);
    if(HashTable[bucket])
        return true;
    return false;
}

template <class K, class E>
bool ExpandableLinkedHashTable<K,E>::Insert(  K& key,  E& e){
    int bucket;
    if(findPos(key,bucket)){//如果元素存在 则替换
        HashTable[bucket]->Remove(key);
        HashTable[bucket]->Append(key,e);
        return true;
    }
    bucket = getBucket(key);
    //若不存在
    if(HashTable[bucket]){//如果不为空桶
        HashTable[bucket]->Append(key,e);
        return true;
    }
    else{
        HashTable[bucket]=new DbLinkedList<K,E>();
        HashTable[bucket]->Append(key,e);
        BucketSize++;
        if(double(getBucketcount()/getCapacity())>LoadFactor)
            resizeTable();
        return true;
    }

    return false;
}

template <class K, class E>
int ExpandableLinkedHashTable<K,E>::Remove(  K& key){
    if(TableSize==0) return  0;
    int bucket=getBucket(key);
    if(HashTable[bucket]->Remove(key)){
        return 1;
    }
    return 0;
}

template <class K, class E>
void ExpandableLinkedHashTable<K,E>::resizeTable(){
    int i=getdivisor(this->TableSize);
    this->TableSize=getdivisor(TableSize*2);
    ExpandableArrayList<DbLinkedList<K,E>*> newHashTable(TableSize);
//    HashTable.resizeList(TableSize);
    for(int j=0;j<i;j++){
        if(HashTable[j]){//如果该桶不空
            DblNode<K,E> *p=HashTable[j]->getFirst()->rLink;
                int bucket=getBucket(p->key);

                newHashTable[bucket]=HashTable[j];
        }
    }
    HashTable.resizeList(TableSize);
    for(int j=0;j<TableSize;j++){
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
    int h=0;
    for(int i=0;i<key.size();i++)
        h=((unsigned char)key[0]-129)*190 +
                ((unsigned char)key[1]-64) - (unsigned char)key[1]/128;
    int t = getdivisor(TableSize);
    return h%t;
}

#endif // EXPANDABLELINKEDHASHTABLE_H
