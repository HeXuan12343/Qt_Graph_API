#ifndef WQUPCUFSET_H
#define WQUPCUFSET_H


class WQUPCUFset
{
public:
    WQUPCUFset(int sz=10);
    ~WQUPCUFset(){delete [] parent;}
    void Union(int Root1,int Root2);//合并
    int Find(int i);//查找根

private:
    int *parent;//父指针数组
    int size;//元素数目
};

WQUPCUFset::WQUPCUFset(int sz)
{
    //构造函数：sz 是集合元素个数，双亲数组的范围
    //为parent[0]～parent[size-1]。
    size = sz; //集合元素个数
    parent = new int[size]; //创建双亲数组
    for (int i = 0; i < size; i++)
        parent[i] = -1; //每个自成单元素集合
}

void WQUPCUFset::Union(int Root1, int Root2)
{
    //按Union的加权规则改进的算法
    int r1=Find(Root1),r2=Find(Root2),temp;
    if(r1!=r2)
    {
        temp = parent[r1] + parent[r2];
        if (parent[r2] < parent[r1]) {//r2中结点数多
            parent[r1] = r2; parent[r2] = temp; //r1指向r2
        }
        else {//r1中结点数多
            parent[r2] = r1; parent[r1] = temp; //r2指向r1
        }
    }
}

int WQUPCUFset::Find(int i){
    //使用折叠规则的搜索算法
    if(parent[i]<0)
        return i;
    int j=i;
    while (parent[j]>0) {
        j=parent[j];
    }//让 j 循双亲指针走到根
    while (parent[i] != j) { //换 parent[i] 到 j
         int temp = parent[i];
         parent[i] = j;
         i = temp;
    }
    return j;
}

#endif // WQUPCUFSET_H

