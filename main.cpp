#include "widget.h"

#include <QApplication>

#include<QDebug>
#include <QFileDialog>
#include <QString>
#include <iostream>
#include <windows.h>
#include <process.h>
#include <conio.h>

using namespace std;


#include <QTextStream>

#include <dblinkedlist.h>
#include <expandablearraylist.h>
#include "hashmap.h"
#include "wusgraph.h"
#include "wusgraphclient.h"
#include "minspanforest.h"
#include "minspantree.h"
#include "routeplanningsystem.h"

void PrintCity(int v)
{
    cout<<v<<",";
}

void showMenu()
{
    cout<<"****************欢迎使用城市路径规划系统！*********************"<<endl;
    cout<<"**              ========================                     **"<<endl;
    cout<<"**              ||        菜单         ||                    **"<<endl;
    cout<<"**              ||      显示信息1      ||                    **"<<endl;
    cout<<"**              ||   导入交通信息2     ||                    **"<<endl;
    cout<<"**              ||      规划计算3      ||                    **"<<endl;
    cout<<"**              ||        查询4        ||                    **"<<endl;
    cout<<"请输入菜单选项：";
}

void showInfo(RoutePlanningSystem<int , int> &contralSysteam)
{
    contralSysteam.ShowSysteamInfo();
    cout<<"按任意键返回主菜单。。。。。";
    getch();
    cout<<"正在返回,请稍候。。。。。。";
    Sleep(1000);
}

void readFaile(RoutePlanningSystem<int , int> &contralSysteam)
{
    QString failePath = QFileDialog::getOpenFileName();
    contralSysteam.ReadFileAndInit(failePath);
    cout<<"按任意键返回主菜单。。。。。";
    getch();
    cout<<"正在返回,请稍候。。。。。。";
    Sleep(1000);
}

void calculate(RoutePlanningSystem<int , int> &contralSysteam)
{
    cout<<"**              ===========================                     **"<<endl;
    cout<<"**              ||  计算图的稀疏程度1       ||                  **"<<endl;
    cout<<"**              ||  地图的连通分量个数2     ||                  **"<<endl;
    cout<<"**              ||       输出环路3          ||                  **"<<endl;
    cout<<"**              ||求相邻的城市数最多的城市4 ||                  **"<<endl;
    cout<<"**              ||        Dijstral 5        ||                  **"<<endl;
    cout<<"**              ||        最小生成树 6      ||                  **"<<endl;
    cout<<"**              ||        Prim 7            ||                  **"<<endl;
    cout<<"**              ||        最长路径 8        ||                  **"<<endl;
    cout<<"请输入菜单选项：";
    int op = 0;
    int co = 1;
    while (co) {
        cout<<"请输入菜单选项：";
        cin>>op;
        switch (op) {
        case 1:
            cout<<contralSysteam.Sparseness();
            break;
        case 2:
            cout<<contralSysteam.ConnectedComponentCount();
            break;
        case 3:
            cout<<"环路：";
            break;
        case 4:
            cout<<contralSysteam.maxNeiborCityCount();
            break;
        case 5:
            cout<<"请输入起始城市名称："<<endl;
            int name1;
            cin>>name1;
            cout<<"请输入终点城市名称："<<endl;
            int name2;
            cin>>name2;
            contralSysteam.showMinDistance(name1 , name2);
            break;
        case 6:
            cout<<"请输入起始城市名称："<<endl;
            cin>>name1;
            contralSysteam.showKruskalForest(name1);
            cout<<"最小生成树"<<endl;
            break;
        case 7:
            cout<<"Prim请输入起始城市名称："<<endl;
            cin>>name1;
            contralSysteam.showPrimForest(name1);
        case 8:
            cout<<"最长路径";
            cout<<"请输入起始城市名称："<<endl;
            cin>>name1;
            contralSysteam.showMaxDistance(name1);
        }

        cout<<endl<<"输入1继续，输入0退出。";
        cin>>co;

    }
    cout<<"按任意键返回主菜单。。。。。";
    getch();
    cout<<"正在返回,请稍候。。。。。。";
    Sleep(1000);
}

void quary(RoutePlanningSystem<int , int> &contralSysteam)
{
    cout<<"**              ============================================                    **"<<endl;
    cout<<"**              ||   城市是否在系统中1                    ||                    **"<<endl;
    cout<<"**              ||   道路是否在系统中2                    ||                    **"<<endl;
    cout<<"**              ||   查询邻接城市数量3                    ||                    **"<<endl;
    cout<<"**              ||    计算道路的距离4                     ||                    **"<<endl;
    cout<<"**              ||查询从该城市出发可以到达的所有城市5     ||                    **"<<endl;
    int op = 0;
    int co = 1;
    while(co){
        cout<<"请输入菜单选项：";
        cin>>op;
        switch (op) {
        case 1:
            cout<<"请输入要查询的城市名称：";
            int cityName;
            cin>>cityName;
            if(contralSysteam.isInCity(cityName)){
                cout<<"该城市在图中。";
            }
            else {
                cout<<"该城市不在图中。";
            }
            break;
        case 2:
            cout<<"请输入要城市1和城市2名称：";
            int name1,name2;
            cin>>name1;
            cin>>name2;
            if(contralSysteam.isInRoad(name1 , name2)){
                cout<<"该道路在图中。";
            }
            else {
                cout<<"该道路不在图中。";
            }
            break;
        case 3:
            cout<<"请输入要查询的城市名称：";
            cin>>cityName;
            cout<<contralSysteam.NeiborsCount(cityName);
            break;
        case 4:
            cout<<"请输入要城市1和城市2名称：";
            cin>>name1;
            cin>>name2;
            cout<<contralSysteam.getRoadDistance(name1 , name2);
            break;
        case 5:
            cout<<"请输入要查询的城市名称：";
            cin>>cityName;
            contralSysteam.getRechableCity(cityName , PrintCity);
            break;
        }
        cout<<endl<<"输入1继续，输入0退出。";
        cin>>co;
    }
    cout<<"按任意键返回主菜单。。。。。";
    getch();
    cout<<"正在返回,请稍候。。。。。。";
    Sleep(1000);
}


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    SetConsoleOutputCP(CP_UTF8);
    RoutePlanningSystem<int , int> contralSysteam(10);
    for(int i = 0 ; i < 10; i++){
        contralSysteam.addCity(i+1);
    }
    contralSysteam.addRoad(1 , 2 , 50);
    contralSysteam.addRoad(3 , 2 , 10);
    contralSysteam.addRoad(4 , 2 , 60);
    contralSysteam.addRoad(6 , 8 , 150);
    contralSysteam.addRoad(5 , 9 , 80);
    contralSysteam.addRoad(5 , 7 , 160);

//    Widget w;
//    w.show();
    showMenu();
    int op = 0;
    while (1) {
        cin>>op;
        switch (op) {
        case 1:
            system("cls");
            showInfo(contralSysteam);
            system("cls");
            showMenu();
            break;
        case 2:
            system("cls");
            readFaile(contralSysteam);
            system("cls");
            showMenu();
            break;
        case 3:
            system("cls");
            calculate(contralSysteam);
            system("cls");
            showMenu();
            break;
        case 4:
            system("cls");
            quary(contralSysteam);
            system("cls");
            showMenu();
            break;
        }

    }

    return a.exec();
}

