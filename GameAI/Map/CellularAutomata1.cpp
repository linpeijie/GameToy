#include <iostream>
#include <vector>
#include <random>
#include <ctime>

int checkNeighborWalls(std::vector<std::vector <int> >,int, int, int, int, int);
void printMap(std::vector<std::vector <int> >);

int main()
{
    int cols = 90;
    int lines =30;

    /* 初始化地图 */
    std::vector<std::vector <int> > initMap(lines, std::vector<int>(cols));
    std::default_random_engine e(time(0));
    std::uniform_real_distribution<double> u(0.0,1.0);
    for (int line = 0; line < lines; ++line)
    {
        for (int col = 0; col < cols; ++col)
        {
            if (line ==0 || col == 0 || line == lines - 1 || col == cols - 1)
                initMap[line][col] = 1;
            else
                initMap[line][col] = u(e) < 0.45 ? 1 : 0;
        }
    }   

    /* 生成地图 */
    for (int line = 0; line < lines; ++line)
    {
       for (int col = 0; col < cols; ++col)
        {
            /* 
            1.如果当前元素周围超过 4 个墙就保持为墙 
            2.如果当前元素周围少于 4 个墙就变为地面
            */
            int wallCount1 = checkNeighborWalls(initMap, lines, cols, line, col, 1);

            if (wallCount1 > 4)
                initMap[line][col] = 1;
            else if(wallCount1 < 4)
                initMap[line][col] = 0;
        }
    }

    printMap(initMap);
    
    return 0;
}

/* 检测某个点周围有多少障碍物(墙) , cycle 为检测的圈数*/
int checkNeighborWalls(std::vector<std::vector <int> > M, int lines, int cols, int line, int col, int cycle=1)
{
    int count = 0;
    for (int i = line - cycle; i <= line + cycle; ++i)
        for (int j = col - cycle; j <= col + cycle; ++j)
        {
            if ((i >= 0 && i < lines) && (j >=0 && j < cols))    // 如果没有超出边界，则正常计算
            {
                if (i != line || j != col)
                    count += M[i][j];
            }else
                count++;    // 如果这个点周围的某个点超过边界，则该点一定在边界上，值一定得设为1，故直接count++
        }
    
    return count;
}

/* 打印地图 */
void printMap(std::vector<std::vector <int> > M)
{  
    for (auto line:M)
    {
        for (auto col:line)
        {
            if (col == 0)
                std::cout << ' ';
            else
                std::cout << '*';
        }
        std::cout << std::endl;
    }
}