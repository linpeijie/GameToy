//------------------------------------------------------------------------
//
//  Name:   MinerOwnedStates.h
//
//  Desc:   All the states that can be assigned to the Miner class
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
#ifndef MINER_OWNED_STATES_H
#define MINER_OWNED_STATES_H
#include "State.h"

class Miner;


/**
 * 在这个状态里，矿工会执行‘走到矿场’、‘挖矿’和'离开'这三个动作。
 * 如果口袋满了，矿工会改变当前状态变为 VisitBankAndDepositGold。
 * 如果渴了，矿工会改变当前状态为 QuenchThirst。
 * */
class EnterMineAndDigForNugget : public State
{
private:

    EnterMineAndDigForNugget(){}

public:
    //禁止复制构造函数和赋值,同时避免内存泄露
    ~EnterMineAndDigForNugget(){}
    EnterMineAndDigForNugget(const EnterMineAndDigForNugget&)=delete;
    EnterMineAndDigForNugget& operator=(const EnterMineAndDigForNugget&)=delete;

    // static保证实例对象是全局的
    static EnterMineAndDigForNugget* Instance();

    virtual void Enter(Miner* miner);

    virtual void Execute(Miner* miner);

    virtual void Exit(Miner* miner);
};


/**
 * 在这个状态中，矿工会‘进到银行’，然后‘存储金子’。
 * 如果银行账户余额足够，矿工会‘回家休息’。
 * 否则，继续进矿场挖矿。
 * */
class VisitBankAndDepositGold : public State
{
private:

    VisitBankAndDepositGold(){}

public:
    //禁止复制构造函数和赋值,同时避免内存泄露
    ~VisitBankAndDepositGold(){}
    VisitBankAndDepositGold(const VisitBankAndDepositGold&)=delete;
    VisitBankAndDepositGold& operator=(const VisitBankAndDepositGold&)=delete;

    //this is a singleton
    static VisitBankAndDepositGold* Instance();

    virtual void Enter(Miner* miner);

    virtual void Execute(Miner* miner);

    virtual void Exit(Miner* miner);
};


/**
 * 在这个状态中，矿工会’走回家‘，然后’休息睡觉‘，直到疲劳值减少到一定程度。
 * */
class GoHomeAndSleepTilRested : public State
{
private:

    GoHomeAndSleepTilRested(){}

public:
    //禁止复制构造函数和赋值,同时避免内存泄露
    ~GoHomeAndSleepTilRested(){}
    GoHomeAndSleepTilRested(const GoHomeAndSleepTilRested&)=delete;
    GoHomeAndSleepTilRested& operator=(const GoHomeAndSleepTilRested&)=delete;

    //this is a singleton
    static GoHomeAndSleepTilRested* Instance();

    virtual void Enter(Miner* miner);

    virtual void Execute(Miner* miner);

    virtual void Exit(Miner* miner);
};


/**
 * 在这个状态中，矿工会’喝酒解渴‘。
 * */
class QuenchThirst : public State
{
private:

    QuenchThirst(){}

public:
    //禁止复制构造函数和赋值,同时避免内存泄露
    ~QuenchThirst(){}
    QuenchThirst(const QuenchThirst&)=delete;
    QuenchThirst& operator=(const QuenchThirst&)=delete;

    //this is a singleton
    static QuenchThirst* Instance();

    virtual void Enter(Miner* miner);

    virtual void Execute(Miner* miner);

    virtual void Exit(Miner* miner);
};

#endif