#include <iostream>
#include <vector>
#include <queue>
#include <list>
#include <random>
#include <ctime>

/* 地图宽高 */
const int height = 90;
const int width = 20;

/* 存储点坐标 */
struct Coord {
    int x, y;
    Coord(int _x, int _y):x(_x),y(_y){}
};

std::vector<std::vector <int> > createMap();
void generateMap(std::vector<std::vector <int> > &);
int checkNeighborWalls(std::vector<std::vector <int> >, int, int);
std::list<Coord> getRegionPoints(std::vector<std::vector <int> > M, int, int);
std::list<std::list<Coord> > getRegions(std::vector<std::vector <int> >, int);
void processMap(std::vector<std::vector <int> > &);
void printMap(std::vector<std::vector <int> >);

int main()
{

    /* 初始化地图 */
    std::vector<std::vector <int> > initMap = createMap();
    printMap(initMap);

    /* 生成地图 */
    generateMap(initMap);
    printMap(initMap);

    /* 处理地图 */
    processMap(initMap);
    std::cout << std::endl;
    printMap(initMap);

    return 0;
}

/* 初始化地图 */
std::vector<std::vector <int> > createMap()
{
    std::vector<std::vector <int> > initMap(width, std::vector<int>(height));
    std::default_random_engine e(time(0));
    std::uniform_real_distribution<double> u(0.0,1.0);

    for (int x = 0; x < width; ++x)
    {
        for (int y = 0; y < height; ++y)
        {
            if (x ==0 || y == 0 || x == width - 1 || y == height - 1)  // 判断是否是边界点，边界永远是墙壁
                initMap[x][y] = 1;
            else
                initMap[x][y] = u(e) < 0.45 ? 1 : 0;                   // 以小于0.45的概率生成1
        }
    }
    return initMap;
}

/* 生成地图 */
void generateMap(std::vector<std::vector <int> > &initMap)
{
    for (int x = 0; x < width; ++x)
    {
       for (int y = 0; y < height; ++y)
        {
            int wallCount1 = checkNeighborWalls(initMap, x, y);  // 计算该点周围墙壁的数量

            if (wallCount1 > 4)  // 如果当前元素周围超过 4 个墙就保持为墙
                initMap[x][y] = 1;
            else if(wallCount1 < 4)  // 如果当前元素周围少于 4 个墙就变为地面
                initMap[x][y] = 0;
        }
    }
}

/* 计算某点周围墙壁数量*/
int checkNeighborWalls(std::vector<std::vector <int> > M, int x, int y)
{
    int count = 0;
    for (int i = x - 1; i <= x + 1; ++i)
        for (int j = y - 1; j <= y + 1; ++j)
        {
            if ((i >= 0 && i < width) && (j >=0 && j < height))    // 判断是否超出边界
            {
                if (i != x || j != y)
                    count += M[i][j];
            }else
                count++;    // 如果这个点周围的某个点超过边界，则该点一定在边界上，值一定得设为1，故直接count++
        }

    return count;
}

/* 将小于某个值的区域消除 */
void processMap(std::vector<std::vector <int> > &M)
{
    /* 消除墙壁 */
    std::list<std::list<Coord> > wallRegions = getRegions(M, 1);
    int wallThresholdSize = 5;

    for (auto wallregion:wallRegions)
    {
        if (wallregion.size() < wallThresholdSize)
        {
            for (auto point:wallregion)
            {
                M[point.x][point.y] = 0;
            }
        }
    }

    /* 消除房间 */
    std::list<std::list<Coord> > roomRegions = getRegions(M, 0);
    int roomThresholdSize = 20;

    for (auto roomregion:roomRegions)
    {
        if (roomregion.size() < roomThresholdSize)
        {
            for (auto point:roomregion)
            {
                M[point.x][point.y] = 1;
            }
        }
    }

}

/* 返回地图中某类区域的集合 */
std::list<std::list<Coord> > getRegions(std::vector<std::vector <int> > M, int pointType)
{
    std::list<std::list<Coord> > regions;
    std::vector<std::vector<int> > mapFlags(width, std::vector<int>(height));

    for (int x = 0; x < width; ++x)
        for (int y = 0; y < height; ++y)
        {
            if(mapFlags[x][y] == 0 && M[x][y] == pointType)
            {
                std::list<Coord> newRegion = getRegionPoints(M, x, y);
                regions.push_back(newRegion);

                for (auto e:newRegion)
                {
                    mapFlags[e.x][e.y] = 1;
                }
            }
        }
    return regions;
}

/* 找到某个区域中的所有点 , 启发式搜索， 类似广度遍历法，遍历某个点周围与其相同的点，直到不再有相同的点*/
std::list<Coord> getRegionPoints(std::vector<std::vector <int> > M, int startX, int startY)
{
    std::list<Coord> points;  // 存储一个区域内的所有点
    std::vector<std::vector<int> > mapFlags(width, std::vector<int>(height));  // 标记相同区域的点
    int pointType = M[startX][startY];  // 起始点的类型（墙，房间）

    std::queue<Coord> queue;  // 存储遍历的每个点
    queue.push(Coord(startX, startY));
    mapFlags[startX][startY] = 1;

    while (queue.size() > 0)
    {
        Coord point = queue.front();
        queue.pop();

        points.push_back(point);

        for (int x = point.x - 1; x <= point.x + 1; ++x)
        {
            for (int y = point.y - 1; y <= point.y + 1; ++y)
            {
                if ((x >= 0 && x < width) && (y >=0 && y < height) && (y == point.y || x == point.x))
                {
                    if (mapFlags[x][y] == 0 && M[x][y] == pointType)
                    {
                        mapFlags[x][y] = 1;
                        queue.push(Coord(x, y));
                    }
                }
            }
        }
    }
    return points;
}

/* 打印地图 */
void printMap(std::vector<std::vector <int> > M)
{
    for (auto x:M)
    {
        for (auto y:x)
        {
            if (y == 0)
                std::cout << ' ';
            else
                std::cout << '#';
        }
        std::cout << std::endl;
    }
}