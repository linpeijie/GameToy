#ifndef DIJKSTRA_H
#define DIJKSTRA_H
#include <vector>
#include <list>
#include <cmath>
#include "../BFS/BFS.h"

using namespace std;

class Dijkstra
{
private:
    vector<vector<int> >       maze;
    list<shared_ptr<Point> >   openList;
    list<shared_ptr<Point> >   closeList;
    vector<int>                cost;

    shared_ptr<Point>          findPath(Point startPoint, Point endPoint, bool isIgnoreCorner);
    vector<shared_ptr<Point> > getSurroundPoints(shared_ptr<Point> point, bool isIgnoreCorner) const;
    bool                       isCanReach(shared_ptr<Point> point, unique_ptr<Point> target, bool isIgnoreCorner) const;
    shared_ptr<Point>          isInList(list<shared_ptr<Point> > list,shared_ptr<Point> point) const;
    int                        costCurToNext(shared_ptr<Point> temp_point, shared_ptr<Point> point);

public:
    Dijkstra() {}
    ~Dijkstra() {}
    Dijkstra(vector<vector<int> > _maze);

    void                       setMaze(vector<vector<int> > _maze);
    list<shared_ptr<Point> >   GetPath(Point startPoint, Point endPoint, bool isIgnoreCorner);
    list<shared_ptr<Point> >   getSearchPath();
};


#endif