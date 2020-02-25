#include <iostream>
#include <vector>
#include <random>
#include <ctime>

int checkNeighborWalls(std::vector<std::vector <int> >,int, int, int, int, int);

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

    /* 打印地图 */
    for (auto line:initMap){
        for (auto col:line)
        {
            if (col == 0)
                std::cout << ' ';
            else
                std::cout << '*';
        }
            
        std::cout << std::endl;
    }
    std::cout << std::endl;
        
    /* 地图演化 */
    for(int loop = 0; loop < 5; ++loop)
    {
        /* 生成地图 */
        for (int line = 0; line < lines; ++line)
        {
           for (int col = 0; col < cols; ++col)
            {
                /* 
                1.如果当前元素是墙，那么周围超过 4 个墙就保持为墙 
                2.如果当前元素是地板，那么周围第一圈超过 5 个墙就变为墙或者周围第二圈小于2个就变为墙 
                */
                int wallCount1 = checkNeighborWalls(initMap, lines, cols, line, col, 1);
                int wallCount2 = checkNeighborWalls(initMap, lines, cols, line, col, 2);

                if (initMap[line][col] == 1)
                {
                    initMap[line][col] = wallCount1 >= 4 ? 1 : 0;
                }else
                {
                    if(loop < 2)
                        initMap[line][col] = (wallCount1 >= 5)? 1 : 0;
                    else
                        initMap[line][col] = (wallCount1 >= 5 || wallCount2 <= 2)? 1 : 0;
                }
                /* 保持墙壁不变 */
                if (line ==0 || col == 0 || line == lines - 1 || col == cols - 1)
                initMap[line][col] = 1;
            }
        }

        /* 打印地图 */
        for (auto line:initMap){
            for (auto col:line)
            {
                if (col == 0)
                    std::cout << ' ';
                else
                    std::cout << '*';
            }

            std::cout << std::endl;
        }
            
        std::cout << std::endl;
    }
    
    return 0;
}

/* 检测某个点周围有多少障碍物(墙) , cycle 为检测的圈数*/
int checkNeighborWalls(std::vector<std::vector <int> > M, int lines, int cols, int line, int col, int cycle=1)
{
    int count = 0;
    for (int i = line - cycle; i <= line + cycle; ++i)
        for (int j = col - cycle; j <= col + cycle; ++j)
        {
            if ((i >= 0 && i < lines) && (j >=0 && j < cols)) 
                 if (M[i][j] == 1)
                     count++;
        }
    
    /* 当前点为墙则不计算 */
    if(M[line][col] == 1)
        count--;
    
    return count;
}