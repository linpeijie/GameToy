#include "Astar.h"

Astar::Astar(vector<vector<int>> _maze)
{
    this->maze = _maze;
}

// 重置地图
void Astar::setMaze(vector<vector<int>> _maze)
{
    this->maze = _maze;
}

// 计算路径,返回指针列表
list<shared_ptr<Point> > Astar::GetPath(Point startPoint, Point endPoint, bool isIgnoreCorner)
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

shared_ptr<Point> Astar::findPath(Point startPoint, Point endPoint, bool isIgnoreCorner)
{
    // 一定要记得把这两个数组清空，不然会发生内存错误
    openList.clear();
    closeList.clear();

    shared_ptr<Point> newEndPoint(new Point(endPoint.x, endPoint.y));
    openList.push_back(shared_ptr<Point>(new Point(startPoint.x, startPoint.y))); //置入起点,拷贝开辟一个节点，内外隔离

    while (!openList.empty())
    {
        auto curPoint = getLeastFpoint(); //找到F值最小的点
        openList.remove(curPoint); //从开启列表中删除
        closeList.push_back(curPoint); //放到关闭列表
        //1,找到当前周围八个格中可以通过的格子
        auto surroundPoints = getSurroundPoints(curPoint,isIgnoreCorner);
        for(auto &target:surroundPoints)
        {
            //2,对某一个格子，如果它不在开启列表中，加入到开启列表，设置当前格为其父节点，计算F G H
            if(!isInList(openList, target))
            {
                target->parent = curPoint;

                target->G = calcG(curPoint,target);
                target->H = calcH(target, newEndPoint);
                target->F = calcF(target);

                openList.push_back(target);
            }
            //3，对某一个格子，它在开启列表中，计算G值, 如果比原来的大, 就什么都不做, 否则设置它的父节点为当前点,并更新G和F
            else
            {
                int tempG=calcG(curPoint,target);
                if(tempG<target->G)
                {
                    target->parent=curPoint;

                    target->G=tempG;
                    target->F=calcF(target);
                }
            }
            shared_ptr<Point> resPoint=isInList(openList, newEndPoint);
            if(resPoint)
                return resPoint; //返回列表里的节点指针，不要用原来传入的endpoint指针，因为发生了深拷贝
        }
    }

    return NULL;
}

list<shared_ptr<Point> > Astar::getSearchPath()
{
    return closeList;
}

/*  找到F值最小的下一个节点 */
shared_ptr<Point> Astar::getLeastFpoint()
{
    if(!openList.empty())
    {
        auto resPoint = openList.front();
        for(auto &point:openList)
        {
            if(point->F < resPoint->F)
            {
                resPoint = point;
            }
        }
        return resPoint;
    }
    return NULL;
}

vector<shared_ptr<Point> > Astar::getSurroundPoints(shared_ptr<Point> point, bool isIgnoreCorner) const
{
    vector<shared_ptr<Point>> surroundPoints;

    for(int x=point->x-1;x<=point->x+1;x++)
        for(int y=point->y-1;y<=point->y+1;y++)
            if(isCanReach(point,shared_ptr<Point>(new Point(x, y)), isIgnoreCorner))
                surroundPoints.push_back(shared_ptr<Point>(new Point(x,y)));

    return surroundPoints;
}

// 判断是否可以通过
bool Astar::isCanReach(shared_ptr<Point> point, shared_ptr<Point> target, bool isIgnoreCorner) const
{
    //如果点与当前节点重合、超出地图、是障碍物、或者在关闭列表中，返回false
    if((target->x<0||target->x>maze.size()-1)
        ||(target->y<0&&target->y>maze[0].size()-1)
        ||(maze[target->x][target->y]==1)
        ||(target->x==point->x&&target->y==point->y)
        ||(isInList(closeList, target)))
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
shared_ptr<Point> Astar::isInList(list<shared_ptr<Point>> list, shared_ptr<Point> point) const
{
    //判断某个节点是否在列表中，这里不能比较指针，因为每次加入列表是新开辟的节点，只能比较坐标
    for(auto p:list)
        if(p->x==point->x&&p->y==point->y)
            return p;
    return NULL;
}

/* 曼哈顿距离计算G */
int Astar::calcG(shared_ptr<Point> temp_point, shared_ptr<Point> point)
{
    int extraG = (abs(point->x - temp_point->x) + abs(point->y - temp_point->y))==1 ? kCost1 : kCost2;    // 判断是直边还是斜边
    int parentG = point->parent == NULL ? 0 : point->parent->G;
    return extraG + parentG;
}

/* 欧几里何距离计算H */
int Astar::calcH(shared_ptr<Point> point, shared_ptr<Point> end)
{
    //用简单的欧几里得距离计算H，这个H的计算是关键，还有很多算法
    return sqrt((double)(end->x-point->x)*(double)(end->x-point->x)+(double)(end->y-point->y)*(double)(end->y-point->y))*kCost1;
}

/* F = G + H */
int Astar::calcF(shared_ptr<Point> point)
{
    return point->G + point->H;
}