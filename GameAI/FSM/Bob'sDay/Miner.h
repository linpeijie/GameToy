//------------------------------------------------------------------------
//
//  Name:   Miner.h
//
//  Desc:   A class defining a goldminer.
//
//  Author: Mat Buckland 2002 (fup@ai-junkie.com)
//
//------------------------------------------------------------------------
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

  State*                m_pCurrentState;

  location_type         m_Location;

  //how many nuggets the miner has in his pockets
  int                   m_iGoldCarried;

  int                   m_iMoneyInBank;

  //the higher the value, the thirstier the miner
  int                   m_iThirst;

  //the higher the value, the more tired the miner
  int                   m_iFatigue;

public:

  Miner(int id);

  //this must be implemented
  void Update();

  //this method changes the current state to the new state. It first
  //calls the Exit() method of the current state, then assigns the
  //new state to m_pCurrentState and finally calls the Entry()
  //method of the new state.
  void ChangeState(State* new_state);

  location_type Location()const{return m_Location;}
  void          ChangeLocation(const location_type loc){m_Location=loc;}

  int           GoldCarried()const{return m_iGoldCarried;}
  void          SetGoldCarried(const int val){m_iGoldCarried = val;}
  void          AddToGoldCarried(const int val);
  bool          PocketsFull()const{return m_iGoldCarried >= MaxNuggets;}

  bool          Fatigued()const;
  void          DecreaseFatigue(){m_iFatigue -= 1;}
  void          IncreaseFatigue(){m_iFatigue += 1;}

  int           Wealth()const{return m_iMoneyInBank;}
  void          SetWealth(const int val){m_iMoneyInBank = val;}
  void          AddToWealth(const int val);

  bool          Thirsty()const;
  void          BuyAndDrinkAWhiskey(){m_iThirst = 0; m_iMoneyInBank-=2;}

};
