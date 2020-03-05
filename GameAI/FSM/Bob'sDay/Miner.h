//------------------------------------------------------------------------
//
//  Name:   Miner.h
//
//  Desc:   A class defining a goldminer.
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#ifndef MINER_H
#define MINER_H

#include <string>
#include <cassert>
#include "BaseGameEntity.h"
#include "Locations.h"

class State;

const int ComfortLevel       = 5;  //银行账户存满多少钱，则回家休息
const int MaxNuggets         = 3;  //口袋最多能放多少金子
const int ThirstLevel        = 5;  //多久后人物感到口渴
const int TirednessThreshold = 5;  //多久后人物感到累

/* 所有类都必须继承BaseGameENtity基础类 */
class Miner : public BaseGameEntity
{
private:

    State* m_pCurrentState;
    location_type m_Location;

    //矿工可携带的金子数量
    int m_iGoldCarried;

    //银行账户余额
    int m_iMoneyInBank;

    //饥渴值
    int m_iThirst;

    //疲劳值
    int m_iFatigue;

public:

    Miner(int id);
    //必须实现
    void Update();

    //改变当前状态到新的状态
    void ChangeState(State* new_state);

    //移动位置
    location_type Location()const{return m_Location;}
    void ChangeLocation(const location_type loc){m_Location=loc;}

    //计算携带的金子数量
    int  GoldCarried()const{return m_iGoldCarried;}
    void SetGoldCarried(const int val){m_iGoldCarried = val;}
    void AddToGoldCarried(const int val);
    bool PocketsFull()const{return m_iGoldCarried >= MaxNuggets;}

    //计算疲劳值
    bool Fatigued()const;
    void DecreaseFatigue(){m_iFatigue -= 1;}
    void IncreaseFatigue(){m_iFatigue += 1;}

    //计算银行账户余额
    int  Wealth()const{return m_iMoneyInBank;}
    void SetWealth(const int val){m_iMoneyInBank = val;}
    void AddToWealth(const int val);

    //计算饥渴值
    bool Thirsty()const;
    void BuyAndDrinkAWhiskey(){m_iThirst = 0; m_iMoneyInBank-=2;}

};

#endif