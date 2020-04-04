#ifndef ASTAR2_H
#define ASTAR2_H
#include <iostream>
#include <vector>
#include <list>
#include <cmath>

using namespace std;

// 移动消耗，1为直移，2为斜移
const int kCost1 = 10;
const int kCost2 = 14;

// 地图上的点
struct Point
{
    int x,y;
    int F,G,H;
    shared_ptr<Point> parent;
    shared_ptr<Point> next;
    //变量初始化
    Point(int _x,int _y):x(_x),y(_y),F(0),G(0),H(0),parent(NULL),next(NULL){ }
};

class Astar
{
private:
    vector<vector<int> >       maze;
    list<shared_ptr<Point> >   openList;
    list<shared_ptr<Point> >   closeList;

    shared_ptr<Point>          findPath(Point startPoint, Point endPoint, bool isIgnoreCorner);
    shared_ptr<Point>          getLeastFpoint();
    vector<shared_ptr<Point> > getSurroundPoints(shared_ptr<Point> point, bool isIgnoreCorner) const;
    bool                       isCanReach(shared_ptr<Point> point, shared_ptr<Point> target, bool isIgnoreCorner) const;
    shared_ptr<Point>          isInList(list<shared_ptr<Point> > list,shared_ptr<Point> point) const;

    //计算 F = G + H
    int                        calcG(shared_ptr<Point> temp_start, shared_ptr<Point> point);
    int                        calcH(shared_ptr<Point> point, shared_ptr<Point> end);
    int                        calcF(shared_ptr<Point> point);

public:
    Astar() {}
    ~Astar() {}
    Astar(vector<vector<int> > _maze);

    void                       setMaze(vector<vector<int> > _maze);
    list<shared_ptr<Point> >   GetPath(Point startPoint, Point endPoint, bool isIgnoreCorner);
    list<shared_ptr<Point> >   getSearchPath();
};

#endif