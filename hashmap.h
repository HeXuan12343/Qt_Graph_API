#ifndef HASHMAP_H
#define HASHMAP_H
#include<iostream>
#include"expandablelinkedhashtable.h"
#include<set>
using namespace std;

template<class K,class V>
class HashMap
{
public:
    HashMap(int initialSize=16,double MaxLoadFactor=0.7){
        map=new ExpandableLinkedHashTable<K,pair<K,V>>(initialSize,MaxLoadFactor);
    };
    ~HashMap();

    V getValue(  K& key);
    set<K> keySet();
    bool containsKey(  K& key);
    void Insert(pair<K,V>  k_v);
    V Remove(  K &key);
    V Remove(  K& key,  V val);
    void Clear();
    int getSize();
    void resizeTable();

private:
    ExpandableLinkedHashTable<K,pair<K,V>> *map;
    set<K> hashset;
};

template<class K, class V>
HashMap<K, V>::~HashMap()
{
    Clear();
    delete map;
}

template<class K,class V>
V HashMap<K,V>::getValue(  K& key){
    int bucket;
    if(map->findPos(key,bucket)){
        return map->findPos(key,bucket)->data.second;
    }
    else
        return V();
}

template<class K,class V>
set<K> HashMap<K,V>::keySet(){
    return hashset;
}

template<class K,class V>
bool HashMap<K,V>::containsKey(  K& key){
    int bucket;
    if(map->findPos(key,bucket)){
        return true;
    }
    else
        return false;
}

template<class K,class V>
void HashMap<K,V>::Insert(pair<K,V>  k_v){
    K key=k_v.first;
    map->Insert(key,k_v);
    hashset.insert(key);
}

template<class K,class V>
V HashMap<K,V>::Remove(  K& key){
    int bucket;
    if(map->findPos(key,bucket)){
        V val=getValue(key);
        map->Remove(key);
        hashset.erase(key);
        return  val;
    }
    return V();
}

template<class K,class V>
V  HashMap<K,V>::Remove(  K& key,  V val){
    int bucket;
    pair<K,V> p=map->findPos(key,bucket)->data;
    if(p.second==val){
        map->Remove(key);
        hashset.erase(key);
        return val;
    }

    return V();
}

template<class K,class V>
void HashMap<K,V>::Clear(){
    map->Clear();
}

template<class K,class V>
int HashMap<K,V>::getSize(){
    int sum=0;
    for(int i=0;i<map->getSize();i++){
       sum+= map->getBucketSize(i);
    }
    return 0;
}

template<class K,class V>
void HashMap<K,V>::resizeTable(){
    map->resizeTable();
}

#endif // HASHMAP_H
