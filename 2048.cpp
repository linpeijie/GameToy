// File:    2048.cpp
// Author:  linpeijie (linpeijie_4626@163.com)
// Date:    2019/10/05 09:41:59
#include<iostream>
//#include<windows.h>
#include<ctime>
#include<unistd.h>
using namespace std;

const int ROW = 4;
const int COL = 4;
int game[ROW][COL] = {0};


//上下左右
const int UP = 1;
const int DOWN = 2;
const int LEFT = 3;
const int RIGHT = 4;

//游戏所处的状态
const int GAME_OVER = 1;
const int GAME_WIN = 2;
const int GAME_CONTINUE = 3;

enum GameNum
{
    Game_2 = 2,
    Game_4 = 4,
    Game_8 = 8,
    Game_16 = 16,
    Game_32 = 32,
    Game_64 = 64,
    Game_128 = 128,
    Game_256 = 256,
    Game_512 = 512,
    Game_1024 =1024,
    Game_2048 = 2048,
};

//打印所得数组
void Print()
{
    system("clear");
    cout << "****************** 2048 控 制 台 版 ********************" << endl;
    cout << "********************  By 林 培 捷  *********************" << endl;
    cout << '\n';

    for (int i = 0; i < ROW; ++i)
    {
        cout << "------------------------------------------------------------------" << endl;

        for (int j = 0; j < COL; ++j)
        {

            if (game[i][j] == 0)
            {
                cout << "|\t\t";
            }
            else
            {
                cout << "|\t" << game[i][j] << "\t";
            }
        }

        cout << "|" << endl;
    }

    cout << "------------------------------------------------------------------" << endl;
}

//随机在空白处生成2或4
bool CreateNumber()
{
    int x = -1;
    int y = -1;
    int times = 0;
    int maxTimes = ROW * COL;
    //三分之一概率生成4，三分之二概率生成2
    int whitch = rand() % 3;

    do
    {
        x = rand() % ROW;
        y = rand() % COL;
        ++times;
    } while(game[x][y] != 0 && times <= maxTimes);

    if (times >= maxTimes)
    {
        return false;
    }
    else
    {
        GameNum num;
        if(whitch == 0)
        {
            num = Game_4;
        }
        else if(whitch)
        {
            num =Game_2;
        }
        game[x][y] = num;
    }
    return true;
}

//合并数字,处理逻辑模块;一次性检查全部的单元格;
void Process(int direction)
{
    switch(direction)
    {
        case UP:
            for (int row = 1; row < ROW; ++row)
            {
                for(int crow = row; crow >= 1; --crow)
                {
                     
                    for (int col = 0; col < COL; ++col)
                    {
                        //若上一个格子为空
                        if (game[crow-1][col] == 0)
                        {
                            game[crow-1][col] = game[crow][col];
                            game[crow][col] = 0;
                        }
                        else
                        {
                            //否则乘2，合并格子和数字
                            if (game[crow-1][col] == game[crow][col])
                            {
                                game[crow-1][col] *= 2;
                                game[crow][col] = 0;
                            }
                        }
                    }
                }
            }
            break;
        case DOWN:
            //从下往上计算
            for (int row = ROW - 2; row >= 0; --row)
            {
                for (int crow = row; crow < ROW -1; ++crow)
                {
                        
                    for (int col = 0; col < COL; ++col)
                    {
                        //若上一个格子为空
                        if (game[crow+1][col] == 0)
                        {
                            game[crow+1][col] = game[crow][col];
                            game[crow][col] = 0;
                        }
                        else
                        {
                            //若数字相同则合并
                            if(game[crow+1][col] == game[crow][col])
                            {
                                game[crow+1][col] *= 2;
                                game[crow][col] = 0;
                            }
                        }
                    }
                }
            }
            break;
        case LEFT:
            //从左往右计算
            for (int col = 1; col < COL; ++col)
            {
                for (int ccol=col; ccol >= 1; --ccol)
                {
                    for (int row = 0; row < ROW; ++row)
                    {
                        //若左一个格子为空
                        if(game[row][ccol-1] == 0)
                        {
                            game[row][ccol-1] = game[row][ccol];
                            game[row][ccol] = 0;
                        }
                        else
                        {
                            //若相同，则合并
                            if(game[row][ccol-1] == game[row][ccol])
                            {
                                game[row][ccol-1] *= 2;
                                game[row][ccol] = 0;
                            }
                        }
                    }
                }
            }
            break;
        case RIGHT:
            //从右往左计算
            for (int col = COL -2; col >=0; --col)
            {
                for (int ccol = col; ccol <= COL-2; ++ccol)
                {
                    for (int row = 0; row < ROW; ++row)
                    {
                        //若右边格子为空
                        if(game[row][ccol+1] == 0)
                        {
                            game[row][ccol+1] = game[row][ccol];
                            game[row][ccol] = 0;
                        }
                        else
                        {
                            //否则合并
                            if(game[row][ccol+1] == game[row][ccol])
                            {
                                game[row][ccol+1] *= 2;
                                game[row][ccol] = 0;
                            }
                        }
                    }
                }
            }
            break;
    }
}


//处理输入输出，返回上下左右
int Input(char d)
{
    //读取上下左右四个方向键
    int upArrow = 0;
    int downArrow = 0;
    int leftArrow = 0;
    int rightArrow = 0;
    int direction = 0;

    while(true)
    {
        upArrow = d;
        downArrow = d;
        leftArrow = d;
        rightArrow = d;

        if(upArrow == 'w')
        {
            direction = UP;
            break;
        }
        else if(downArrow == 's')
        {
            direction = DOWN;
            break;
        }
        else if(leftArrow == 'a')
        {
            direction = LEFT;
            break;
        }
        else if(rightArrow == 'd')
        {
            direction = RIGHT;
            break;
        }

        sleep(1);
    }

    return direction;
}


//判断游戏状态
int Judge()
{
    //赢得游戏
    for (int i = 0; i < ROW; ++i)
    {
        for (int j = 0; j < COL; ++j)
        {
            if (game[i][j] == 2048)
            {
                return GAME_WIN;
                break;
            }
        }
    }

    //横向检查
    for (int i =0; i < ROW; ++i)
    {
        for (int j = 0; j < COL; ++j)
        {
            if (!game[i][j] || (game[i][j] == game[i][j+1]))
            {
                return GAME_CONTINUE;
                break;
            }
        }
    }

    //纵向检查
    for (int j = 0; j < COL; ++j)
    {
        for (int i = 0; i < ROW; ++i)
        {
            if(!game[i][j] || (game[i][j] == game[i+1][j]))
            {
                return GAME_CONTINUE;
                break;
            }
        }
    }

    return GAME_OVER;
}

int main()
{

    srand((unsigned int)time(0));
    CreateNumber();
    CreateNumber();
    Print();
    int direction = 0;
    int gameState = -1;
    char ch;

    while(true)
    {
        cout << "Please enter 'w, s, a or d' to control the direction: ";
        cin.get(ch).get();
        direction = Input(ch);

        gameState = Judge();
        if(direction && gameState == GAME_CONTINUE)
        {
            Process(direction);
            CreateNumber();
            Print();
            sleep(1);
        }
        else if(gameState == GAME_WIN)
        {
            Print();
            cout << "You Win!" << endl;
            break;
        }
        else if(gameState == GAME_OVER)
        {
            Print();
            cout << "You lose!" << endl;
            break;
        }
    }

    return 0;
}


