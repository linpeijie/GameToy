#ifndef BFS_H
#define BFS_H
#include <iostream>
#include <vector>
#include <list>
#include <cmath>
#include "../includes/Point.h"

using namespace std;

class BFS
{
private:
    vector<vector<int> >       maze;
    list<shared_ptr<Point> >   openList;
    list<shared_ptr<Point> >   closeList;

    shared_ptr<Point>          findPath(Point startPoint, Point endPoint, bool isIgnoreCorner);
    vector<shared_ptr<Point> > getSurroundPoints(shared_ptr<Point> point, bool isIgnoreCorner) const;
    shared_ptr<Point>          isInList(list<shared_ptr<Point> > list,shared_ptr<Point> point) const;
    bool                       isCanReach(shared_ptr<Point> point, shared_ptr<Point> target, bool isIgnoreCorner) const;

public:
    BFS() {}
    ~BFS() {}

    BFS(vector<vector<int> > _maze);

    void                       setMaze(vector<vector<int> > _maze);
    list<shared_ptr<Point> >   GetPath(Point startPoint, Point endPoint, bool isIgnoreCorner);
    list<shared_ptr<Point> >   getSearchPath();
};

#endif