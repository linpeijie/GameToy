#include <iostream>
#include "Astar.h"

using namespace std;

int main()
{
    // 构建迷宫, 1表示不能通过
    vector<vector<int> > maze = {
        {1,0,1,1,1,1,1,1,1,1,1,1},
        {1,0,0,1,1,0,1,0,0,0,0,1},
        {1,0,0,1,1,0,0,0,0,0,0,1},
        {1,0,0,0,0,0,1,0,0,1,1,1},
        {1,1,1,0,0,0,0,0,1,1,0,1},
        {1,1,0,1,0,0,0,0,0,0,0,1},
        {1,0,1,0,0,0,0,1,0,0,0,1},
        {1,1,1,1,1,1,1,1,1,1,0,1}
    };

    for(auto m:maze)
    {
        for(auto n:m)
        {
            cout << n;
        }
        cout << endl;
    }


    Astar astar;
    astar.InitAstarMaze(maze);

    // 起点和终点
    Point start(0,1);
    Point end(7,10);
    // A*算法计算路径
    list<Point *> path = astar.GetPath(start, end, false);
    //打印
    cout << "begin->";
    for(auto &p:path)
        cout<<'('<<p->x<<','<<p->y<<')' << "->";
    cout << "end" << endl;

    return 0;
}
