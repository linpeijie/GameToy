#include "BFS.h"

BFS::BFS(vector<vector<int> > _maze)
{
    this->maze = _maze;
}

void BFS::setMaze(vector<vector<int> > _maze)
{
    this->maze = _maze;
}

// 计算路径,返回指针列表
list<shared_ptr<Point> > BFS::GetPath(Point startPoint, Point endPoint, bool isIgnoreCorner)
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

// BFS算法
shared_ptr<Point> BFS::findPath(Point startPoint, Point endPoint, bool isIgnoreCorner)
{
    // 一定要记得把这两个数组清空，不然会发生错误
    openList.clear();
    closeList.clear();
    // 1.首先将根节点放入队列中
    shared_ptr<Point> newEndPoint(new Point(endPoint.x, endPoint.y));
    openList.push_back(shared_ptr<Point>(new Point(startPoint.x, startPoint.y))); //置入起点,拷贝开辟一个节点，内外隔离

    while (!openList.empty())
    {
        // 2 从队列中取出第一个节点。
        auto curPoint = openList.front();
        openList.remove(curPoint);

        //2.2 找到当前周围八个格中可以通过的格子，放入列表中
        auto surroundPoints = getSurroundPoints(curPoint,isIgnoreCorner);

        for(auto &target:surroundPoints)
        {
            //2.2 对某一个格子，如果它不在关闭列表中(未访问过)，加入到开启列表和关闭列表
            if(!isInList(closeList, target))
            {
                target->parent = curPoint;
                openList.push_back(target);
                closeList.push_back(target);
            }

            //2.1 如果找到了目标节点，直接返回即可
            shared_ptr<Point> resPoint = isInList(openList, newEndPoint);
            if(resPoint)
                return resPoint; //返回列表里的节点指针，不要用原来传入的endpoint指针，因为发生了深拷贝
        }
    }
    // 3.队列为空，且未找到目标节点
    return NULL;
}

// 返回搜索路径
list<shared_ptr<Point> > BFS::getSearchPath()
{
    return closeList;
}

// 找到周围可以通过的节点
vector<shared_ptr<Point> > BFS::getSurroundPoints(shared_ptr<Point> point, bool isIgnoreCorner) const
{
    vector<shared_ptr<Point>> surroundPoints;

    for(int x=point->x-1;x<=point->x+1;x++)
        for(int y=point->y-1;y<=point->y+1;y++)
            if(isCanReach(point,shared_ptr<Point>(new Point(x, y)), isIgnoreCorner))
                surroundPoints.push_back(shared_ptr<Point>(new Point(x,y)));

    return surroundPoints;
}

// 判断某个节点是否在列表中，这里不能比较指针，因为每次加入列表是新开辟的节点，只能比较坐标
shared_ptr<Point> BFS::isInList(list<shared_ptr<Point>> list, shared_ptr<Point> point) const
{
    //判断某个节点是否在列表中，这里不能比较指针，因为每次加入列表是新开辟的节点，只能比较坐标
    for(auto p:list)
        if(p->x==point->x&&p->y==point->y)
            return p;
    return NULL;
}

// 判断是否可以通过
bool BFS::isCanReach(shared_ptr<Point> point, shared_ptr<Point> target, bool isIgnoreCorner) const
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