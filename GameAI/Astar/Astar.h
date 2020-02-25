/*
//声明 A*算法对象类
*/ 
#include <vector>
#include <list>

using namespace std;

// 移动消耗，1为直移，2为斜移
const int kCost1 = 10;
const int kCost2 = 14;

// 走迷宫的角色
struct Point
{
    int x,y;
    int F,G,H;
    Point *parent;
    Point(int _x,int _y):x(_x),y(_y),F(0),G(0),H(0),parent(NULL)  //变量初始化 
    { 
    }
};

class Astar
{
public:
    void InitAstarMaze(vector<vector<int> > &_maze);
    list<Point *> GetPath(Point &startPoint, Point &endPoint, bool isIgnoreCorner);

private:
    Point *findPath(Point &startPoint, Point &endPoint, bool isIgnoreCorner);
    vector<Point *> getSurroundPoints(const Point *point, bool isIgnoreCorner) const;
    bool isCanReach(const Point *point, const Point *target, bool isIgnoreCorner) const;    //判断某点是否可以用于下一步判断 
    Point *isInList(const list<Point *> &list, const Point *point) const;    // 判断开启/关闭列表中是否包含某点
    Point *getLeastFpoint();    //从开启列表中返回F值最小的点

    //计算FGH
    int calcG(Point *temp_start, Point *point);
    int calcH(Point *point, Point *end);
    int calcF(Point *point);

private:
    vector<vector<int> > maze;
    list<Point *> openList;
    list<Point *> closeList;
};

