#include "Dijkstra.h"

Dijkstra::Dijkstra(vector<vector<int>> _maze)
{
    this->maze = _maze;
    for (int i = 0; i < this->maze.size() * this->maze[0].size(); ++i)
        cost.push_back(INT_MAX);
}

// 重置地图
void Dijkstra::setMaze(vector<vector<int>> _maze)
{
    this->maze = _maze;
}

// 计算路径,返回指针列表
list<shared_ptr<Point> > Dijkstra::GetPath(Point startPoint, Point endPoint, bool isIgnoreCorner)
{
    shared_ptr<Point> result = findPath(startPoint, endPoint, isIgnoreCorner);
    list<shared_ptr<Point>> path;
    //返回路径，如果没找到路径，返回空链表
    while(result)
    {
        path.push_front(result);
        result = result->parent;
    }

    return path;
}

// Dijkstra算法
shared_ptr<Point> Dijkstra::findPath(Point startPoint, Point endPoint, bool isIgnoreCorner)
{
    // 每次调用都要重新初始化，因为连续调用的时候，内存是连续的，所以上次计算结果还会保存
    // openList（Q）存储需要遍历的节点，closeList（S）存储所有已知实际最短路径值的顶点
    // cost 存储的便是从 s 到 v 的最短路径
    openList.clear();
    closeList.clear();
    cost.clear();
    for (int i = 0; i < this->maze.size() * this->maze[0].size(); ++i)
        cost.push_back(INT_MAX);
    shared_ptr<Point> resPoint = NULL;

    // 1.起始点cost=0，其他为无穷大
    shared_ptr<Point> newEndPoint(new Point(endPoint.x, endPoint.y));
    openList.push_back(shared_ptr<Point>(new Point(startPoint.x, startPoint.y))); //置入起点,拷贝开辟一个节点，内外隔离
    cost[startPoint.y*maze[0].size() + startPoint.x] = 0;

    while (!resPoint)
    {
        // 2.取出当前节点 u, 未访问过的
        auto curPoint = openList.front();
        openList.remove(curPoint);
        // 3.找出节点 u 的全部连通节点 v
        auto surroundPoints = getSurroundPoints(curPoint,isIgnoreCorner);

        for(auto &target:surroundPoints)
        {
            // 4.松弛操作，如果从d[u]+w(u,v) < d[v]，则更新d[v]为这个更小的值
            auto new_cost = cost[curPoint->y*maze[0].size() + curPoint->x] + costCurToNext(curPoint, target);
            // 如果是未访问过的，意味着该点的距离还是无穷大，因此第一次访问的距离就是最短距离
            if(!isInList(closeList, target) || (new_cost < cost[target->y*maze[0].size() + target->x]))
            {
                // 判断该节点是否已经搜索过，如果是的话，在原节点指针上进行修改，
                // 如果不做这一步的话，会出现路径节点指向旧节点指针的情况，导致出现BUG
                shared_ptr<Point> oldTarget = isInList(openList, target);
                if (oldTarget)
                    target = oldTarget;

                target->parent = curPoint;
                cost[target->y*maze[0].size() + target->x] = new_cost;
                openList.push_back(target);
                closeList.push_back(target);
            }
        }
        resPoint = isInList(closeList, newEndPoint);
    }

    return resPoint;
}

// 返回全部搜索路径
list<shared_ptr<Point> > Dijkstra::getSearchPath()
{
    return closeList;
}

// 获取周围待搜索节点
vector<shared_ptr<Point> > Dijkstra::getSurroundPoints(shared_ptr<Point> point, bool isIgnoreCorner) const
{
    vector<shared_ptr<Point>> surroundPoints;

    for(int x=point->x-1;x<=point->x+1;x++)
        for(int y=point->y-1;y<=point->y+1;y++)
            if(isCanReach(point,unique_ptr<Point>(new Point(x, y)), isIgnoreCorner))
                surroundPoints.push_back(shared_ptr<Point>(new Point(x,y)));

    return surroundPoints;
}

// 判断是否可以通过
bool Dijkstra::isCanReach(shared_ptr<Point> point, unique_ptr<Point> target, bool isIgnoreCorner) const
{
    //如果点与当前节点重合、超出地图、是障碍物、或者在关闭列表中，返回false
    if((target->x<0||target->x>maze.size()-1)
        ||(target->y<0&&target->y>maze[0].size()-1)
        ||(maze[target->x][target->y]==1)
        ||(target->x==point->x&&target->y==point->y))
    {
        return false;
    }
    else
    {
        if(abs(point->x-target->x)+abs(point->y-target->y)==1) //非斜角可以
            return true;
        else
        {
            //斜对角要判断是否绊住
            if(maze[point->x][target->y]==0&&maze[target->x][point->y]==0)
                return true;
            else
                return isIgnoreCorner;
        }
    }
}

// 判断某个节点是否在列表中，这里不能比较指针，因为每次加入列表是新开辟的节点，只能比较坐标
shared_ptr<Point> Dijkstra::isInList(list<shared_ptr<Point>> list, shared_ptr<Point> point) const
{
    //判断某个节点是否在列表中，这里不能比较指针，因为每次加入列表是新开辟的节点，只能比较坐标
    for(auto p:list)
        if(p->x==point->x&&p->y==point->y)
            return p;
    return NULL;
}

/* 计算当前节点到下一个节点的耗费 */
int Dijkstra::costCurToNext(shared_ptr<Point> temp_point, shared_ptr<Point> point)
{
    int extra = (abs(point->x - temp_point->x) + abs(point->y - temp_point->y))==1 ? kCost1 : kCost2;    // 判断是直边还是斜边
    return extra;
}