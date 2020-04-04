#ifndef BFS_H
#define BFS_H
#include <iostream>
#include <vector>
#include <list>
#include <cmath>

using namespace std;

// 地图上的点
struct Point
{
    int x,y;
    shared_ptr<Point> parent;
    shared_ptr<Point> next;
    //变量初始化
    Point(int _x,int _y):x(_x),y(_y),parent(NULL),next(NULL){ }
};

class BFS
{
private:

};

#endif