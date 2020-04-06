#include <memory>

using namespace std;

// 边的权重，1为直移，2为斜移
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